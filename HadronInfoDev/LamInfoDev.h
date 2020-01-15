/* ====================================================
#   Copyright (C)2019 All rights reserved.
#
#   Author        : Xin-Xin MA
#   Email         : xxmawhu@163.com
#   File Name     : LamInfoDev.h
#   Create Time   : 2019-12-08 18:11
#   Last Modified : 2019-12-08 18:17
#   Describe      :
#
# ====================================================*/

#ifndef CLASS_Lambda_INFODev_H
#define CLASS_Lambda_INFODev_H
#include "EvtRecEvent/EvtRecTrack.h"
#include "VertexFit/VertexFit.h"
#include "VertexFit/SecondVertexFit.h"
#include "CLHEP/Vector/LorentzVector.h"
#include "HadronInfoDev/AvailableInfoDev.h"
#include "HadronInfoDev/VeeInfoDev.h"

#include "BesDChain/CDDecay.h"
#include <iostream>
using namespace std;

class LamInfoDev : public VeeInfoDev {
   public:
    // LamInfoDev();
    // LamInfoDev(); : VeeInfoDev("Proton", "Pion"){};
    // VeeInfoDev::VeeInfoDev(track0, track1);
    LamInfoDev(const string &name1 = "Proton", const string &name2 = "Pion")
        : VeeInfoDev(name1, name2) {
        // VeeInfoDev::setChildName(0, name1);
        // VeeInfoDev::setChildName(1, name2);
    }

    LamInfoDev(const EvtRecTrack *track0, const EvtRecTrack *track1,
            const string &name1 = "Proton", const string &name2 = "Pion")
        : VeeInfoDev(track0, track1, name1, name2) {
        // VeeInfoDev::setChildName(0, name1);
        // VeeInfoDev::setChildName(1, name2);
    }

    LamInfoDev(const CDCandidate &aLambda, const string &name1 = "Proton",
            const string &name2 = "Pion")
        : VeeInfoDev(aLambda, name1, name2) {
        // VeeInfoDev::setChildName(0, name1);
        // VeeInfoDev::setChildName(1, name2);
    }
    virtual const string GetName() {
        // m_name = "Lambda";
        return "Lambda";
    }
    string getName() {
        string name = "Lambda";
        return name;
    }
    ~LamInfoDev() {};
    virtual const HepLorentzVector &GetLorentzVector(const string &info_name) {
        if (info_name == "p4") return this->p4();
        if (info_name == "p4" + getChildName(0)) return this->p4child(0);
        if (info_name == "p4" + getChildName(1)) return this->p4child(1);
        if (info_name == "p4Fit" + getChildName(0)) return this->p4fit(0);
        if (info_name == "p4Fit" + getChildName(1)) return this->p4fit(1);
        return HepLorentzVector(0, 0, 0, -110);
    }
    virtual const double &GetDoubleInfoDev(const string &info_name) {
        if (info_name == "mass") return this->m();
        if (info_name == "vtxChi2") return this->vtxChi2();
        if (info_name == "chisq") return this->chisq();
        if (info_name == "decayLength") return this->decayLength();
        if (info_name == "decayLengthRatio") return this->decayLengthRatio();
        if (info_name == "decayLengthError") return this->decayLengthError();
        return -110;
    }

    // LamInfoDev &operator=(LamInfoDev &aLamInfoDev);

    bool calculate() {
        if (calculated()) {
            return true;
        }
        RecMdcKalTrack *protonTrk = getchild(0)->mdcKalTrack();
        RecMdcKalTrack *pionTrk = getchild(1)->mdcKalTrack();
        protonTrk->setPidType(RecMdcKalTrack::proton);
        const double mproton = 0.938272013;
        HepLorentzVector pion1p4 = protonTrk->p4(mproton);
        pionTrk->setPidType(RecMdcKalTrack::pion);
        const double mpion = 0.139570;
        HepLorentzVector pion2p4 = pionTrk->p4(mpion);
        VeeInfoDev::setP4Child(pion1p4, 0);
        setP4Child(pion2p4, 1);
        setRawMass((pion1p4 + pion2p4).m());

        WTrackParameter wvTrk1(mproton, protonTrk->getZHelixP(),
                               protonTrk->getZErrorP());
        WTrackParameter wvTrk2(mpion, pionTrk->getZHelix(),
                               pionTrk->getZError());

        VertexParameter wideVertex = getWideVertex();
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

        VertexParameter primaryVertex = getPrimaryVertex();
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
    string m_name;
    virtual void addAvialInfoDev() {
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
