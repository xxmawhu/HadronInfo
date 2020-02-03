/* ====================================================
#   Copyright (C)2019 All rights reserved.
#
#   Author        : Xin-Xin MA
#   Email         : xxmawhu@163.com
#   File Name     : TrackInfo.h
#   Create Time   : 2019-12-09 19:19
#   Last Modified : 2019-12-09 19:19
#   Describe      :
#
# ====================================================*/

#ifndef CLASS_HadronInfo_TrackInfo_H
#define CLASS_HadronInfo_TrackInfo_H

#include "EvtRecEvent/EvtRecTrack.h"

#include "CLHEP/Vector/LorentzVector.h"
#include "VertexFit/WTrackParameter.h"
#include "MdcRecEvent/RecMdcKalTrack.h"

#include "BesDChain/CDDecay.h"
#include "HadronInfo/AvailableInfo.h"
#include "VertexFit/VertexFit.h"
#include <iostream>

using namespace std;
class TrackInfo : public AvailableInfo {
   public:
    TrackInfo();
    TrackInfo(const int &);
    TrackInfo(const EvtRecTrack *);
    TrackInfo(const CDCandidate &aTrk);
    void Feed(const EvtRecTrack *);
    void Feed(const CDCandidate &aTrk);
    ~TrackInfo();

    const int Charge() { return m_track->mdcKalTrack()->charge(); }
    // virtual const double &GetDoubleInfo(const string &);
    // virtual const HepLorentzVector &GetLorentzVector(const string &info_name);
    virtual void GetInfo(const std::string&info_name, double& targe){
        if (info_name == "Rxy") {
            targe = this->m_Rxy;
            return ; 
        }
        if (info_name == "Rz") {
            targe = this->m_Rz;
            return; 
        }
        if (info_name == "CosTheta") {
            targe = this->m_costheta;
            return; 
        }
    }
    virtual void GetInfo(const std::string&info_name, HepLorentzVector& targe){
        if (info_name == "p4") {
            targe = this->p4();
            return; 
        }
    }

    virtual const bool DoVertexFit() {
        return false;
    } 

    void setPrimaryVertex(VertexParameter& vpar) {
    }

    void SetTrack(const int &parId, const EvtRecTrack *);
    void SetTrack(const EvtRecTrack *);
    // TrackInfo &operator=(TrackInfo &aTrackInfo);

    void setPID(const int &pid) { m_parId = pid; }
    HepLorentzVector p4();
    HepLorentzVector p4(const int &PID);
    HepLorentzVector p4(EvtRecTrack *, const int &);
    HepLorentzVector p4c(const EvtRecTrack *, const int &);
    WTrackParameter wtrk(EvtRecTrack *, const int &);
    WTrackParameter wtrk(const int &PID);
    WTrackParameter wtrk();
    WTrackParameter wtrkc(const EvtRecTrack *, const int &);
    const HepPoint3D &getIP();
    void updateWTrk(const WTrackParameter& newWtrk);

   private:
    bool m_cal;
    bool m_updateWTrk;
    void calculate();
    EvtRecTrack *m_track;
    WTrackParameter m_wtrk;
    int m_parId;
    double m_Rxy, m_Rz, m_costheta;
    HepLorentzVector m_p4;
    double m_mass;
    void addAvialInfo() {
        AvailableInfo::add("Rxy", "double");
        AvailableInfo::add("Rz", "double");
        AvailableInfo::add("CosTheta", "double");
        AvailableInfo::add("p4", "HepLorentzVector");
    }
};
#endif
