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
#include <string>

class GGInfo : virtual public AvailableInfo {
   public:
    GGInfo() : AvailableInfo() {};
    ~GGInfo() {};
    int Charge() { return 0; }
    virtual const double& GetDoubleInfo(const string& info_name);
    virtual const HepLorentzVector& GetLorentzVector(const string& info_name);
    virtual void GetInfoD(const std::string& info_name, double& targe);
    virtual void GetInfoH(const std::string& info_name, HepLorentzVector& targe);
    const double& Mass();
    const double& Chisq();
    const double& Angle();
    const double& OpenAngle();
    const double& Helicity();
    const HepLorentzVector& P4();
    const HepLorentzVector& p41C();
    const HepLorentzVector& p41c() { return this->p41C(); }
    const HepLorentzVector& P4Child(const int& i);
    const HepLorentzVector& P4GammaHigh();
    const HepLorentzVector& P4GammaLow();
    const bool& isGood();
    const WTrackParameter& WTrk();
    // for compatiable
    const double& m() { return this->Mass(); }
    const double& chisq() { return this->Chisq(); }
    // ...

    virtual bool Calculate();
    virtual bool isGoodPhoton(EvtRecTrack*);
    void SetWTrackParameter(const WTrackParameter& wtrk);
    void SetRawMass(const double& mass);
    void SetHelicity(const double& helicity);
    void SetHelicityAngle(const double& helicityAngle);
    void SetOpenAngle(const double& openangle);
    void SetChisq(const double& chisq);
    void SetP41C(const HepLorentzVector& p4);
    void SetRawP4(const HepLorentzVector& p4);
    void SetP4Child(const HepLorentzVector& p4, const int& i);

   private:
    WTrackParameter m_wtrk;
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
    void AddAvialInfo();
};
#endif
