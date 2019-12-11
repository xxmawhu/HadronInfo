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
    Pi0Info(EvtRecTrack *, EvtRecTrack *);
    Pi0Info(vector<const EvtRecTrack *>);
    Pi0Info(const CDCandidate &);

    ~Pi0Info();
    virtual double GetDoubleInfo(const string &);
    virtual HepLorentzVector GetLorentzVector(const string &info_name);
    void setchild(int, EvtRecTrack *);
    void setchilds(EvtRecTrack *, EvtRecTrack *);
    EvtRecTrack *getchild(int n);
    double m();
    double m1c();
    double angle();
    double openAngle();
    double helicity();
    HepLorentzVector p4();
    HepLorentzVector p41c();
    HepLorentzVector p4child(const int &);
    double chisq();
    bool isGoodPi0();
    WTrackParameter wtrk();
    Pi0Info &operator=(Pi0Info &aPi0Info);
    bool calculate();

   private:
    EvtRecTrack *m_shower0;
    EvtRecTrack *m_shower1;
    WTrackParameter m_wtrk;
    bool isGoodPhoton(EvtRecTrack *);
    HepLorentzVector m_p4;
    HepLorentzVector m_p41c;
    double Pi0Info_mpi0;
    double m_mpi0;
    double m_mpi01c;
    double m_pi0_heliAngle;
    double m_helicity;
    double m_openAngle;
    double m_chisq;
    bool m_isgoodpi0, m_calculate;
};
#endif
