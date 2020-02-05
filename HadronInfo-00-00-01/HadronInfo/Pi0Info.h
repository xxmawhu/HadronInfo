#ifndef CLASS_Pi0Info_H
#define CLASS_Pi0Info_H

#include "EvtRecEvent/EvtRecTrack.h"

#include "CLHEP/Vector/LorentzVector.h"
#include "VertexFit/KalmanKinematicFit.h"
#include "BesDChain/CDDecay.h"
#include "HadronInfo/AvailableInfo.h"
#include "HadronInfo/GGInfo.h"

#include <iostream>

class Pi0Info : public GGInfo {
   public:
    Pi0Info();
    Pi0Info(const EvtRecTrack *, const EvtRecTrack *);
    Pi0Info(vector<const EvtRecTrack *>);
    Pi0Info(const CDCandidate &);
    void Feed(const EvtRecTrack *, const EvtRecTrack *);
    void Feed(vector<const EvtRecTrack *>);
    void Feed(const CDCandidate &);
    ~Pi0Info();
    virtual bool Calculate();
    virtual bool isGoodPhoton(EvtRecTrack *);
    // virtual const double& GetDoubleInfo(const string &);
    // virtual const HepLorentzVector& GetLorentzVector(const string
    // &info_name);
    void SetChild(const int &, const EvtRecTrack *);
    void SetChildren(const EvtRecTrack *, const EvtRecTrack *);
    EvtRecTrack *GetChild(const int &i);
    // double m();
    // double m1c();
    // double Angle();
    // double openAngle();
    // double Helicity();
    // HepLorentzVector P4();
    // HepLorentzVector p41c();
    // HepLorentzVector P4Child(const int &);
    // double chisq();
    // bool isGoodPi0();
    // WTrackParameter WTrk();
    // Pi0Info &operator=(Pi0Info &aPi0Info);

   private:
    EvtRecTrack *m_shower[2];
    WTrackParameter m_wtrk;
    bool m_calculate, m_isgoodpi0;
    // HepLorentzVector m_p4;
    // HepLorentzVector m_p41c;
    // double Pi0Info_mpi0;
    // double m_mpi0;
    // double m_mpi01c;
    // double m_pi0_heliAngle;
    // double m_helicity;
    // double m_openAngle;
    // double m_chisq;
};
#endif
