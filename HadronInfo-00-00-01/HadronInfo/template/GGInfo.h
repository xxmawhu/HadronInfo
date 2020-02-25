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
#include "VertexFit/VertexFit.h"

#include "CLHEP/Vector/LorentzVector.h"
#include "VertexFit/KalmanKinematicFit.h"
#include "BesDChain/CDDecay.h"
#include "HadronInfo/AvailableInfo.h"
#include "HadronInfo/util.h"
#include "HadronInfo/ShowerInfo.h"
#include "HadronInfo/util.h"
#include <iostream>
#include <string>
// pi0 111
// eta 221
template <int pid = 111>
class GGInfo : virtual public AvailableInfo {
   public:
    GGInfo();
    GGInfo(const EvtRecTrack* trk1, const EvtRecTrack* trk2);
    GGInfo(vector<const EvtRecTrack*> trks);
    GGInfo(const CDCandidate& sig);
    void Feed(const EvtRecTrack*, const EvtRecTrack*);
    void Feed(vector<const EvtRecTrack*>);
    void Feed(const CDCandidate&);
    ~GGInfo() {
    };
    int Charge();
    virtual void GetInfoD(const std::string&, double&);
    virtual void GetInfoH(const std::string&, HepLorentzVector&);
    const double& Mass();
    const double& Chisq();
    const double& Angle();
    const double& OpenAngle();
    const double& Helicity();
    void SetChild(const int&, const EvtRecTrack*);
    EvtRecTrack* GetChild(const int& n) { return m_shower[n]; }
    const HepLorentzVector& P4();
    const HepLorentzVector& p41C();
    const HepLorentzVector& P4Child(const int& i);
    const HepLorentzVector& P4GammaHigh();
    const HepLorentzVector& P4GammaLow();
    virtual bool Calculate();
    virtual const bool DoVertexFit() { return false; }
    const WTrackParameter& WTrk();
    void UpdateWTrk(const WTrackParameter& newWtrk);
    void SetPrimaryVertex(VertexParameter& vpar) {};
    // for compatiable
    const double& m() { return this->Mass(); }
    const double& chisq() { return this->Chisq(); }
    // ...
   private:
    EvtRecTrack* m_shower[2];
    WTrackParameter m_wtrk;
    double m_massPDG, m_rawMass;
    int m_PID;
    bool m_calculate, m_isgoodeta;
    bool m_updateWTrk;
    HepLorentzVector m_rawP4;
    HepLorentzVector m_P41C;
    HepLorentzVector m_rawP4Child[2];
    double m_mpi0;
    double m_mpi01c;
    double m_angle;
    double m_helicity;
    double m_openAngle, m_helicityAngle;
    double m_chisq;
    void AddAvialInfo();
};
#include "GGInfo.cpp"
#endif
