/* ====================================================
#   Copyright (C)2019 All rights reserved.
#
#   Author        : Xin-Xin MA
#   Email         : xxmawhu@163.com
#   File Name     : GGInfo.h
#   Create Time   : 2019-12-09 20:49
#   Last Modified : 2019-12-09 20:49
#   Describe      :
#
# ====================================================*/

#ifndef CLASS_HadronInfo_GGInfo_H
#define CLASS_HadronInfo_GGInfo_H

#include "EvtRecEvent/EvtRecTrack.h"

#include "CLHEP/Vector/LorentzVector.h"
#include "VertexFit/KalmanKinematicFit.h"
#include "BesDChain/CDDecay.h"
#include "HadronInfo/AvailableInfo.h"

#include <iostream>

using namespace std;
class GGInfo : public AvailableInfo {
   public:
    GGInfo():AvailableInfo(){
    }
    ~GGInfo(){};
    virtual double GetDoubleInfo(const string & info_name){
        if (info_name == "helicity") return this->helicity();
        if (info_name == "openAngle") return this->openAngle();
        if (info_name == "mass") return this->m();
        return -999;
    }
    virtual HepLorentzVector GetLorentzVector(const string &info_name){
        if (info_name == "p4") return this->p4();
        if (info_name == "p41C") return this->p41C();
        if (info_name == "p4GammaHigh") return this->p4GammaHigh();
        if (info_name == "p4GammaLow") return this->p4GammaLow();
        return HepLorentzVector(0, 0, 0, -999);
    }
    const double& m(){
        // turn the invarin mass of two gamma before 1C fit
        if (!m_calculate) calculate();
        return m_mpi0;
    }
    const double& m1c(){
        if (!m_calculate) calculate();
        return m_mpi01c;
    }
    const double& angle(){
        if (!m_calculate) calculate();
        return m_pi0_heliAngle;
    }
    const double& openAngle(){
        if (!m_calculate) calculate();
        return m_openAngle;
    }
    const double& helicity(){
        if (!m_calculate) calculate();
        return m_helicity;
    }
    const HepLorentzVector& p4(){
        if (!m_calculate) calculate();
        return m_rawP4; 
    }
    const HepLorentzVector& p41C(){
        if (!m_calculate) calculate();
        return m_P41C; 
    }
    const HepLorentzVector& p4child(const int &i){
        if (!m_calculate) calculate();
        return m_rawP4Child[i];
    }
    const HepLorentzVector& p4GammaHigh(){
        if (!m_calculate) calculate();
        if (m_rawP4Child[0].e()  > m_rawP4Child[1].e()){
            return m_rawP4Child[0];
        } else {
            return m_rawP4Child[1];
        }
    }

    const HepLorentzVector& p4GammaLow(){
        if (!m_calculate) calculate();
        if (m_rawP4Child[0].e()  < m_rawP4Child[1].e()){
            return m_rawP4Child[0];
        } else {
            return m_rawP4Child[1];
        }
    }
    const double& chisq(){
        if (!m_calculate) calculate();
        return m_chisq;
    }
    const bool& isGood(){
        if (!m_calculate) calculate();
        return m_isgoodpi0;
    }
    const WTrackParameter& wtrk(){
        if (!m_calculate) calculate();
        return m_wtrk; 
    }
    // GGInfo &operator=(GGInfo &aGGInfo);
    virtual bool calculate(){
        m_calculate = true;
    }
    void setWTrackParameter(const WTrackParameter& wtrk){
        m_wtrk = wtrk;
    }
    void setRawMass(const double& mass){
        m_mpi0 = mass;
    }
    void setHelicity(const double& helicity){
        m_helicity = helicity;
    }
    void setOpenAngle(const double& openangle){
        m_openAngle = openangle;
    }
    void setChisq(const double& chisq){
        m_chisq = chisq;
    }
    void setP41C(const HepLorentzVector& p4) {
        m_P41C = p4;
    }
    void setRawP4(const HepLorentzVector& p4){
        m_rawP4 = p4;
    }
    void setP4Child(const HepLorentzVector& p4, const int& i){
        m_rawP4Child[i] = p4;
    }

   private:
    WTrackParameter m_wtrk;
    bool isGoodPhoton(EvtRecTrack *);
    HepLorentzVector m_rawP4;
    HepLorentzVector m_P41C;
    HepLorentzVector m_rawP4Child[2];
    double constrain_mass;
    double m_mpi0;
    double m_mpi01c;
    double m_pi0_heliAngle;
    double m_helicity;
    double m_openAngle;
    double m_chisq;
    bool m_isgoodpi0, m_calculate;
    void initAvialableInfo() {
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
};
#endif
