/* ====================================================
#   Copyright (C)2019 All rights reserved.
#
#   Author        : Xin-Xin MA
#   Email         : xxmawhu@163.com
#   File Name     : KaonInfo.h
#   Create Time   : 2019-12-09 19:19
#   Last Modified : 2019-12-12 13:29
#   Describe      :
#
# ====================================================*/

#ifndef CLASS_HadronInfo_KaonInfo_H
#define CLASS_HadronInfo_KaonInfo_H

#include "EvtRecEvent/EvtRecTrack.h"

#include "CLHEP/Vector/LorentzVector.h"
#include "VertexFit/WTrackParameter.h"
#include "MdcRecEvent/RecMdcKalTrack.h"

#include "BesDChain/CDDecay.h"
#include "HadronInfo/TrackInfo.h"
#include <iostream>

using namespace std;
class KaonInfo : public TrackInfo, virtual public AvailableInfo {
   public:
    KaonInfo() : TrackInfo(321) { SetName("Kaon"); }
    KaonInfo(const EvtRecTrack* aTrack) : TrackInfo(aTrack) {
        SetPID(321);
        SetName("Kaon");
    }
    KaonInfo(const CDCandidate& aTrk) : TrackInfo(aTrk) {
        SetPID(321);
        SetName("Kaon");
    }
    ~KaonInfo() {};
};
#endif
