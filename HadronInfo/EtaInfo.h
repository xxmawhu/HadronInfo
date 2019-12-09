#ifndef CLASS_EtaINFO_H
#define CLASS_EtaINFO_H

#include "EvtRecEvent/EvtRecTrack.h"

#include "CLHEP/Vector/LorentzVector.h"
#include "VertexFit/KalmanKinematicFit.h"

#include "BesDChain/CDDecay.h"
#include "HadronInfo/AvailableInfo.h"
#include <iostream>
#include <vector>
using std::vector;

using namespace std;
class EtaInfo : public AvailableInfo {
   public:
    EtaInfo();
    EtaInfo(EvtRecTrack *, EvtRecTrack *);
    EtaInfo(vector<const EvtRecTrack *>);
    EtaInfo(const CDCandidate &);
    ~EtaInfo();
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
    bool isGoodEta();
    WTrackParameter wtrk();
    EtaInfo &operator=(EtaInfo &aEtaInfo);
    bool calculate();

   private:
    EvtRecTrack *m_shower0;
    EvtRecTrack *m_shower1;
    bool isGoodPhoton(EvtRecTrack *);
    HepLorentzVector m_p4;
    HepLorentzVector m_p41c;
    WTrackParameter m_wtrk;
    double EtaInfo_mpi0;
    double m_mpi0;
    double m_mpi01c;
    double m_pi0_heliAngle;
    double m_helicity;
    double m_openAngle;
    double m_chisq;
    bool m_isgoodpi0, m_calculate;
};
#endif
