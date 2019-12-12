/* ====================================================
#   Copyright (C)2019 All rights reserved.
#
#   Author        : Xin-Xin MA
#   Email         : xxmawhu@163.com
#   File Name     : GGInfo.cxx
#   Create Time   : 2019-12-09 20:49
#   Last Modified : 2019-12-11 22:06
#   Describe      :
#
# ====================================================*/

#include "EvtRecEvent/EvtRecTrack.h"

#include "CLHEP/Vector/LorentzVector.h"
#include "VertexFit/KalmanKinematicFit.h"
#include "BesDChain/CDDecay.h"
#include "HadronInfo/AvailableInfo.h"
#include "HadronInfo/GGInfo.h"

#include <iostream>
using namespace std;
void GGInfo::addAvialInfo() {
    AvailableInfo::add("mass", "double");
    // AvailableInfo::add("mass1C", "double");
    // AvailableInfo::add("angle", "double");
    AvailableInfo::add("openAngle", "double");
    AvailableInfo::add("helicity", "double");
    AvailableInfo::add("p4", "HepLorentzVector");
    AvailableInfo::add("p41C", "HepLorentzVector");
    AvailableInfo::add("p4GammaHigh", "HepLorentzVector");
    AvailableInfo::add("p4GammaLow", "HepLorentzVector");
}

const double& GGInfo::GetDoubleInfo(const string& info_name) {
    if (info_name == "helicity") return this->helicity();
    // if (info_name == "helicity") return this->helicityAngle();
    if (info_name == "openAngle") return this->openAngle();
    if (info_name == "mass") return this->m();
    // the default value is set at a very large number, however it can not 
    // prevent someone taking it as a very reasonal value. Hope you could 
    // understand my purpose here.
    return -999;
}

const HepLorentzVector& GGInfo::GetLorentzVector(const string& info_name) {
    if (info_name == "p4") return this->p4();
    if (info_name == "p41C") return this->p41C();
    if (info_name == "p4GammaHigh") return this->p4GammaHigh();
    if (info_name == "p4GammaLow") return this->p4GammaLow();
    // the default value is set at a very large number, however it can not 
    // prevent someone taking it as a very reasonal value. Hope you could 
    // understand my purpose here.
    return HepLorentzVector(0, 0, 0, -999);
}


const double& GGInfo::m() {
    // turn the invarin mass of two gamma before 1C fit
    if (!m_calculate) calculate();
    return m_mpi0;
}
const double& GGInfo::m1c() {
    if (!m_calculate) calculate();
    return m_mpi01c;
}
const double& GGInfo::angle() {
    if (!m_calculate) calculate();
    return m_angle;
}
const double& GGInfo::openAngle() {
    if (!m_calculate) calculate();
    return m_openAngle;
}
const double& GGInfo::helicity() {
    if (!m_calculate) calculate();
    return m_helicity;
}
const HepLorentzVector& GGInfo::p4() {
    if (!m_calculate) calculate();
    return m_rawP4;
}
const HepLorentzVector& GGInfo::p41C() {
    if (!m_calculate) calculate();
    return m_P41C;
}
const HepLorentzVector& GGInfo::p4child(const int& i) {
    if (!m_calculate) calculate();
    return m_rawP4Child[i];
}
const HepLorentzVector& GGInfo::p4GammaHigh() {
    if (!m_calculate) calculate();
    if (m_rawP4Child[0].e() > m_rawP4Child[1].e()) {
        return m_rawP4Child[0];
    } else {
        return m_rawP4Child[1];
    }
}

const HepLorentzVector& GGInfo::p4GammaLow() {
    if (!m_calculate) calculate();
    if (m_rawP4Child[0].e() < m_rawP4Child[1].e()) {
        return m_rawP4Child[0];
    } else {
        return m_rawP4Child[1];
    }
}
const double& GGInfo::chisq() {
    if (!m_calculate) calculate();
    return m_chisq;
}
const bool& GGInfo::isGood() {
    if (!m_calculate) calculate();
    return m_isgoodpi0;
}
const WTrackParameter& GGInfo::wtrk() {
    if (!m_calculate) calculate();
    return m_wtrk;
}
// GGInfo &operator=(GGInfo &aGGInfo);
bool GGInfo::calculate() { m_calculate = true; }
void GGInfo::setWTrackParameter(const WTrackParameter& wtrk) { m_wtrk = wtrk; }
void GGInfo::setRawMass(const double& mass) { m_mpi0 = mass; }
void GGInfo::setHelicity(const double& helicity) { m_helicity = helicity; }
void GGInfo::setHelicityAngle(const double& helicityAngle) {
    m_helicityAngle = helicityAngle;
}
void GGInfo::setOpenAngle(const double& openangle) { m_openAngle = openangle; }
void GGInfo::setChisq(const double& chisq) { m_chisq = chisq; }
void GGInfo::setP41C(const HepLorentzVector& p4) { m_P41C = p4; }
void GGInfo::setRawP4(const HepLorentzVector& p4) { m_rawP4 = p4; }
void GGInfo::setP4Child(const HepLorentzVector& p4, const int& i) {
    m_rawP4Child[i] = p4;
}

bool GGInfo::isGoodPhoton(EvtRecTrack *track) {
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
