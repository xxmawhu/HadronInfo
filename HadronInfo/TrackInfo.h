#ifndef CLASS_TrackINFO_H
#define CLASS_TrackINFO_H

#include "EvtRecEvent/EvtRecTrack.h"

#include "CLHEP/Vector/LorentzVector.h"
#include "VertexFit/WTrackParameter.h"
#include "MdcRecEvent/RecMdcKalTrack.h"

#include "BesDChain/CDDecay.h"
#include "HadronInfo/AvailableInfo.h"
#include <iostream>

using namespace std;
class TrackInfo : public AvailableInfo {
   public:
    TrackInfo();
    TrackInfo(const int&);
    TrackInfo(const EvtRecTrack *);
    TrackInfo(const CDCandidate &aTrk);
    ~TrackInfo();

    virtual double GetDoubleInfo(const string &);
    virtual HepLorentzVector GetLorentzVector(const string &info_name);

    void SetTrack(const int &parId, const EvtRecTrack *);
    void SetTrack(const EvtRecTrack *);
    TrackInfo &operator=(TrackInfo &aTrackInfo);

    void setPID(const int &pid) { m_parId = pid; }
    HepLorentzVector p4();
    HepLorentzVector p4(const int &PID);
    HepLorentzVector p4(EvtRecTrack *, const int &);
    HepLorentzVector p4c(const EvtRecTrack *, const int &);
    WTrackParameter wtrk(EvtRecTrack *, const int &);
    WTrackParameter wtrk(const int &PID);
    WTrackParameter wtrkc(const EvtRecTrack *, const int &);

   private:
    void calculate();
    EvtRecTrack *m_track;
    WTrackParameter m_wtrk;
    int m_parId;
    HepLorentzVector m_p4;
    void initAvialableInfo() {
        AvailableInfo::add("Rxy", "double");
        AvailableInfo::add("Rz", "double");
        AvailableInfo::add("p4", "HepLorentzVector");
    }
};
#endif
