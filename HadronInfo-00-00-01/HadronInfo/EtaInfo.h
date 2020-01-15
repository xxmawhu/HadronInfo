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
    ~EtaInfo();
    virtual bool calculate();
    // virtual bool isGoodPhoton(EvtRecTrack *);
    //  virtual const double& GetDoubleInfo(const string &);
    //  virtual const HepLorentzVector& GetLorentzVector(const string
    // &info_name);
    virtual const string GetName() { return "Eta"; }
    void setchild(const int &, const EvtRecTrack *);
    void setchilds(const EvtRecTrack *, const EvtRecTrack *);
    EvtRecTrack *getchild(const int &i);

   private:
    EvtRecTrack *m_shower[2];
    WTrackParameter m_wtrk;
    bool m_calculate, m_isgoodeta;
};
#endif
