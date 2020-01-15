#include "HadronInfoDev/DTagFunc.h"
#include "EvtRecEvent/EvtRecDTag.h"
#include "EvtRecEvent/EvtRecTrack.h"
#include "BesDChain/CDCandidate.h"

bool DTagFunc::overlap(EvtRecDTag &tag_D, const CDCandidate &sig) {
    SmartRefVector<EvtRecTrack> tag_tracks = tag_D.tracks();
    SmartRefVector<EvtRecTrack> tag_showers = tag_D.showers();
    vector<const EvtRecTrack *> sig_tracks = sig.finalChildren().first;
    vector<const EvtRecTrack *> sig_showers = sig.finalChildren().second;
    for (int i = 0; i < tag_tracks.size(); i++) {
        for (int j = 0; j < sig_tracks.size(); j++) {
            EvtRecTrack *tag_trk = tag_tracks[i];
            EvtRecTrack *sig_trk = const_cast<EvtRecTrack *>(sig_tracks[j]);
            if (tag_trk->trackId() == sig_trk->trackId()) {
                return true;
            }
        }
    }

    for (int i = 0; i < tag_showers.size(); i++) {
        for (int j = 0; j < sig_showers.size(); j++) {
            EvtRecTrack *tag_trk = tag_showers[i];
            EvtRecTrack *sig_trk = const_cast<EvtRecTrack *>(sig_showers[j]);
            if (tag_trk->trackId() == sig_trk->trackId()) {
                return true;
            }
        }
    }
    return false;
}
