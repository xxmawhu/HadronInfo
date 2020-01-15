#ifndef CLASS_EtaINFODev_H
#define CLASS_EtaINFODev_H

#include "EvtRecEvent/EvtRecTrack.h"

#include "CLHEP/Vector/LorentzVector.h"
#include "VertexFit/KalmanKinematicFit.h"
#include "BesDChain/CDDecay.h"
#include "HadronInfoDev/AvailableInfoDev.h"
#include "HadronInfoDev/GGInfoDev.h"

#include <iostream>

using namespace std;
class EtaInfoDev : public GGInfoDev {
   public:
    EtaInfoDev();
    EtaInfoDev(const EvtRecTrack *, const EvtRecTrack *);
    EtaInfoDev(vector<const EvtRecTrack *>);
    EtaInfoDev(const CDCandidate &);
    ~EtaInfoDev();
    virtual bool calculate();
    // virtual bool isGoodPhoton(EvtRecTrack *);
    //  virtual const double& GetDoubleInfoDev(const string &);
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
