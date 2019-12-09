#ifndef CLASS_KSINFO_H
#define CLASS_KSINFO_H

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
#include "HadronInfo/AvailableInfo.h"
#include "HadronInfo/VeeInfo.h"

#include "BesDChain/CDDecay.h"
#include <iostream>
using namespace std;

class KsInfo : public VeeInfo {
   public:
    // KsInfo();
    KsInfo(const string &name1 = "Proton", const string &name2 = "Pion")
        : VeeInfo(name1, name2) {
        VeeInfo::setChildName(0, name1);
        VeeInfo::setChildName(1, name2);
    }

    KsInfo(const EvtRecTrack *track0, const EvtRecTrack *track1,
           const string &name1 = "Proton", const string &name2 = "Pion")
        : VeeInfo(track0, track1, name1, name2) {
        VeeInfo::setChildName(0, name1);
        VeeInfo::setChildName(1, name2);
    }

    KsInfo(const CDCandidate &aLambda, const string &name1 = "Proton",
           const string &name2 = "Pion")
        : VeeInfo(aLambda, name1, name2) {
        VeeInfo::setChildName(0, name1);
        VeeInfo::setChildName(1, name2);
    }
    ~KsInfo();
    virtual double GetDoubleInfo(const string &);
    virtual HepLorentzVector GetLorentzVector(const string &info_name);

    // KsInfo &operator=(KsInfo &aKsInfo);

    bool calculate() {
        if (calculated()) {
            return true;
        }
        RecMdcKalTrack *pion1Trk = getchild(0)->mdcKalTrack();
        RecMdcKalTrack *pion2Trk = getchild(1)->mdcKalTrack();
        pion1Trk->setPidType(RecMdcKalTrack::pion);
        pion2Trk->setPidType(RecMdcKalTrack::pion);
        const double mpion = 0.139570;
        HepLorentzVector pion1p4 = pion1Trk->p4(mpion);
        HepLorentzVector pion2p4 = pion2Trk->p4(mpion);
        VeeInfo::setP4Child(pion1p4, 0);
        setP4Child(pion2p4, 1);
        setRawMass((pion1p4 + pion2p4).m());

        WTrackParameter wvTrk1(mpion, pion1Trk->getZHelix(),
                               pion1Trk->getZError());
        WTrackParameter wvTrk2(mpion, pion2Trk->getZHelix(),
                               pion2Trk->getZError());

        VertexParameter &wideVertex = getWideVertex();
        // the vertex fit to get the `primary vertex` or `second vertex`, or
        // `third vertex`
        VertexFit *m_vertexFit = VertexFit::instance();
        m_vertexFit->init();
        // m_vertexFit -> setChisqCut(1000);
        m_vertexFit->AddTrack(0, wvTrk1);
        m_vertexFit->AddTrack(1, wvTrk2);
        m_vertexFit->AddVertex(0, wideVertex, 0, 1);
        m_vertexFit->Fit(0);
        m_vertexFit->Swim(0);
        m_vertexFit->BuildVirtualParticle(0);

        setWTrackParameter(m_vertexFit->wVirtualTrack(0));
        setWTrk(0, m_vertexFit->wtrk(0));
        setWTrk(1, m_vertexFit->wtrk(1));
        setP4Fit(m_vertexFit->pfit(0), 0);
        setP4Fit(m_vertexFit->pfit(1), 1);
        HepLorentzVector p4Ks = m_vertexFit->pfit(0) + m_vertexFit->pfit(1);
        setP4(p4Ks);
        setVtxChi2(m_vertexFit->chisq(0));

        VertexParameter &primaryVertex = getPrimaryVertex();
        SecondVertexFit *m_secondVertexFit = SecondVertexFit::instance();
        m_secondVertexFit->init();
        m_secondVertexFit->AddTrack(0, m_vertexFit->wVirtualTrack(0));
        m_secondVertexFit->setVpar(m_vertexFit->vpar(0));
        m_secondVertexFit->setPrimaryVertex(primaryVertex);
        m_secondVertexFit->Fit();

        setChi2(m_secondVertexFit->chisq());
        setDecayLength(m_secondVertexFit->decayLength());
        setDecayLengthError(m_secondVertexFit->decayLengthError());
        if (m_secondVertexFit->decayLengthError() == 0) {
            setDecayLengthRatio(-999);
        } else {
            setDecayLengthRatio(m_secondVertexFit->decayLength() /
                                m_secondVertexFit->decayLengthError());
        }
        setCalculated(true);
        return true;
    }

   private:
    void initAvialableInfo() {
        add("mass", "double");
        add("mksp4", "double");
        add("vtxChi2", "double");
        add("chi", "double");
        add("decayLength", "double");
        add("decayLengthError", "double");
        add("decayLengthRatio", "double");
        add("p4", "HepLorentzVector");
        add("p4Pip", "HepLorentzVector");
        add("p4Pim", "HepLorentzVector");
        add("p4FitPip", "HepLorentzVector");
        add("p4FitPim", "HepLorentzVector");
    }
};
#endif
