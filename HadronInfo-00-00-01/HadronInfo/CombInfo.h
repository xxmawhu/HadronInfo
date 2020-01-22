/* ====================================================
#   Copyright (C)2019 All rights reserved.
#
#   Author        : Xin-Xin MA
#   Email         : xxmawhu@163.com
#   File Name     : CombInfo.h
#   Create Time   : 2019-12-11 10:37
#   Last Modified : 2019-12-12 12:33
#   Describe      :
# get the combinate information of two particles, three particles
# for example, (pi0, pi0), (pi+, pi-, eta)
# ====================================================*/
#ifndef HadronInfo_COMBInfo_H
#define HadronInfo_COMBInfo_H
// #include "TupleSvc/DecayTree.h"
#include "GaudiKernel/Bootstrap.h"
#include "VertexFit/VertexFit.h"
#include "VertexFit/SecondVertexFit.h"
#include "VertexFit/IVertexDbSvc.h"
#include "CLHEP/Vector/LorentzVector.h"
#include "BesDChain/CDCandidate.h"
#include "BesDChain/CDDecay.h"
#include "HadronInfo/AvailableInfo.h"
#include "HadronInfo/util.h"
#include <iostream>
#include <string>
using CLHEP::HepLorentzVector;
using std::string;
using std::cout;
using std::endl;
template <class FirstInfo, class SecondInfo, int pid = 0, int doVertexFit = 0>
class CombInfo : public AvailableInfo {
   public:
    CombInfo(const CDCandidate& combParticle) {
        if (combParticle.decay().children().size() != 2) {
            cout << "Error: the numberChildren is not equal 2!" << endl;
        }
        // cout << "init with CDCandidate" << endl;
        m_firstInfo = FirstInfo(combParticle.decay().child(0));
        m_secondInfo = SecondInfo(combParticle.decay().child(1));
        m_calculate = false;
    }
    CombInfo(FirstInfo& firsInfo, SecondInfo& secondInfo) {
        m_firstInfo = firsInfo;
        m_secondInfo = secondInfo;
        m_pid = pid;
        std::cout << "init CombInfo successful" << std::endl;
        m_calculate = false;
        // std::cout << "CombInfo " << endl;
        // std::cout <<  firsInfo.GetName() << " and"
        //    << secondInfo.GetName() << endl;
        // cout << "name : "  << m_pid <<  endl;
        // if (!doVertexFit) {
        //     std::cout << "did not perform vertexfit!!!" << std::endl;
        // }
    }
    virtual const string GetName() { return HadronTool::Name(m_pid); }
    virtual const bool& DoVertexFit() {
        // do vertexfit
        // after vertex the children information will be update,
        // except pi0, eta, kaon...
        return doVertexFit;
    }
    virtual bool calculate() {
        if (m_calculate) {
            return true;
        }
        if (!doVertexFit) {
            m_p4 = m_firstInfo.p4() + m_secondInfo.p4();
            m_mass = m_p4.m();
            m_calculate = true;
            return true;
        }
        // do vertex fit now!
        // please make sure that the two candidates could be performd vertexfit
        VertexFit* m_vertexFit = VertexFit::instance();
        m_vertexFit->init();
        // m_vertexFit -> setChisqCut(1000);
        m_vertexFit->AddTrack(0, m_firstInfo.wtrk());
        m_vertexFit->AddTrack(1, m_secondInfo.wtrk());

        VertexParameter wideVertex;
        HepPoint3D vWideVertex(0., 0., 0.);
        HepSymMatrix evWideVertex(3, 0);

        evWideVertex[0][0] = 1.0e12;
        evWideVertex[1][1] = 1.0e12;
        evWideVertex[2][2] = 1.0e12;

        wideVertex.setVx(vWideVertex);
        wideVertex.setEvx(evWideVertex);

        m_vertexFit->AddVertex(0, wideVertex, 0, 1);
        m_vertexFit->Fit(0);
        m_vertexFit->Swim(0);
        m_vertexFit->BuildVirtualParticle(0);
        m_wVirtualTrack = m_vertexFit->wVirtualTrack(0);
        m_p4Child[0] = m_vertexFit->pfit(0);
        m_p4Child[1] = m_vertexFit->pfit(1);
        m_p4 = m_p4Child[0] + m_p4Child[1];
        m_vpar = m_vertexFit->vpar(0);
        m_firstInfo.updateWTrk(m_vertexFit->wtrk(0));
        m_secondInfo.updateWTrk(m_vertexFit->wtrk(1));

        m_mass = m_p4.m();
        m_vertexFitChisq = m_vertexFit->chisq(0);
        m_calculate = true;
        // cout << "CombInfo " << __func__ << __LINE__ << endl;
        // perform second vertex fit now!
        SecondVertexFit* m_2ndVtxFit = SecondVertexFit::instance();
        m_2ndVtxFit->init();
        // m_2ndVtxFit -> setChisqCut(1000);
        m_2ndVtxFit->AddTrack(0, m_wVirtualTrack);
        m_2ndVtxFit->setVpar(m_vpar);
        // set the primary Vertex
        VertexParameter primaryVertex;
        if (!m_isSetPriVtx) {
            VertexParameter beamSpot;
            HepPoint3D vBeamSpot(0., 0., 0.);
            HepSymMatrix evBeamSpot(3, 0);

            IVertexDbSvc* vtxsvc;
            Gaudi::svcLocator()->service("VertexDbSvc", vtxsvc);
            double* dbv = vtxsvc->PrimaryVertex();
            double* vv = vtxsvc->SigmaPrimaryVertex();
            for (unsigned int ivx = 0; ivx < 3; ivx++) {
                vBeamSpot[ivx] = dbv[ivx];
                evBeamSpot[ivx][ivx] = vv[ivx] * vv[ivx];
            }

            beamSpot.setVx(vBeamSpot);
            beamSpot.setEvx(evBeamSpot);
            primaryVertex = VertexParameter(beamSpot);
        } else {
            primaryVertex = m_privtxpar;
        }
        m_2ndVtxFit->setPrimaryVertex(primaryVertex);
        m_2ndVtxFit->Fit();
        m_secondVertexFitChisq = m_2ndVtxFit->chisq();
        m_decayLength = m_2ndVtxFit->decayLength();
        m_decayLError = m_2ndVtxFit->decayLengthError();
        return true;
    }

