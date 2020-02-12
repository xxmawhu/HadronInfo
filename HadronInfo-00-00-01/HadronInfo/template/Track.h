/* ====================================================
#   Copyright (C)2020 All rights reserved.
#
#   Author        : Xin-Xin MA
#   Email         : xxmawhu@163.com
#   File Name     : Track.h
#   Create Time   : 2020-02-10 15:57
#   Last Modified : 2020-02-10 15:57
#   Describe      :
#
# ====================================================*/
#ifndef HadronInfo_TRACK_H
#define HadronInfo_TRACK_H
#include "EvtRecEvent/EvtRecTrack.h"
#include "GaudiKernel/Bootstrap.h"
#include "VertexFit/IVertexDbSvc.h"

#include "CLHEP/Vector/LorentzVector.h"
#include "VertexFit/Helix.h"
#include "VertexFit/IVertexDbSvc.h"
#include "VertexFit/WTrackParameter.h"
#include "VertexFit/VertexFit.h"
#include "MdcRecEvent/RecMdcKalTrack.h"

#include "BesDChain/CDDecay.h"
#include "HadronInfo/AvailableInfo.h"
#include "HadronInfo/util.h"
#include <iostream>
// electron = 0,
// muon = 1,
// pion = 2,
// kaon = 3,
// proton = 4
template <int pid>
class Track : virtual public AvailableInfo {
   public:
    Track();
    Track(const int &);
    Track(const EvtRecTrack *);
    Track(const CDCandidate &aTrk);
    void Feed(const EvtRecTrack *);
    void Feed(const CDCandidate &aTrk);
    ~Track();
    const int Charge();
    virtual void GetInfoD(const std::string&, double &);
    virtual void GetInfoH(const std::string&, HepLorentzVector&);

    virtual const bool DoVertexFit() { return false; }

    void SetPrimaryVertex(VertexParameter &vpar) {}

    void SetTrack(const int &parId, const EvtRecTrack *);
    void SetTrack(const EvtRecTrack *);
    // TrackInfo &operator=(TrackInfo &aTrackInfo);

    double GetRxy();
    double GetRz();
    double GetCosTheta();
    HepLorentzVector P4();
    WTrackParameter WTrk();
    void UpdateWTrk(const WTrackParameter &newWtrk);

   private:
    HepPoint3D GetIP();
    bool m_calculate;
    bool m_updateWTrk;
    void Calculate();
    EvtRecTrack *m_track;
    WTrackParameter m_wtrk;
    int m_PID;
    double m_Rxy, m_Rz, m_costheta;
    HepLorentzVector m_p4;
    double m_mass;
    void AddAvialInfo();
};
#include "Track.cpp"
#endif
