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
void GGInfo::AddAvialInfo() {
    AvailableInfo::Add("mass", "double");
    // AvailableInfo::Add("mass1C", "double");
    // AvailableInfo::Add("angle", "double");
    AvailableInfo::Add("openAngle", "double");
    AvailableInfo::Add("helicity", "double");
    AvailableInfo::Add("p4", "HepLorentzVector");
    AvailableInfo::Add("p41C", "HepLorentzVector");
    AvailableInfo::Add("p4GammaHigh", "HepLorentzVector");
    AvailableInfo::Add("p4GammaLow", "HepLorentzVector");
}
void GGInfo::GetInfo(const std::string& info_name, double& targe) {
    if (info_name == "mass") {
        targe = this->Mass();
    } else if (info_name == "openAngle") {
        targe = this->OpenAngle();

    } else if (info_name == "helicity") {
        targe = this->Helicity();
    }
}
void GGInfo::GetInfo(const std::string& info_name,
                             HepLorentzVector& targe) {
    if (info_name == "p4") {
        targe = this->P4();
    } else if (info_name == "p41C") {
        targe = this->p41c();
    }
else if (info_name == "p4GammaLow") {
    targe = this->P4GammaLow();
}
else if (info_name == "p4GammaHigh") {
    targe = this->P4GammaHigh();
}
}

const double& GGInfo::GetDoubleInfo(const string& info_name) {
    if (info_name == "helicity") return this->Helicity();
    // if (info_name == "helicity") return this->HelicityAngle();
    if (info_name == "openAngle") return this->OpenAngle();
    if (info_name == "mass") return this->m();
    // the default value is set at a very large number, however it can not
    // prevent someone taking it as a very reasonal value. Hope you could
    // understand my purpose here.
    return -999;
}

const HepLorentzVector& GGInfo::GetLorentzVector(const string& info_name) {
    if (info_name == "p4") return this->P4();
    if (info_name == "p41C") return this->p41C();
    if (info_name == "p4GammaHigh") return this->P4GammaHigh();
    if (info_name == "p4GammaLow") return this->P4GammaLow();
    // the default value is set at a very large number, however it can not
    // prevent someone taking it as a very reasonal value. Hope you could
    // understand my purpose here.
    return HepLorentzVector(0, 0, 0, -999);
}

const double& GGInfo::Mass() {
    // turn the invarin mass of two gamma before 1C fit
    if (!m_calculate) Calculate();
    return m_mpi0;
}

const double& GGInfo::Angle() {
    if (!m_calculate) Calculate();
    return m_angle;
}

const double& GGInfo::OpenAngle() {
    if (!m_calculate) Calculate();
    return m_openAngle;
}

const double& GGInfo::Helicity() {
    if (!m_calculate) Calculate();
    return m_helicity;
}
const HepLorentzVector& GGInfo::P4() {
    if (!m_calculate) Calculate();
    return m_rawP4;
}
const HepLorentzVector& GGInfo::p41C() {
    if (!m_calculate) Calculate();
    return m_P41C;
}
const HepLorentzVector& GGInfo::P4Child(const int& i) {
    if (!m_calculate) Calculate();
    return m_rawP4Child[i];
}
const HepLorentzVector& GGInfo::P4GammaHigh() {
    if (!m_calculate) Calculate();
    if (m_rawP4Child[0].e() > m_rawP4Child[1].e()) {
        return m_rawP4Child[0];
    } else {
        return m_rawP4Child[1];
    }
}

const HepLorentzVector& GGInfo::P4GammaLow() {
    if (!m_calculate) Calculate();
    if (m_rawP4Child[0].e() < m_rawP4Child[1].e()) {
        return m_rawP4Child[0];
    } else {
        return m_rawP4Child[1];
    }
}
const double& GGInfo::Chisq() {
    if (!m_calculate) Calculate();
    return m_chisq;
}
const bool& GGInfo::isGood() {
    if (!m_calculate) Calculate();
    return m_isgoodpi0;
}
const WTrackParameter& GGInfo::WTrk() {
    if (!m_calculate) Calculate();
    return m_wtrk;
}
// GGInfo &operator=(GGInfo &aGGInfo);
bool GGInfo::Calculate() { m_calculate = true; }
void GGInfo::SetWTrackParameter(const WTrackParameter& wtrk) { m_wtrk = wtrk; }
void GGInfo::SetRawMass(const double& mass) { m_mpi0 = mass; }
void GGInfo::SetHelicity(const double& helicity) { m_helicity = helicity; }
void GGInfo::SetHelicityAngle(const double& helicityAngle) {
    m_helicityAngle = helicityAngle;
}
void GGInfo::SetOpenAngle(const double& openangle) { m_openAngle = openangle; }
void GGInfo::SetChisq(const double& chisq) { m_chisq = chisq; }
void GGInfo::SetP41C(const HepLorentzVector& p4) { m_P41C = p4; }
void GGInfo::SetRawP4(const HepLorentzVector& p4) { m_rawP4 = p4; }
void GGInfo::SetP4Child(const HepLorentzVector& p4, const int& i) {
    m_rawP4Child[i] = p4;
}

bool GGInfo::isGoodPhoton(EvtRecTrack* track) {
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
