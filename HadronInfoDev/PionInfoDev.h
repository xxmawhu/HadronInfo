/* ====================================================
#   Copyright (C)2019 All rights reserved.
#
#   Author        : Xin-Xin MA
#   Email         : xxmawhu@163.com
#   File Name     : PionInfoDev.h
#   Create Time   : 2019-12-09 19:19
#   Last Modified : 2019-12-12 13:31
#   Describe      :
#
# ====================================================*/

#ifndef CLASS_HadronInfoDev_PionInfoDev_H
#define CLASS_HadronInfoDev_PionInfoDev_H

#include "EvtRecEvent/EvtRecTrack.h"

#include "CLHEP/Vector/LorentzVector.h"
#include "VertexFit/WTrackParameter.h"
#include "MdcRecEvent/RecMdcKalTrack.h"

#include "BesDChain/CDDecay.h"
#include "HadronInfoDev/TrackInfoDev.h"
#include <iostream>
#include <string>

using namespace std;
class PionInfoDev : public TrackInfoDev {
   public:
    PionInfoDev() : TrackInfoDev(211) {
        cout << "TrackInfoDev::GetName()" << TrackInfoDev::GetName() << endl;
        cout << "PionInfoDev::GetName()" << GetName() << endl;
    }
    PionInfoDev(const EvtRecTrack* aTrack) : TrackInfoDev(aTrack) { setPID(211); }
    PionInfoDev(const CDCandidate& aTrk) : TrackInfoDev(aTrk) { setPID(211); }
    ~PionInfoDev() {};

    virtual const string GetName() { return "Pion"; }
};
#endif
