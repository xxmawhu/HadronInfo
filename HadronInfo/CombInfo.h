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
#ifndef HadronInfo_COMBINFO_H
#define HadronInfo_COMBINFO_H
// #include "TupleSvc/DecayTree.h"
#include "VertexFit/VertexFit.h"
#include "CLHEP/Vector/LorentzVector.h"
#include <iostream>
#include <string>
#include "HadronInfo/AvailableInfo.h"
#include "HadronInfo/util.h"
using CLHEP::HepLorentzVector;
using std::string;
using std::cout;
using std::endl;
template <class FirstInfo, class SecondInfo, int pid=0,
         bool doVertexFit = false>
class CombInfo : public AvailableInfo {
   public:
    CombInfo(FirstInfo& firsInfo, SecondInfo& secondInfo) {
        m_firstInfo = firsInfo;
        m_secondInfo = secondInfo;
        m_pid = pid;
        std::cout << "init CombInfo successful" << std::endl;
        cout << "CombInfo " << firsInfo.GetName() << " and"
            << secondInfo.GetName() << endl;
        cout << "name : "  << m_pid <<  endl;
        if (!doVertexFit) {
            std::cout << "did not perform vertexfit!!!" << std::endl;
        }
    }
    virtual const string& GetName(){
        return HadronTool::Name(m_pid);
    }
    virtual bool calculate(){
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
        VertexFit *m_vertexFit = VertexFit::instance();
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
        m_p4 = m_vertexFit->pfit(0) + m_vertexFit->pfit(1);
        m_mass = m_p4.m();
        m_calculate = true;
        return true;
    }

    void updateWTrk(const WTrackParameter& newWtrk) {
        m_wVirtualTrack = newWtrk;
        m_p4 = newWtrk.p();
        m_mass = newWtrk.mass();
    }
    const WTrackParameter& wtrk(){
        if (!m_calculate) calculate();
        return m_p4;
    }
    const HepLorentzVector& p4(){
        if (!m_calculate) calculate();
        return m_p4;
    }
    const double& mass(){
        if (!m_calculate) calculate();
        return m_mass;
    }
    void setP4(const HepLorentzVector& p4){
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
