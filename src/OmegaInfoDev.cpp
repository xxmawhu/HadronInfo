#include "GaudiKernel/Bootstrap.h"
#include "HadronInfoDev/OmegaInfoDev.h"
#include "HadronInfoDev/OmegaInfoDev.h"
#include "EvtRecEvent/EvtRecVeeVertex.h"
#include "VertexFit/VertexFit.h"
#include "VertexFit/SecondVertexFit.h"
#include "VertexFit/IVertexDbSvc.h"
#include "GaudiKernel/ISvcLocator.h"

#include "HadronInfoDev/LamInfoDev.h"
OmegaInfoDev::OmegaInfoDev() : m_track0(0), m_track1(0), m_track2(0) {
    m_cal = false;
}

OmegaInfoDev::OmegaInfoDev(const EvtRecTrack *track0, const EvtRecTrack *track1,
                     const EvtRecTrack *track2) {
    this->setchilds(track0, track1, track2);
}

OmegaInfoDev::OmegaInfoDev(const CDCandidate &aOmega) {
    const EvtRecTrack *trk0 = aOmega.finalChildren().first[0];
    const EvtRecTrack *trk1 = aOmega.finalChildren().first[1];
    const EvtRecTrack *trk2 = aOmega.finalChildren().first[2];
    m_track0 = const_cast<EvtRecTrack *>(trk0);
    m_track1 = const_cast<EvtRecTrack *>(trk1);
    m_track2 = const_cast<EvtRecTrack *>(trk2);
    m_cal = false;
}

OmegaInfoDev::~OmegaInfoDev() {
    m_track0 = 0;
    m_track1 = 0;
    m_track2 = 0;
    m_p4 = HepLorentzVector(0, 0, 0, 0);
}

