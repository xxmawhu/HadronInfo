#ifndef CLASS_Pi0INFO_H
#define CLASS_Pi0INFO_H

#include "EvtRecEvent/EvtRecTrack.h"

#include "CLHEP/Vector/LorentzVector.h"
#include "VertexFit/KalmanKinematicFit.h"
#include "BesDChain/CDDecay.h"
#include "HadronInfo/AvailableInfo.h"
#include "HadronInfo/GGInfo.h"

#include <iostream>

using namespace std;
class Pi0Info : public GGInfo {
   public:
    Pi0Info();
    Pi0Info(const EvtRecTrack *, const EvtRecTrack *);
    Pi0Info(vector<const EvtRecTrack *>);
    Pi0Info(const CDCandidate &);
    ~Pi0Info();
    virtual bool calculate();
    virtual const double& GetDoubleInfo(const string &);
    virtual const HepLorentzVector& GetLorentzVector(const string &info_name);
   void setchild(const int&, const EvtRecTrack *);
   void setchilds(const EvtRecTrack *, const EvtRecTrack *);
    EvtRecTrack *getchild(const int& i);
 virtual bool isGoodPhoton(EvtRecTrack *);
   //double m();
   //double m1c();
   //double angle();
   //double openAngle();
   //double helicity();
   //HepLorentzVector p4();
   //HepLorentzVector p41c();
   //HepLorentzVector p4child(const int &);
  // double chisq();
  // bool isGoodPi0();
  // WTrackParameter wtrk();
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
