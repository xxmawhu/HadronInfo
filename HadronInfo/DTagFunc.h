#ifndef CLASS_DTagFunc_H
#define CLASS_DTagFunc_H

#include "EvtRecEvent/EvtRecTrack.h"

#include "CLHEP/Vector/LorentzVector.h"
#include "VertexFit/WTrackParameter.h"
#include "MdcRecEvent/RecMdcKalTrack.h"
#include "EvtRecEvent/EvtRecDTag.h"
#include "EvtRecEvent/EvtRecTrack.h"
#include "BesDChain/CDCandidate.h"

#include <iostream>

namespace DTagFunc {
bool overlap(EvtRecDTag &tag_D, const CDCandidate &sig);
}
#endif