bool OmegaInfoDev::calculate() {
    if (m_cal) {
        return true;
    }
    m_cal = true;
    RecMdcKalTrack *protonTrk = m_track0->mdcKalTrack();
    RecMdcKalTrack *pionmTrk = m_track1->mdcKalTrack();
    RecMdcKalTrack *kaonmTrk = m_track2->mdcKalTrack();
    protonTrk->setPidType(RecMdcKalTrack::proton);
    pionmTrk->setPidType(RecMdcKalTrack::pion);
    kaonmTrk->setPidType(RecMdcKalTrack::kaon);
    HepLorentzVector protonp4 = protonTrk->p4(Omegainfo_mproton);
    HepLorentzVector pionmp4 = pionmTrk->p4(Omegainfo_mpionm);
    HepLorentzVector kaonmp4 = kaonmTrk->p4(Omegainfo_mkaonm);
    HepLorentzVector omegap4 = protonp4 + pionmp4 + kaonmp4;
    m_momegap4 = omegap4.m();

    WTrackParameter wKaon(Omegainfo_mkaonm, kaonmTrk->getZHelixK(),
                          kaonmTrk->getZErrorK());

    const EvtRecTrack *trk0 = m_track0;
    const EvtRecTrack *trk1 = m_track1;
    LamInfoDev lamInfoDev(trk0, trk1);
    WTrackParameter lamWtrk = lamInfoDev.wtrk();

    VertexParameter wideVertex;
    HepPoint3D vWideVertex(0., 0., 0.);
    HepSymMatrix evWideVertex(3, 0);

    evWideVertex[0][0] = 1.0e12;
    evWideVertex[1][1] = 1.0e12;
    evWideVertex[2][2] = 1.0e12;

    wideVertex.setVx(vWideVertex);
    wideVertex.setEvx(evWideVertex);

    // add the primary vertex
    VertexParameter primaryVertex;
    if (!m_isSetPriVtx) {
        VertexParameter beamSpot;
        HepPoint3D vBeamSpot(0., 0., 0.);
        HepSymMatrix evBeamSpot(3, 0);

        IVertexDbSvc *vtxsvc;
        Gaudi::svcLocator()->service("VertexDbSvc", vtxsvc);
        double *dbv = vtxsvc->PrimaryVertex();
        double *vv = vtxsvc->SigmaPrimaryVertex();
        for (unsigned int ivx = 0; ivx < 3; ivx++) {
            vBeamSpot[ivx] = dbv[ivx];
            evBeamSpot[ivx][ivx] = vv[ivx] * vv[ivx];
        }

        beamSpot.setVx(vBeamSpot);
        beamSpot.setEvx(evBeamSpot);
        primaryVertex = VertexParameter(beamSpot);
    } else {
        primaryVertex = m_privtxpar;
    }
    //--------the first vertex fit
    VertexFit *m_vtxFit = VertexFit::instance();
    m_vtxFit->init();
    // m_vtxFit -> setChisqCut(1000);
    m_vtxFit->AddTrack(0, lamWtrk);
    m_vtxFit->AddTrack(1, wKaon);

    m_vtxFit->AddVertex(0, wideVertex, 0, 1);
    m_vtxFit->Fit(0);
    m_vtxFit->Swim(0);
    m_vtxFit->BuildVirtualParticle(0);

    m_wVirtualTrack = m_vtxFit->wVirtualTrack(0);
    m_wtrk[0] = m_vtxFit->wtrk(0);
    m_wtrk[1] = m_vtxFit->wtrk(1);
    m_vpar = m_vtxFit->vpar(0);
    m_pfit[0] = m_vtxFit->pfit(0);
    m_pfit[1] = m_vtxFit->pfit(0);
    m_p4child0 = m_vtxFit->pfit(0);
    m_p4child1 = m_vtxFit->pfit(1);
    m_p4 = m_p4child0 + m_p4child1;
    m_vmomega = m_p4.m();

    SecondVertexFit *m_2ndVtxFit = SecondVertexFit::instance();
    m_2ndVtxFit->init();
    // m_2ndVtxFit -> setChisqCut(1000);
    m_2ndVtxFit->AddTrack(0, m_wVirtualTrack);
    m_2ndVtxFit->setVpar(m_vpar);
    m_2ndVtxFit->setPrimaryVertex(primaryVertex);
    m_2ndVtxFit->Fit();

    m_vchi2omega1 = m_vtxFit->chisq(0);
    m_vchi2omega2 = m_2ndVtxFit->chisq();
    m_vlomega = m_2ndVtxFit->decayLength();
    if (m_2ndVtxFit->decayLengthError() == 0) {
        m_vromega = -999;
    } else {
        m_vromega =
            m_2ndVtxFit->decayLength() / m_2ndVtxFit->decayLengthError();
    }
    m_veomega = m_2ndVtxFit->decayLengthError();
    m_2ndVtx = m_2ndVtxFit->crossPoint();
    return true;
}

void OmegaInfoDev::setchilds(const EvtRecTrack *track0, const EvtRecTrack *track1,
                          const EvtRecTrack *track2) {
    m_track0 = const_cast<EvtRecTrack *>(track0);
    m_track1 = const_cast<EvtRecTrack *>(track1);
    m_track2 = const_cast<EvtRecTrack *>(track2);
    m_cal = false;
}

void OmegaInfoDev::setchild(const int &n, const EvtRecTrack *track) {
    if (n == 0) {
        m_track0 = const_cast<EvtRecTrack *>(track);
    } else if (n == 1) {
        m_track1 = const_cast<EvtRecTrack *>(track);
    } else if (n == 2) {
        m_track2 = const_cast<EvtRecTrack *>(track);
    }
    m_cal = false;
}
EvtRecTrack *OmegaInfoDev::getchild(const int &n) {
    if (n == 0) {
        return m_track0;
    } else if (n == 1) {
        return m_track1;
    } else if (n == 2) {
        return m_track2;
    }
}

double OmegaInfoDev::m() {
    if (!m_cal) {
        calculate();
        m_cal = true;
    }
    return m_vmomega;
}
double OmegaInfoDev::momegap4() {
    if (!m_cal) {
        calculate();
        m_cal = true;
    }
    return m_momegap4;
}

