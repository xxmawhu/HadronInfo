#include "HadronInfo/EtaInfo.h"
#include "HadronInfo/ShowerInfo.h"
#include "HadronInfo/GGInfo.h"
#include <iostream>
#include <vector>
using std::vector;

EtaInfo::EtaInfo(){
    m_calculate = false;
    m_shower[0] = NULL;
    m_shower[1] = NULL;
}
void EtaInfo::setchild(const int& i, const EvtRecTrack *shower) {
    m_calculate = false;
    m_shower[i] = const_cast<EvtRecTrack *>(shower);
}
void EtaInfo::setchilds(const EvtRecTrack *shower0, 
        const EvtRecTrack *shower1) {
    m_calculate = false;
    this->setchild(0, shower0);
    this->setchild(1, shower1);
}
EvtRecTrack *EtaInfo::getchild(const int& n) {
    return m_shower[n];
}
EtaInfo::EtaInfo(vector<const EvtRecTrack *> shower) {
    m_calculate = false;
    this->setchild(0, shower[0]);
    this->setchild(1, shower[1]);
}

EtaInfo::EtaInfo(const EvtRecTrack *shower0, 
        const EvtRecTrack *shower1) {
    m_calculate = false;
    this->setchild(0, shower0);
    this->setchild(1, shower1);
}

EtaInfo::EtaInfo(const CDCandidate &aPi0) {
    m_calculate = false;
    this->setchild(0, aPi0.finalChildren().second[0]);
    this->setchild(1, aPi0.finalChildren().second[1]);
}

EtaInfo::~EtaInfo() {
    m_shower[0] = NULL;
    m_shower[1] = NULL;
}

/*
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
}*/

bool EtaInfo::calculate() {
    if (m_calculate) return true;
    if (isGoodPhoton(m_shower[0]) && isGoodPhoton(m_shower[1])) {
        m_isgoodeta = true;
    } else {
        m_isgoodeta = false;
    }
    // update the raw momentum which is not performed kinemitic fit yet.
    ShowerInfo showerInfo;
    showerInfo.setchild(m_shower[0]);
    HepLorentzVector p4raw1 = showerInfo.p4();
    showerInfo.setchild(m_shower[1]);
    HepLorentzVector p4raw2 = showerInfo.p4();
    GGInfo::setRawP4(p4raw1 + p4raw2);
    GGInfo::setRawMass((p4raw1 + p4raw2).m());
    GGInfo::setP4Child(p4raw1, 0);
    GGInfo::setP4Child(p4raw2, 1);

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
    GGInfo::setWTrackParameter(m_kmfit->wVirtualTrack(0));

    HepLorentzVector pfit1 = m_kmfit->pfit(0);
    HepLorentzVector pfit2 = m_kmfit->pfit(1);

    HepLorentzVector ppi0 = pfit1 + pfit2;
    GGInfo::setP41C(pfit1 + pfit2);
    GGInfo::setOpenAngle(cos(pfit1.vect().angle(pfit2.vect())));
    GGInfo::setHelicity((pfit1.e() - pfit2.e()) / ppi0.rho());

    const Hep3Vector bvpi0 = -(ppi0.boostVector());
    HepLorentzVector pfit1Bv = pfit1;
    pfit1Bv.boost(bvpi0);
    GGInfo::setHelicityAngle(pfit1Bv.vect().angle(-ppi0.vect()));
    m_calculate = true;
    return true;
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
bool EtaInfo::isGoodPi0() {
    if (!m_calculate) calculate();
    return m_isgoodeta;
}
double EtaInfo::chisq() {
    if (!m_calculate) calculate();
    return m_chisq;
}
WTrackParameter EtaInfo::wtrk() {
    if (!m_calculate) calculate();
    return m_wtrk;
}

HepLorentzVector EtaInfo::p4child(const int& id) {
    if (id==0) {
        // return high energy
        EvtRecTrack *trk = m_shower0;
        if (m_shower0->emcShower()->energy() < m_shower1->emcShower()->energy())
{
            trk = m_shower1;
        }
        TrackInfo showerInfo(trk);
        return showerInfo.p4(22);
    } else {
        // return low energy
        EvtRecTrack *trk = m_shower0;
        if (m_shower0->emcShower()->energy() < m_shower1->emcShower()->energy())
{
            trk = m_shower1;
        }
        TrackInfo showerInfo(trk);
        return showerInfo.p4(22);
    }
}

const double& EtaInfo::GetDoubleInfo(const string &info_name) {
    if (info_name == "mass") return this->m();
    if (info_name == "mass1C") return this->m1c();
    if (info_name == "angle") return this->angle();
    if (info_name == "openAngle") return this->openAngle();
    if (info_name == "helicity") return this->helicity();
    return -110;
}

const HepLorentzVector& EtaInfo::GetLorentzVector(const string &info_name) {
    if (info_name == "p4") return this->p4();
    if (info_name == "p41C") return this->p41c();
    if (info_name == "p4GammaHigh") return this->p4child(0);
    if (info_name == "p4GammaLow") return this->p4child(1);
    return HepLorentzVector(0, 0, 0, -110);
}
*/