    void updateWTrk(const WTrackParameter& newWtrk) {
        m_wVirtualTrack = newWtrk;
        m_p4 = newWtrk.p();
        m_mass = newWtrk.mass();
    }
    const WTrackParameter& wtrk() {
        if (!m_calculate) calculate();
        return m_wVirtualTrack;
    }
    const HepLorentzVector& p4() {
        if (!m_calculate) calculate();
        return m_p4;
    }
    const HepLorentzVector& p4child(const int& i) {
        if (i!=0 && i!= 1) {
            std::cout << "Error no child for index " << i << std::endl;
            return HepLorentzVector(0, 0, 0, 999);
        }
        if (!m_calculate) calculate();
        return m_p4Child[i];
    }
    const double& mass() {
        if (!m_calculate) calculate();
        return m_mass;
    }
    // for convenence
    const double& m() { return this->mass(); }
    void setP4(const HepLorentzVector& p4) {
        m_p4 = p4;
        m_mass = p4.m();
    }
    const double& decayLength() {
        if (!m_calculate) calculate();
        return m_decayLength;
    }
    const double& decayLengthError() {
        if (!m_calculate) calculate();
        return m_decayLError;
    }
    const double& decayLengthRatio() {
        if (!m_calculate) calculate();
        return m_decayLength / m_decayLError;
    }
    const double& vtxChi2() { return this->VertexFitChisq(); }
    const double& chisq() { return this->VertexFitChisq(); }
    const double& VertexFitChisq() {
        if (!m_calculate) calculate();
        return m_vertexFitChisq;
    }
    const double& SecondVertexFitChisq() {
        if (!m_calculate) calculate();
        return m_secondVertexFitChisq;
    }
    const double& chi2() { return this->SecondVertexFitChisq(); }
    void setPrimaryVertex(VertexParameter& privtxpar) {
        m_privtxpar = privtxpar;
        m_isSetPriVtx = true;
        m_calculate = false;
    }
    std::pair<FirstInfo, SecondInfo>& decay() {
        return std::make_pair<m_firstInfo, m_secondInfo>;
    }

   private:
    bool m_calculate, m_isSetPriVtx;
    int m_pid;
    HepLorentzVector m_p4;
    HepLorentzVector m_p4Child[2];
    double m_mass;
    double m_decayLength, m_decayLError;
    double m_vertexFitChisq, m_secondVertexFitChisq;
    FirstInfo m_firstInfo;
    SecondInfo m_secondInfo;
    WTrackParameter m_wVirtualTrack;
    VertexParameter m_vpar;
    VertexParameter m_privtxpar;
};
#endif