double OmegaInfoDev::vtxChi2() {
    if (!m_cal) {
        calculate();
        m_cal = true;
    }
    return m_vchi2omega1;
}

double OmegaInfoDev::chi2() {
    if (!m_cal) {
        calculate();
        m_cal = true;
    }
    return m_vchi2omega2;
}
double OmegaInfoDev::decayLength() {
    if (!m_cal) {
        calculate();
        m_cal = true;
    }
    return m_vlomega;
}
double OmegaInfoDev::decayLengthRatio() {
    if (!m_cal) {
        calculate();
        m_cal = true;
    }
    return m_vromega;
}
double OmegaInfoDev::decayLengthError() {
    if (!m_cal) {
        calculate();
        m_cal = true;
    }
    return m_veomega;
}
HepLorentzVector OmegaInfoDev::p4() {
    if (!m_cal) {
        calculate();
        m_cal = true;
    }
    return m_p4;
}
HepLorentzVector OmegaInfoDev::p4child(const int &i) {
    if (!m_cal) {
        calculate();
        m_cal = true;
    }
    return i == 0 ? m_p4child0 : m_p4child1;
}
HepLorentzVector OmegaInfoDev::pfit(const int &i) {
    if (!m_cal) {
        calculate();
        m_cal = true;
    }
    return m_pfit[i];
}
HepPoint3D OmegaInfoDev::sndvtx() {
    if (!m_cal) {
        calculate();
        m_cal = true;
    }
    return m_2ndVtx;
}
VertexParameter OmegaInfoDev::vtxPar() {
    if (!m_cal) {
        calculate();
        m_cal = true;
    }
    return m_vpar;
}
VertexParameter OmegaInfoDev::primaryVtxPar() {
    if (!m_cal) {
        calculate();
        m_cal = true;
    }
    return m_privtxpar;
}
void OmegaInfoDev::setPrimaryVtxPar(VertexParameter &privtxpar) {
    m_privtxpar = privtxpar;
    m_isSetPriVtx = true;
    m_cal = false;
}
/*
OmegaInfoDev &OmegaInfoDev::operator=(OmegaInfoDev &aOmegaInfoDev) {
    setchild(0, aOmegaInfoDev.getchild(0));
    setchild(1, aOmegaInfoDev.getchild(1));
    m_p4 = aOmegaInfoDev.p4();
    m_momegap4 = aOmegaInfoDev.momegap4();
    m_vmomega = aOmegaInfoDev.m();
    m_vchi2omega1 = aOmegaInfoDev.vtxChi2();
    m_vchi2omega2 = aOmegaInfoDev.chi2();
    m_vlomega = aOmegaInfoDev.decayLength();
    m_vromega = aOmegaInfoDev.decayLengthRatio();
    m_veomega = aOmegaInfoDev.decayLengthError();
    init();
    return *this;
}*/
WTrackParameter OmegaInfoDev::wtrk() {
    if (!m_cal) {
        calculate();
        m_cal = true;
    }
    return m_wVirtualTrack;
}
WTrackParameter &OmegaInfoDev::wtrk(const int &n) {
    if (!m_cal) {
        calculate();
        m_cal = true;
    }
    return m_wtrk[n];
}
const double &OmegaInfoDev::GetDoubleInfoDev(const string &info_name) {
    if (info_name == "mass") return this->m();
    if (info_name == "vtxChi2") return this->vtxChi2();
    if (info_name == "chisq") return this->chisq();
    if (info_name == "decayLength") return this->decayLength();
    if (info_name == "decayLengthRatio") return this->decayLengthRatio();
    if (info_name == "decayLengthError") return this->decayLengthError();
    return -999;
}

const HepLorentzVector &OmegaInfoDev::GetLorentzVector(const string &info_name) {
    if (info_name == "p4") return this->p4();
    if (info_name == "p4Proton") return this->p4child(0);
    if (info_name == "p4Pion") return this->p4child(1);
    return HepLorentzVector(0, 0, 0, -110);
}
