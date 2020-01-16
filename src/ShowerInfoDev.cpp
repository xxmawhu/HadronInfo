#include "HadronInfoDev/ShowerInfoDev.h"

ShowerInfoDev::ShowerInfoDev() : m_shower(0) {
    m_energyThreshold_e = 0.05;
    m_energyThreshold_b = 0.025;
    m_costheta_b = 0.8;
    m_costheta_e1 = 0.86;
    m_costheta_e2 = 0.92;
    m_cal = false;
}
ShowerInfoDev::ShowerInfoDev(const CDCandidate &aTrk) {
    m_shower= const_cast<EvtRecTrack* >(aTrk.finalChildren().second[0]);
}

ShowerInfoDev::~ShowerInfoDev() {
    m_shower = 0;
    m_p4 = HepLorentzVector(0, 0, 0, 0);
}
bool ShowerInfoDev::calculate() {
    if (m_cal) {
        return true;
    }
    m_badshower = false;
    if (m_shower == 0) return false;
    RecEmcShower *photon1 = m_shower->emcShower();
    double eraw1 = photon1->energy();
    double phi1 = photon1->phi();
    double theta1 = photon1->theta();
    double costheta1 = fabs(cos(theta1));
    HepLorentzVector p4raw1;
    p4raw1.setPx(eraw1 * sin(theta1) * cos(phi1));
    p4raw1.setPy(eraw1 * sin(theta1) * sin(phi1));
    p4raw1.setPz(eraw1 * cos(theta1));
    p4raw1.setE(eraw1);
    if (!((costheta1 < m_costheta_b && eraw1 > m_energyThreshold_b) ||
          (costheta1 > m_costheta_e1 && costheta1 < m_costheta_e2 &&
           eraw1 > m_energyThreshold_e)))
        return false;
    if ((costheta1 > m_costheta_e1 && costheta1 < m_costheta_e2))
        m_badshower = true;

    m_p4 = p4raw1;
    m_cal = true;
    return true;
}

HepLorentzVector ShowerInfoDev::p4() {
    if (m_cal) {
        return m_p4;
    } else {
        this->calculate();
        return m_p4;
    }
}

ShowerInfoDev &ShowerInfoDev::operator=(ShowerInfoDev &aShowerInfoDev) {
    m_shower = aShowerInfoDev.getchild();
    m_p4 = aShowerInfoDev.p4();
    return *this;
}
const double &ShowerInfoDev::GetDoubleInfoDev(const string &info_name) {
    // if (info_name == "decayLengthError") return this->decayLengthError();
    return -110;
}

const HepLorentzVector &ShowerInfoDev::GetLorentzVector(const string &info_name) {
    if (info_name == "p4") return this->p4();
    return HepLorentzVector(0, 0, 0, -110);
}