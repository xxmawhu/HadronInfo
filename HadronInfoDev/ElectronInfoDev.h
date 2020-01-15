/* ====================================================
#   Copyright (C)2019 All rights reserved.
#
#   Author        : Xin-Xin MA
#   Email         : xxmawhu@163.com
#   File Name     : ElectronInfoDev.h
#   Create Time   : 2019-12-09 19:19
#   Last Modified : 2019-12-12 13:29
#   Describe      :
#
# ====================================================*/

#ifndef CLASS_HadronInfoDev_ElectronInfoDev_H
#define CLASS_HadronInfoDev_ElectronInfoDev_H

#include "EvtRecEvent/EvtRecTrack.h"

#include "CLHEP/Vector/LorentzVector.h"
#include "VertexFit/WTrackParameter.h"
#include "MdcRecEvent/RecMdcKalTrack.h"

#include "BesDChain/CDDecay.h"
#include "HadronInfoDev/TrackInfoDev.h"
#include <iostream>

using namespace std;
class ElectronInfoDev : public TrackInfoDev {
   public:
    ElectronInfoDev() : TrackInfoDev(11) {};
    ElectronInfoDev(const EvtRecTrack* aTrack) : TrackInfoDev(aTrack) { setPID(11); }
    ElectronInfoDev(const CDCandidate& aTrk) : TrackInfoDev(aTrk) { setPID(11); }
    ~ElectronInfoDev() {};

    virtual const string GetName() { return "Electron"; }
};
#endif
