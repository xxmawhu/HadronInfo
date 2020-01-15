#include "HadronInfoDev/EtaInfoDev.h"
#include "HadronInfoDev/ShowerInfoDev.h"
#include "HadronInfoDev/GGInfoDev.h"
#include <iostream>
#include <vector>
using std::vector;

EtaInfoDev::EtaInfoDev() {
    m_calculate = false;
    m_shower[0] = NULL;
    m_shower[1] = NULL;
}
void EtaInfoDev::setchild(const int &i, const EvtRecTrack *shower) {
    m_calculate = false;
    m_shower[i] = const_cast<EvtRecTrack *>(shower);
}
void EtaInfoDev::setchilds(const EvtRecTrack *shower0,
                        const EvtRecTrack *shower1) {
    m_calculate = false;
    this->setchild(0, shower0);
    this->setchild(1, shower1);
}
EvtRecTrack *EtaInfoDev::getchild(const int &n) { return m_shower[n]; }
EtaInfoDev::EtaInfoDev(vector<const EvtRecTrack *> shower) {
    m_calculate = false;
    this->setchild(0, shower[0]);
    this->setchild(1, shower[1]);
}

EtaInfoDev::EtaInfoDev(const EvtRecTrack *shower0, const EvtRecTrack *shower1) {
    m_calculate = false;
    this->setchild(0, shower0);
    this->setchild(1, shower1);
}

EtaInfoDev::EtaInfoDev(const CDCandidate &aPi0) {
    m_calculate = false;
    this->setchild(0, aPi0.finalChildren().second[0]);
    this->setchild(1, aPi0.finalChildren().second[1]);
}

EtaInfoDev::~EtaInfoDev() {
    m_shower[0] = NULL;
    m_shower[1] = NULL;
}

bool EtaInfoDev::calculate() {
    if (m_calculate) return true;
    if (isGoodPhoton(m_shower[0]) && isGoodPhoton(m_shower[1])) {
        m_isgoodeta = true;
    } else {
        m_isgoodeta = false;
    }
    // update the raw momentum which is not performed kinemitic fit yet.
    ShowerInfoDev showerInfoDev;
    showerInfoDev.setchild(m_shower[0]);
    HepLorentzVector p4raw1 = showerInfoDev.p4();
    showerInfoDev.setchild(m_shower[1]);
    HepLorentzVector p4raw2 = showerInfoDev.p4();
    GGInfoDev::setRawP4(p4raw1 + p4raw2);
    GGInfoDev::setRawMass((p4raw1 + p4raw2).m());
    GGInfoDev::setP4Child(p4raw1, 0);
    GGInfoDev::setP4Child(p4raw2, 1);

    KalmanKinematicFit *m_kmfit;
    m_kmfit = KalmanKinematicFit::instance();
    m_kmfit->init();

    RecEmcShower *photon1 = m_shower[0]->emcShower();
    RecEmcShower *photon2 = m_shower[1]->emcShower();

    m_kmfit->AddTrack(0, 0.0, photon1);
    m_kmfit->AddTrack(1, 0.0, photon2);
    m_kmfit->AddResonance(0, 0.547862, 0, 1);

    m_kmfit->Fit(0);

    setChisq(m_kmfit->chisq(0));

    m_kmfit->BuildVirtualParticle(0);
    GGInfoDev::setWTrackParameter(m_kmfit->wVirtualTrack(0));

    HepLorentzVector pfit1 = m_kmfit->pfit(0);
    HepLorentzVector pfit2 = m_kmfit->pfit(1);

    HepLorentzVector ppi0 = pfit1 + pfit2;
    GGInfoDev::setP41C(pfit1 + pfit2);
    GGInfoDev::setOpenAngle(cos(pfit1.vect().angle(pfit2.vect())));
    GGInfoDev::setHelicity((pfit1.e() - pfit2.e()) / ppi0.rho());

    const Hep3Vector bvpi0 = -ppi0.boostVector();
    HepLorentzVector pfit1Bv = pfit1;
    pfit1Bv.boost(bvpi0);
    GGInfoDev::setHelicityAngle(pfit1Bv.vect().angle(-ppi0.vect()));
    m_calculate = true;
    return true;
}
