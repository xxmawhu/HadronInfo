/* ====================================================
#   Copyright (C)2019 All rights reserved.
#
#   Author        : Xin-Xin MA
#   Email         : xxmawhu@163.com
#   File Name     : CombInfo.h
#   Create Time   : 2019-12-11 10:37
#   Last Modified : 2019-12-12 12:33
#   Describe      :
# get the combinate information of two particles, three particles
# for example, (pi0, pi0), (pi+, pi-, eta)
# ====================================================*/
#ifndef HadronInfo_COMBInfo_H
#define HadronInfo_COMBInfo_H
// #include "TupleSvc/DecayTree.h"
#include "GaudiKernel/Bootstrap.h"
#include "VertexFit/VertexFit.h"
#include "VertexFit/SecondVertexFit.h"
#include "VertexFit/IVertexDbSvc.h"
#include "CLHEP/Vector/LorentzVector.h"
#include "BesDChain/CDCandidate.h"
#include "BesDChain/CDDecay.h"
#include "HadronInfo/AvailableInfo.h"
#include "HadronInfo/util.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
using CLHEP::HepLorentzVector;
using std::string;
using std::cout;
using std::endl;
template <class FirstInfo, class SecondInfo, int pid = 0, int doVertexFit = 0>
class CombInfo : virtual public AvailableInfo {
   public:
    CombInfo() ;
    CombInfo(const CDCandidate& combParticle) ;
    CombInfo(FirstInfo& firsInfo, SecondInfo& secondInfo) ;
    void Feed(const CDCandidate& combParticle) ;
    void Feed(FirstInfo& firsInfo, SecondInfo& secondInfo) ;
    virtual const bool DoVertexFit();
    int Charge();
    virtual void GetInfoI(const std::string& info_name, int& targe) ;

    virtual void GetInfoD(const std::string& info_name, double& targe) ;
    virtual void GetInfoH(const std::string& info_name,
                          HepLorentzVector& targe) ;
    virtual void GetInfoVi(const std::string& info_name,
                           std::vector<int>& targe) ;
    virtual void GetInfoVd(const std::string& info_name,
                           std::vector<double>& targe) ;
    virtual bool Calculate();
    void UpdateWTrk(const WTrackParameter& newWtrk) ;
    const WTrackParameter& WTrk() ;
    const HepLorentzVector& P4() ;
    const HepLorentzVector& RawP4() ;
    const HepLorentzVector& P4Child(const int& i);
    const double& Mass();
    const double& RawMass();
    void SetP4(const HepLorentzVector& p4);
    const double& DecayLength();
    const double& DecayLengthError();
    double DecayLengthRatio();
    const double& VertexFitChisq();
    const double& SecondVertexFitChisq();
    // for compatiable
    const double& m() { return this->Mass(); }
    const double& chi2() { return this->SecondVertexFitChisq(); }
    const double& vtxChi2() { return this->VertexFitChisq(); }
    const double& chisq() { return this->VertexFitChisq(); }
    // ...
    void SetPrimaryVertex(VertexParameter& privtxpar);
    std::pair<FirstInfo, SecondInfo>& Decay();

   private:
    bool m_calculate, m_isSetPriVtx;
    int m_pid;
    HepLorentzVector m_p4, m_rawp4;
    HepLorentzVector m_p4Child[2];
    double m_mass, m_rawMass;
    double m_decayLength, m_decayLError;
    double m_vertexFitChisq, m_secondVertexFitChisq;
    FirstInfo m_firstInfo;
    SecondInfo m_secondInfo;
    WTrackParameter m_wVirtualTrack;
    VertexParameter m_vpar;
    VertexParameter m_privtxpar;
    void AddInfo(const vector<string>& allInfo,
                 const std::map<string, string>& allindexInfo,
                 const std::map<string, int>& allLengthInfo, const string& type,
                 const string& name);
    template <class T>
    void AddInfo(T aInfo) {
        this->AddInfo(aInfo.GetType("int"), aInfo.GetAllIndexInfo(),
                      aInfo.GetAllLengthInfo(), "int", aInfo.GetName());
        this->AddInfo(aInfo.GetType("double"), aInfo.GetAllIndexInfo(),
                      aInfo.GetAllLengthInfo(), "double", aInfo.GetName());
        this->AddInfo(aInfo.GetType("HepLorentzVector"),
                      aInfo.GetAllIndexInfo(), aInfo.GetAllLengthInfo(),
                      "HepLorentzVector", aInfo.GetName());
    }
    void AddAvialInfo();
};
#include "CombInfo.cpp"
#endif
