#ifndef CLASS_EtaInfo_H
#define CLASS_EtaInfo_H

#include "EvtRecEvent/EvtRecTrack.h"

#include "CLHEP/Vector/LorentzVector.h"
#include "VertexFit/KalmanKinematicFit.h"
#include "BesDChain/CDDecay.h"
#include "HadronInfo/AvailableInfo.h"
#include "HadronInfo/GGInfo.h"

#include <iostream>

using namespace std;
class EtaInfo : public GGInfo {
   public:
    EtaInfo();
    EtaInfo(const EvtRecTrack *, const EvtRecTrack *);
    EtaInfo(vector<const EvtRecTrack *>);
    EtaInfo(const CDCandidate &);
    void Feed(const EvtRecTrack *, const EvtRecTrack *);
    void Feed(vector<const EvtRecTrack *>);
    void Feed(const CDCandidate &);
    ~EtaInfo();
    virtual bool Calculate();
    // virtual bool isGoodPhoton(EvtRecTrack *);
    //  virtual const double& GetDoubleInfo(const string &);
    //  virtual const HepLorentzVector& GetLorentzVector(const string
    // &info_name);
    void SetChild(const int &, const EvtRecTrack *);
    void SetChildren(const EvtRecTrack *, const EvtRecTrack *);
    EvtRecTrack *GetChild(const int &i);

   private:
    EvtRecTrack *m_shower[2];
    WTrackParameter m_wtrk;
    bool m_calculate, m_isgoodeta;
};
#endif
