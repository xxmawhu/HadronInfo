/* ====================================================
#   Copyright (C)2019 All rights reserved.
#
#   Author        : Xin-Xin MA
#   Email         : xxmawhu@163.com
#   File Name     : PionInfo.h
#   Create Time   : 2019-12-09 19:19
#   Last Modified : 2019-12-12 13:31
#   Describe      :
#
# ====================================================*/

#ifndef CLASS_HadronInfo_PionInfo_H
#define CLASS_HadronInfo_PionInfo_H

#include "EvtRecEvent/EvtRecTrack.h"

#include "CLHEP/Vector/LorentzVector.h"
#include "VertexFit/WTrackParameter.h"
#include "MdcRecEvent/RecMdcKalTrack.h"

#include "BesDChain/CDDecay.h"
#include "HadronInfo/TrackInfo.h"
#include <iostream>
#include <string>

using namespace std;
class PionInfo : public TrackInfo {
   public:
    PionInfo() : TrackInfo(211) {
        cout << "TrackInfo::GetName()" << TrackInfo::GetName() << endl;
        cout << "PionInfo::GetName()" << GetName() << endl;
    }
    PionInfo(const EvtRecTrack* aTrack) : TrackInfo(aTrack) { setPID(211); }
    PionInfo(const CDCandidate& aTrk) : TrackInfo(aTrk) { setPID(211); }
    ~PionInfo() {};

    virtual const string GetName() { return "Pion"; }
};
#endif
