/* ====================================================
#   Copyright (C)2019 All rights reserved.
#
#   Author        : Xin-Xin MA
#   Email         : xxmawhu@163.com
#   File Name     : GGInfoDev.cxx
#   Create Time   : 2019-12-09 20:49
#   Last Modified : 2019-12-11 22:06
#   Describe      :
#
# ====================================================*/

#include "EvtRecEvent/EvtRecTrack.h"

#include "CLHEP/Vector/LorentzVector.h"
#include "VertexFit/KalmanKinematicFit.h"
#include "BesDChain/CDDecay.h"
#include "HadronInfoDev/AvailableInfoDev.h"
#include "HadronInfoDev/GGInfoDev.h"

#include <iostream>
using namespace std;
void GGInfoDev::addAvialInfoDev() {
    AvailableInfoDev::add("mass", "double");
    // AvailableInfoDev::add("mass1C", "double");
    // AvailableInfoDev::add("angle", "double");
    AvailableInfoDev::add("openAngle", "double");
    AvailableInfoDev::add("helicity", "double");
    AvailableInfoDev::add("p4", "HepLorentzVector");
    AvailableInfoDev::add("p41C", "HepLorentzVector");
    AvailableInfoDev::add("p4GammaHigh", "HepLorentzVector");
    AvailableInfoDev::add("p4GammaLow", "HepLorentzVector");
}

const double& GGInfoDev::GetDoubleInfoDev(const string& info_name) {
    if (info_name == "helicity") return this->helicity();
    // if (info_name == "helicity") return this->helicityAngle();
    if (info_name == "openAngle") return this->openAngle();
    if (info_name == "mass") return this->m();
    // the default value is set at a very large number, however it can not
    // prevent someone taking it as a very reasonal value. Hope you could
    // understand my purpose here.
    return -999;
}

const HepLorentzVector& GGInfoDev::GetLorentzVector(const string& info_name) {
    if (info_name == "p4") return this->p4();
    if (info_name == "p41C") return this->p41C();
    if (info_name == "p4GammaHigh") return this->p4GammaHigh();
    if (info_name == "p4GammaLow") return this->p4GammaLow();
    // the default value is set at a very large number, however it can not
    // prevent someone taking it as a very reasonal value. Hope you could
    // understand my purpose here.
    return HepLorentzVector(0, 0, 0, -999);
}

const double& GGInfoDev::m() {
    // turn the invarin mass of two gamma before 1C fit
    if (!m_calculate) calculate();
    return m_mpi0;
}
const double& GGInfoDev::m1c() {
    if (!m_calculate) calculate();
    return m_mpi01c;
}
const double& GGInfoDev::angle() {
    if (!m_calculate) calculate();
    return m_angle;
}
const double& GGInfoDev::openAngle() {
    if (!m_calculate) calculate();
    return m_openAngle;
}
const double& GGInfoDev::helicity() {
    if (!m_calculate) calculate();
    return m_helicity;
}
const HepLorentzVector& GGInfoDev::p4() {
    if (!m_calculate) calculate();
    return m_rawP4;
}
const HepLorentzVector& GGInfoDev::p41C() {
    if (!m_calculate) calculate();
    return m_P41C;
}
const HepLorentzVector& GGInfoDev::p4child(const int& i) {
    if (!m_calculate) calculate();
    return m_rawP4Child[i];
}
const HepLorentzVector& GGInfoDev::p4GammaHigh() {
    if (!m_calculate) calculate();
    if (m_rawP4Child[0].e() > m_rawP4Child[1].e()) {
        return m_rawP4Child[0];
    } else {
        return m_rawP4Child[1];
    }
}

const HepLorentzVector& GGInfoDev::p4GammaLow() {
    if (!m_calculate) calculate();
    if (m_rawP4Child[0].e() < m_rawP4Child[1].e()) {
        return m_rawP4Child[0];
    } else {
        return m_rawP4Child[1];
    }
}
const double& GGInfoDev::chisq() {
    if (!m_calculate) calculate();
    return m_chisq;
}
const bool& GGInfoDev::isGood() {
    if (!m_calculate) calculate();
    return m_isgoodpi0;
}
const WTrackParameter& GGInfoDev::wtrk() {
    if (!m_calculate) calculate();
    return m_wtrk;
}
// GGInfoDev &operator=(GGInfoDev &aGGInfoDev);
bool GGInfoDev::calculate() { m_calculate = true; }
void GGInfoDev::setWTrackParameter(const WTrackParameter& wtrk) { m_wtrk = wtrk; }
void GGInfoDev::setRawMass(const double& mass) { m_mpi0 = mass; }
void GGInfoDev::setHelicity(const double& helicity) { m_helicity = helicity; }
void GGInfoDev::setHelicityAngle(const double& helicityAngle) {
    m_helicityAngle = helicityAngle;
}
void GGInfoDev::setOpenAngle(const double& openangle) { m_openAngle = openangle; }
void GGInfoDev::setChisq(const double& chisq) { m_chisq = chisq; }
void GGInfoDev::setP41C(const HepLorentzVector& p4) { m_P41C = p4; }
void GGInfoDev::setRawP4(const HepLorentzVector& p4) { m_rawP4 = p4; }
void GGInfoDev::setP4Child(const HepLorentzVector& p4, const int& i) {
    m_rawP4Child[i] = p4;
}

bool GGInfoDev::isGoodPhoton(EvtRecTrack* track) {
    if (!track->isEmcShowerValid()) return false;
    const RecEmcShower* photon = track->emcShower();
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
