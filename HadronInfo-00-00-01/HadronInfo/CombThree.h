/* ====================================================
#   Copyright (C)2019 All rights reserved.
#
#   Author        : Xin-Xin MA
#   Email         : xxmawhu@163.com
#   File Name     : CombThree.h
#   Create Time   : 2019-12-11 10:37
#   Last Modified : 2019-12-12 12:33
#   Describe      :
# get the combinate information of two particles, three particles
# for example, (pi0, pi0), (pi+, pi-, eta)
# ====================================================*/
#ifndef HadronInfo_COMTHREEDev_H
#define HadronInfo_COMTHREEDev_H
// #include "TupleSvc/DecayTree.h"
#include "VertexFit/VertexFit.h"
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
template <class FirstInfo, class SecondInfo, class ThirdInfo, int pid = 0,
          int doVertexFit = 0>
class CombThree : public AvailableInfo {
   public:
    CombThree(const CDCandidate& combParticle) {
        if (combParticle.decay().children().size() != 2) {
            cout << "Error: the numberChildren is not equal 2!" << endl;
        }
        cout << "init with CDCandidate" << endl;
        m_firstInfo = FirstInfo(combParticle.decay().child(0));
        m_secondInfo = SecondInfo(combParticle.decay().child(1));
        m_calculate = false;
    }
    CombThree(FirstInfo& firsInfo, SecondInfo& secondInfo) {
        m_firstInfo = firsInfo;
        m_secondInfo = secondInfo;
        m_pid = pid;
        std::cout << "init CombThree successful" << std::endl;
        m_calculate = false;
        // std::cout << "CombThree " << endl;
        // std::cout <<  firsInfo.GetName() << " and"
        //    << secondInfo.GetName() << endl;
        // cout << "name : "  << m_pid <<  endl;
        // if (!doVertexFit) {
        //     std::cout << "did not perform vertexfit!!!" << std::endl;
        // }
    }
    virtual const string GetName() { return HadronTool::Name(m_pid); }
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
        cout << "CombThree " << __func__ << __LINE__ << endl;
        VertexFit* m_vertexFit = VertexFit::instance();
        cout << "CombThree " << __func__ << __LINE__ << endl;
        m_vertexFit->init();
        // m_vertexFit -> setChisqCut(1000);
        cout << "CombThree " << __func__ << __LINE__ << endl;
        m_vertexFit->AddTrack(0, m_firstInfo.wtrk());
        m_vertexFit->AddTrack(1, m_secondInfo.wtrk());
        cout << "CombThree " << __func__ << __LINE__ << endl;

        VertexParameter wideVertex;
        HepPoint3D vWideVertex(0., 0., 0.);
        HepSymMatrix evWideVertex(3, 0);
        cout << "CombThree " << __func__ << __LINE__ << endl;

        evWideVertex[0][0] = 1.0e12;
        evWideVertex[1][1] = 1.0e12;
        evWideVertex[2][2] = 1.0e12;

        wideVertex.setVx(vWideVertex);
        wideVertex.setEvx(evWideVertex);

        m_vertexFit->AddVertex(0, wideVertex, 0, 1);
        m_vertexFit->Fit(0);
        cout << "CombThree " << __func__ << __LINE__ << endl;
        m_vertexFit->Swim(0);
        m_vertexFit->BuildVirtualParticle(0);
        m_wVirtualTrack = m_vertexFit->wVirtualTrack(0);
        cout << "CombThree " << __func__ << __LINE__ << endl;
        m_p4 = m_vertexFit->pfit(0) + m_vertexFit->pfit(1);
        cout << "CombThree " << __func__ << __LINE__ << endl;
        m_mass = m_p4.m();
        cout << "CombThree " << __func__ << __LINE__ << endl;
        m_calculate = true;
        cout << "CombThree " << __func__ << __LINE__ << endl;
        return true;
    }

    void updateWTrk(const WTrackParameter& newWtrk) {
        m_wVirtualTrack = newWtrk;
        m_p4 = newWtrk.p();
        m_mass = newWtrk.mass();
    }
    const WTrackParameter& wtrk() {
        if (!m_calculate) calculate();
        return m_p4;
    }
    const HepLorentzVector& p4() {
        if (!m_calculate) calculate();
        return m_p4;
    }
    const double& mass() {
        if (!m_calculate) calculate();
        return m_mass;
    }
    inline const double& m() { return this->mass(); }
    void setP4(const HepLorentzVector& p4) {
        m_p4 = p4;
        m_mass = p4.m();
    }

   private:
    int m_pid;
    HepLorentzVector m_p4;
    double m_mass;
    bool m_calculate;
    FirstInfo m_firstInfo;
    SecondInfo m_secondInfo;
    WTrackParameter m_wVirtualTrack;
};
#endif
