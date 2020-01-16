/* ====================================================
#   Copyright (C)2019 All rights reserved.
#
#   Author        : Xin-Xin MA
#   Email         : xxmawhu@163.com
#   File Name     : TrackInfoDev.h
#   Create Time   : 2019-12-09 19:19
#   Last Modified : 2019-12-09 19:19
#   Describe      :
#
# ====================================================*/

#ifndef CLASS_HadronInfoDev_TrackINFODev_H
#define CLASS_HadronInfoDev_TrackINFODev_H

#include "EvtRecEvent/EvtRecTrack.h"

#include "CLHEP/Vector/LorentzVector.h"
#include "VertexFit/WTrackParameter.h"
#include "MdcRecEvent/RecMdcKalTrack.h"

#include "BesDChain/CDDecay.h"
#include "HadronInfoDev/AvailableInfoDev.h"
#include <iostream>

using namespace std;
class TrackInfoDev : public AvailableInfoDev {
   public:
    TrackInfoDev();
    TrackInfoDev(const int &);
    TrackInfoDev(const EvtRecTrack *);
    TrackInfoDev(const CDCandidate &aTrk);
    ~TrackInfoDev();

    inline const int Charge() {
        return m_track->mdcKalTrack()->charge();
    }
    virtual const string GetName() { return "ChargedTrack"; }
    virtual const double &GetDoubleInfoDev(const string &);
    virtual const HepLorentzVector &GetLorentzVector(const string &info_name);

    void SetTrack(const int &parId, const EvtRecTrack *);
    void SetTrack(const EvtRecTrack *);
    // TrackInfoDev &operator=(TrackInfoDev &aTrackInfoDev);

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

   private:
    void calculate();
    EvtRecTrack *m_track;
    WTrackParameter m_wtrk;
    int m_parId;
    double m_Rxy, m_Rz, m_costheta;
    HepLorentzVector m_p4;
    void addAvialInfoDev() {
        AvailableInfoDev::add("Rxy", "double");
        AvailableInfoDev::add("Rz", "double");
        AvailableInfoDev::add("CosTheta", "double");
        AvailableInfoDev::add("p4", "HepLorentzVector");
    }
};
#endif
