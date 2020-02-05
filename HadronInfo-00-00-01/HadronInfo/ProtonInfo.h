/* ====================================================
#   Copyright (C)2019 All rights reserved.
#
#   Author        : Xin-Xin MA
#   Email         : xxmawhu@163.com
#   File Name     : ProtonInfo.h
#   Create Time   : 2019-12-09 19:19
#   Last Modified : 2019-12-12 13:28
#   Describe      :
#
# ====================================================*/

#ifndef CLASS_HadronInfo_ProtonnInfo_H
#define CLASS_HadronInfo_ProtonnInfo_H

#include "EvtRecEvent/EvtRecTrack.h"

#include "CLHEP/Vector/LorentzVector.h"
#include "VertexFit/WTrackParameter.h"
#include "MdcRecEvent/RecMdcKalTrack.h"

#include "BesDChain/CDDecay.h"
#include "HadronInfo/TrackInfo.h"
#include <iostream>

class ProtonInfo : public TrackInfo {
   public:
    ProtonInfo() : TrackInfo(2212) { SetName("Proton"); }
    ProtonInfo(const EvtRecTrack* aTrack) : TrackInfo(aTrack) {
        SetPID(2212);
        SetName("Proton");
    }
    ProtonInfo(const CDCandidate& aTrk) : TrackInfo(aTrk) {
        SetPID(2212);
        SetName("Proton");
    }
    ~ProtonInfo() {};
};
#endif
