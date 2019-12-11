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
    GGInfo():AvailableInfo(){};
    ~GGInfo(){};
    virtual double GetDoubleInfo(const string & info_name);
    virtual HepLorentzVector GetLorentzVector(const string &info_name);
    const double& m();
    const double& m1c();
    const double& angle();
    const double& openAngle();
    const double& helicity();
    const HepLorentzVector& p4();
    const HepLorentzVector& p41C();
    const HepLorentzVector& p4child(const int &i);
    const HepLorentzVector& p4GammaHigh();
    const HepLorentzVector& p4GammaLow();
    const double& chisq();
    const bool& isGood();
    const WTrackParameter& wtrk();
    virtual bool calculate();
    void setWTrackParameter(const WTrackParameter& wtrk);
    void setRawMass(const double& mass);
    void setHelicity(const double& helicity);
    void setHelicityAngle(const double& helicityAngle);
    void setOpenAngle(const double& openangle);
    void setChisq(const double& chisq);
    void setP41C(const HepLorentzVector& p4);
    void setRawP4(const HepLorentzVector& p4);
    void setP4Child(const HepLorentzVector& p4, const int& i);

   private:
    WTrackParameter m_wtrk;
    bool isGoodPhoton(EvtRecTrack *);
    HepLorentzVector m_rawP4;
    HepLorentzVector m_P41C;
    HepLorentzVector m_rawP4Child[2];
    double m_mpi0;
    double m_mpi01c;
    double m_angle;
    double m_helicity;
    double m_openAngle, m_helicityAngle;
    double m_chisq;
    bool m_isgoodpi0, m_calculate;
    void initAvialableInfo();
};
#endif
