/* ====================================================
#   Copyright (C)2019 All rights reserved.
#
#   Author        : Xin-Xin MA
#   Email         : xxmawhu@163.com
#   File Name     : ElectronInfo.h
#   Create Time   : 2019-12-09 19:19
#   Last Modified : 2019-12-12 13:29
#   Describe      :
#
# ====================================================*/

#ifndef CLASS_HadronInfo_ElectronInfo_H
#define CLASS_HadronInfo_ElectronInfo_H

#include "EvtRecEvent/EvtRecTrack.h"

#include "CLHEP/Vector/LorentzVector.h"
#include "VertexFit/WTrackParameter.h"
#include "MdcRecEvent/RecMdcKalTrack.h"

#include "BesDChain/CDDecay.h"
#include "HadronInfo/TrackInfo.h"
#include <iostream>

using namespace std;
class ElectronInfo : public TrackInfo {
   public:
    ElectronInfo() : TrackInfo(11) { SetName("Electron"); }
    ElectronInfo(const EvtRecTrack* aTrack) : TrackInfo(aTrack) {
        SetPID(11);
        SetName("Electron");
    }
    ElectronInfo(const CDCandidate& aTrk) : TrackInfo(aTrk) {
        SetPID(11);
        SetName("Electron");
    }
    ~ElectronInfo() {};
};
#endif
