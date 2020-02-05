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

class TrackInfo : virtual public AvailableInfo {
   public:
    TrackInfo();
    TrackInfo(const int &);
    TrackInfo(const EvtRecTrack *);
    TrackInfo(const CDCandidate &aTrk);
    void Feed(const EvtRecTrack *);
    void Feed(const CDCandidate &aTrk);
    ~TrackInfo();

    const int Charge() { return m_track->mdcKalTrack()->charge(); }
    void GetInfo(const std::string &info_name, double &targe) {
        if (info_name == "Rxy") {
            targe = this->m_Rxy;
            return;
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
    void GetInfo(const std::string &info_name,
                         HepLorentzVector &targe) {
        if (info_name == "p4") {
            targe = this->P4();
            return;
        }
    }

    virtual const bool DoVertexFit() { return false; }

    void SetPrimaryVertex(VertexParameter &vpar) {}

    void SetTrack(const int &parId, const EvtRecTrack *);
    void SetTrack(const EvtRecTrack *);
    // TrackInfo &operator=(TrackInfo &aTrackInfo);

    void SetPID(const int &pid) { m_parId = pid; }
    HepLorentzVector P4();
    HepLorentzVector P4(const int &PID);
    HepLorentzVector P4(EvtRecTrack *, const int &);
    HepLorentzVector P4c(const EvtRecTrack *, const int &);
    WTrackParameter WTrk(EvtRecTrack *, const int &);
    WTrackParameter WTrk(const int &PID);
    WTrackParameter WTrk();
    WTrackParameter WTrkc(const EvtRecTrack *, const int &);
    const HepPoint3D &GetIP();
    void UpdateWTrk(const WTrackParameter &newWtrk);

   private:
    bool m_cal;
    bool m_updateWTrk;
    void Calculate();
    EvtRecTrack *m_track;
    WTrackParameter m_wtrk;
    int m_parId;
    double m_Rxy, m_Rz, m_costheta;
    HepLorentzVector m_p4;
    double m_mass;
    void AddAvialInfo() {
        AvailableInfo::Add("Rxy", "double");
        AvailableInfo::Add("Rz", "double");
        AvailableInfo::Add("CosTheta", "double");
        AvailableInfo::Add("p4", "HepLorentzVector");
    }
};
#endif
