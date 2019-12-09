#ifndef CLASS_HadronInfo_GGInfo_H
#define CLASS_HadronInfo_GGInfo_H

#include "EvtRecEvent/EvtRecTrack.h"

#include "CLHEP/Vector/LorentzVector.h"
#include "VertexFit/KalmanKinematicFit.h"
#include "BesDChain/CDDecay.h"
#include "HadronInfo/AvailableInfo.h"

#include <iostream>

using namespace std;
class GGInfo : public AvailableInfo {
   public:
    GGInfo();
    GGInfo(EvtRecTrack *, EvtRecTrack *);
    GGInfo(vector<const EvtRecTrack *>);
    GGInfo(const CDCandidate &);

    ~GGInfo();
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
    // GGInfo &operator=(GGInfo &aGGInfo);
    bool calculate();
    void setWTrackParameter(const WTrackParameter&);
    void setRawMass(const double&);
    void setHelicity(const double&);
    void setOpenAngle(const double&);
    void setChisq(const double&);
    void setP41C(const HepLorentzVector&);
    void setRawP4(const HepLorentzVector&);
    void setRawP4(const HepLorentzVector&);
    void setP4Child(const HepLorentzVector&, const int&);

   private:
    EvtRecTrack *m_shower0;
    EvtRecTrack *m_shower1;
    WTrackParameter m_wtrk;
    bool isGoodPhoton(EvtRecTrack *);
    HepLorentzVector m_p4;
    HepLorentzVector m_p41c;
    HepLorentzVector m_p4Child[2];
    HepLorentzVector m_rawp4;
    double GGInfo_mpi0;
    double m_mpi0;
    double m_mpi01c;
    double m_pi0_heliAngle;
    double m_helicity;
    double m_openAngle;
    double m_chisq;
    bool m_isgoodpi0, m_calculate;
    void initAvialableInfo() {
        AvailableInfo::add("mass", "double");
        AvailableInfo::add("mass1C", "double");
        AvailableInfo::add("angle", "double");
        AvailableInfo::add("openAngle", "double");
        AvailableInfo::add("helicity", "double");
        AvailableInfo::add("p4", "HepLorentzVector");
        AvailableInfo::add("p41C", "HepLorentzVector");
        AvailableInfo::add("p4GammaHigh", "HepLorentzVector");
        AvailableInfo::add("p4GammaLow", "HepLorentzVector");
    }
};
#endif
