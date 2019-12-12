#ifndef CLASS_OMEGAInfo_H
#define CLASS_OMEGAInfo_H

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
#include "HadronInfo/AvailableInfo.h"
#include <iostream>
using namespace std;
const double Omegainfo_mproton = 938.272081;
const double Omegainfo_mpionm = 0.139571;
const double Omegainfo_mkaonm = 0.493677;

class OmegaInfo : public AvailableInfo {
   public:
    OmegaInfo();
    OmegaInfo(const EvtRecTrack *, const EvtRecTrack *, const EvtRecTrack *);
    OmegaInfo(const CDCandidate &aOmega);
    ~OmegaInfo();

    virtual const double &GetDoubleInfo(const string &);
    virtual const HepLorentzVector &GetLorentzVector(const string &info_name);
    // OmegaInfo &operator=(OmegaInfo &aOmegaInfo);

    void setchild(const int &n, const EvtRecTrack *track);
    void setchilds(const EvtRecTrack *track0, const EvtRecTrack *track1,
                   const EvtRecTrack *track2);
    EvtRecTrack *getchild(const int &);
    bool calculate();
    double m();
    double momegap4();
    double vtxChi2();
    double chi2();
    const double &chisq() { return chi2(); }

    double decayLength();
    double decayLengthRatio();
    double decayLengthError();
    HepLorentzVector p4();
    HepLorentzVector p4child(const int &);
    HepLorentzVector pfit(const int &);
    HepPoint3D sndvtx();
    WTrackParameter wtrk();
    VertexParameter vtxPar();
    WTrackParameter &wtrk(const int &);
    VertexParameter primaryVtxPar();
    void setPrimaryVtxPar(VertexParameter &privtxpar);
    // bool init();

   private:
    EvtRecTrack *m_track0;
    EvtRecTrack *m_track1;
    EvtRecTrack *m_track2;
    HepLorentzVector m_p4;
    HepLorentzVector m_pfit[2];
    HepLorentzVector m_p4child0;
    HepLorentzVector m_p4child1;
    VertexFit *m_vtxFit;
    SecondVertexFit *m_2ndVtxFit;
    VertexParameter m_vpar;
    VertexParameter m_privtxpar;
    WTrackParameter m_wVirtualTrack;
    WTrackParameter m_wtrk[2];
    HepPoint3D m_2ndVtx;
    bool m_cal, m_isSetPriVtx;
    double m_momegap4;
    double m_vmomega;
    double m_vchi2omega1;
    double m_vchi2omega2;
    double m_vlomega;
    double m_vromega;
    double m_veomega;
};
#endif
