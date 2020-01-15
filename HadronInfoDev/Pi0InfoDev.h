#ifndef CLASS_Pi0INFODev_H
#define CLASS_Pi0INFODev_H

#include "EvtRecEvent/EvtRecTrack.h"

#include "CLHEP/Vector/LorentzVector.h"
#include "VertexFit/KalmanKinematicFit.h"
#include "BesDChain/CDDecay.h"
#include "HadronInfoDev/AvailableInfoDev.h"
#include "HadronInfoDev/GGInfoDev.h"

#include <iostream>

using namespace std;
class Pi0InfoDev : public GGInfoDev {
   public:
    Pi0InfoDev();
    Pi0InfoDev(const EvtRecTrack *, const EvtRecTrack *);
    Pi0InfoDev(vector<const EvtRecTrack *>);
    Pi0InfoDev(const CDCandidate &);
    ~Pi0InfoDev();
    virtual bool calculate();
    virtual bool isGoodPhoton(EvtRecTrack *);
    virtual const string GetName() { return "Pi0"; }
    // virtual const double& GetDoubleInfoDev(const string &);
    // virtual const HepLorentzVector& GetLorentzVector(const string
    // &info_name);
    void setchild(const int &, const EvtRecTrack *);
    void setchilds(const EvtRecTrack *, const EvtRecTrack *);
    EvtRecTrack *getchild(const int &i);
    // double m();
    // double m1c();
    // double angle();
    // double openAngle();
    // double helicity();
    // HepLorentzVector p4();
    // HepLorentzVector p41c();
    // HepLorentzVector p4child(const int &);
    // double chisq();
    // bool isGoodPi0();
    // WTrackParameter wtrk();
    // Pi0InfoDev &operator=(Pi0InfoDev &aPi0InfoDev);

   private:
    EvtRecTrack *m_shower[2];
    WTrackParameter m_wtrk;
    bool m_calculate, m_isgoodpi0;
    // HepLorentzVector m_p4;
    // HepLorentzVector m_p41c;
    // double Pi0InfoDev_mpi0;
    // double m_mpi0;
    // double m_mpi01c;
    // double m_pi0_heliAngle;
    // double m_helicity;
    // double m_openAngle;
    // double m_chisq;
};
#endif
