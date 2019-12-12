#include "HadronInfo/EtaInfo.h"
#include "HadronInfo/TrackInfo.h"
#include <iostream>
#include <vector>
using std::vector;

EtaInfo::EtaInfo() : m_shower0(0), m_shower1(0), m_p4(0), m_mpi0(0) {
    m_calculate = false;
}
EtaInfo::EtaInfo(EvtRecTrack *shower1, EvtRecTrack *shower2) {
    m_calculate = false;
    m_shower0 = shower1;
    m_shower1 = shower2;
}
EtaInfo::EtaInfo(vector<const EvtRecTrack *> showers) {
    m_calculate = false;
    m_shower0 = const_cast<EvtRecTrack *>(showers[0]);
    m_shower1 = const_cast<EvtRecTrack *>(showers[1]);
}
EtaInfo::EtaInfo(const CDCandidate &aEta) {
    const EvtRecTrack *trk0 = aEta.finalChildren().second[0];
    const EvtRecTrack *trk1 = aEta.finalChildren().second[1];
    m_shower0 = const_cast<EvtRecTrack *>(trk0);
    m_shower1 = const_cast<EvtRecTrack *>(trk1);
    m_calculate = false;
}
EtaInfo::~EtaInfo() {}
bool EtaInfo::isGoodPhoton(EvtRecTrack *track) {
    if (!track->isEmcShowerValid()) return false;
    const RecEmcShower *photon = track->emcShower();
    double eraw = photon->energy();
    double theta = photon->theta();
    double costheta = fabs(cos(theta));
    // barrel: costheta < 0.80
    if (costheta <= 0.80 && eraw >= 0.025) {
        return true;
    }
    if (costheta >= 0.86 && costheta <= 0.92 && eraw >= 0.05) {
        return true;
    }
    return false;
}
bool EtaInfo::calculate() {
    if (m_calculate) return true;
    if (isGoodPhoton(m_shower0) && isGoodPhoton(m_shower1)) {
        m_isgoodpi0 = true;
    } else {
        m_isgoodpi0 = false;
    }
    TrackInfo trkInf;
    KalmanKinematicFit *m_kmfit;
    m_kmfit = KalmanKinematicFit::instance();
    m_kmfit->init();

    RecEmcShower *photon1 = m_shower0->emcShower();
    RecEmcShower *photon2 = m_shower1->emcShower();

    m_kmfit->AddTrack(0, 0.0, photon1);
    m_kmfit->AddTrack(1, 0.0, photon2);
    m_kmfit->AddResonance(0, 0.547862, 0, 1);

    m_kmfit->Fit(0);  // Perform fit
    m_chisq = m_kmfit->chisq(0);

    m_kmfit->BuildVirtualParticle(0);
    m_wtrk = m_kmfit->wVirtualTrack(0);

    HepLorentzVector pfit1 = m_kmfit->pfit(0);
    HepLorentzVector pfit2 = m_kmfit->pfit(1);

    HepLorentzVector ppi0 = pfit1 + pfit2;
    m_openAngle = cos(pfit1.vect().angle(pfit2.vect()));
    m_helicity = (pfit1.e() - pfit2.e()) / ppi0.rho();

    HepLorentzVector p4raw1 = trkInf.p4(m_shower0, 22);
    HepLorentzVector p4raw2 = trkInf.p4(m_shower1, 22);
    m_p4 = p4raw1 + p4raw2;
    m_p41c = pfit1 + pfit2;
    m_mpi0 = (p4raw1 + p4raw2).m();
    m_mpi01c = (pfit1 + pfit2).m();
    const Hep3Vector bvpi0 = -(ppi0.boostVector());
    HepLorentzVector pfit1Bv = pfit1;
    pfit1Bv.boost(bvpi0);
    m_pi0_heliAngle = pfit1Bv.vect().angle(-ppi0.vect());
    m_calculate = true;
    return true;
}
EtaInfo &EtaInfo::operator=(EtaInfo &aEtaInfo) {
    m_shower0 = aEtaInfo.getchild(0);
    m_shower1 = aEtaInfo.getchild(1);
    m_p4 = aEtaInfo.p4();
    m_p41c = aEtaInfo.p41c();
    m_mpi0 = aEtaInfo.m();
    m_mpi01c = aEtaInfo.m1c();
    m_pi0_heliAngle = aEtaInfo.angle();
    m_openAngle = aEtaInfo.openAngle();
    m_helicity = aEtaInfo.helicity();
    m_chisq = aEtaInfo.chisq();
    return *this;
}
void EtaInfo::setchild(int n, EvtRecTrack *shower) {
    m_calculate = false;
    if (n == 0) {
        m_shower0 = shower;
    } else if (n == 1) {
        m_shower1 = shower;
    }
}
void EtaInfo::setchilds(EvtRecTrack *shower0, EvtRecTrack *shower1) {
    m_calculate = false;
    m_shower0 = shower0;
    m_shower1 = shower1;
}
EvtRecTrack *EtaInfo::getchild(int n) {
    if (n == 0) {
        return m_shower0;
    } else if (n == 1) {
        return m_shower1;
    }
}


/*
double EtaInfo::m() {
    if (!m_calculate) calculate();
    return m_mpi0;
}
double EtaInfo::m1c() {
    if (!m_calculate) calculate();
    return m_mpi01c;
}
double EtaInfo::angle() {
    if (!m_calculate) calculate();
    return m_pi0_heliAngle;
}
double EtaInfo::openAngle() {
    if (!m_calculate) calculate();
    return m_openAngle;
}
double EtaInfo::helicity() {
    if (!m_calculate) calculate();
    return m_helicity;
}
HepLorentzVector EtaInfo::p4() {
    if (!m_calculate) calculate();
    return m_p4;
}
HepLorentzVector EtaInfo::p41c() {
    if (!m_calculate) calculate();
    return m_p41c;
}
bool EtaInfo::isGoodEta() {
    if (!m_calculate) calculate();
    return m_isgoodpi0;
}
double EtaInfo::chisq() {
    if (!m_calculate) calculate();
    return m_chisq;
}
WTrackParameter EtaInfo::wtrk() {
    if (!m_calculate) calculate();
    return m_wtrk;
}

HepLorentzVector EtaInfo::p4child(const int &id) {
    if (id == 0) {
        // return high energy
        EvtRecTrack *trk = m_shower0;
        if (m_shower0->emcShower()->energy() <
            m_shower1->emcShower()->energy()) {
            trk = m_shower1;
        }
        TrackInfo showerInfo(trk);
        return showerInfo.p4(22);
    } else {
        // return low energy
        EvtRecTrack *trk = m_shower0;
        if (m_shower0->emcShower()->energy() <
            m_shower1->emcShower()->energy()) {
            trk = m_shower1;
        }
        TrackInfo showerInfo(trk);
        return showerInfo.p4(22);
    }
}
double EtaInfo::GetDoubleInfo(const string &info_name) {
    if (info_name == "mass") return this->m();
    if (info_name == "mass1C") return this->m1c();
    if (info_name == "angle") return this->angle();
    if (info_name == "openAngle") return this->openAngle();
    if (info_name == "helicity") return this->helicity();
    return -110;
}

HepLorentzVector EtaInfo::GetLorentzVector(const string &info_name) {
    if (info_name == "p4") return this->p4();
    if (info_name == "p41C") return this->p41c();
    if (info_name == "p4GammaHigh") return this->p4child(0);
    if (info_name == "p4GammaLow") return this->p4child(1);
    return HepLorentzVector(0, 0, 0, -110);
}
*/
