/* ====================================================
#   Copyright (C)2019 All rights reserved.
#
#   Author        : Xin-Xin MA
#   Email         : xxmawhu@163.com
#   File Name     : ProtonInfoDev.h
#   Create Time   : 2019-12-09 19:19
#   Last Modified : 2019-12-12 13:28
#   Describe      :
#
# ====================================================*/

#ifndef CLASS_HadronInfoDev_ProtonnInfoDev_H
#define CLASS_HadronInfoDev_ProtonnInfoDev_H

#include "EvtRecEvent/EvtRecTrack.h"

#include "CLHEP/Vector/LorentzVector.h"
#include "VertexFit/WTrackParameter.h"
#include "MdcRecEvent/RecMdcKalTrack.h"

#include "BesDChain/CDDecay.h"
#include "HadronInfoDev/TrackInfoDev.h"
#include <iostream>

using namespace std;
class ProtonInfoDev : public TrackInfoDev {
   public:
    ProtonInfoDev() : TrackInfoDev(2212) {};
    ProtonInfoDev(const EvtRecTrack* aTrack) : TrackInfoDev(aTrack) { setPID(2212); }
    ProtonInfoDev(const CDCandidate& aTrk) : TrackInfoDev(aTrk) { setPID(2212); }
    ~ProtonInfoDev() {};

    virtual const string GetName() { return "Proton"; }
};
#endif
