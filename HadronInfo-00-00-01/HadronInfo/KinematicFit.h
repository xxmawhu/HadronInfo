#ifndef CLASS_KSInfo_H
#define CLASS_KSInfo_H

//#include "GaudiKernel/ObjectVector.h"
//#include "GaudiKernel/AlgFactory.h"
//#include "GaudiKernel/Algorithm.h"
//#include "GaudiKernel/NTuple.h"
//#include "GaudiKernel/IDataProviderSvc.h"

#include "EvtRecEvent/EvtRecTrack.h"
//#include "EvtRecEvent/EvtRecDTag.h"
#include "VertexFit/VertexFit.h"
#include "VertexFit/SecondVertexFit.h"
#include "CLHEP/Vector/LorentzVector.h"

#include "BesDChain/CDDecay.h"
#include <iostream>

class KinematicFit {
   public:
    KinematicFit();
    KinematicFit(const CDCandidate &aKs);
    Feed(const CDCandidate &aKs);
    ~KinematicFit();

    void SetChild(int n, EvtRecTrack *track);
    void SetChildren(EvtRecTrack *track0, EvtRecTrack *track1);
    EvtRecTrack *GetChild(int n);
    bool Calculate();
    double m();
    double mksP4();
    double vtxChi2();
    double chi2();
    double DecayLength();
    double DecayLengthRatio();
    double DecayLengthError();
    HepLorentzVector P4();
    HepLorentzVector P4Child(int i);
    HepLorentzVector pfit(int i);
    HepPoint3D sndvtx();
    WTrackParameter wVirtualTrack();
    VertexParameter vtxPar();
    VertexParameter primaryVtxPar();
    void setPrimaryVtxPar(VertexParameter &privtxpar);
    bool init();

   private:
    KinematicFit &operator=(KinematicFit &aKinematicFit);
    EvtRecTrack *m_track0;
    EvtRecTrack *m_track1;
    HepLorentzVector m_p4;
    HepLorentzVector m_pfit[2];
    HepLorentzVector m_p4child0;
    HepLorentzVector m_p4child1;
    VertexFit *m_vtxFit;
    SecondVertexFit *m_2ndVtxFit;
    VertexParameter m_vpar;
    VertexParameter m_privtxpar;
    WTrackParameter m_wVirtualTrack;
    HepPoint3D m_2ndVtx;
    bool m_cal;
    double m_mksp4;
    double m_vmks;
    double m_vchi2ks1;
    double m_vchi2ks2;
    double m_vlks;
    double m_vrks;
    double m_veks;
};
#endif
