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
#include <vector>
#include <algorithm>
#include <string>
using CLHEP::HepLorentzVector;
using std::string;
using std::cout;
using std::endl;
template <class FirstInfo, class SecondInfo, int pid = 0, int doVertexFit = 0>
class CombInfo : virtual public AvailableInfo {
   public:
    CombInfo() {
        m_pid = pid;
        SetName(HadronTool::Name(m_pid));
        m_firstInfo = FirstInfo();
        m_secondInfo = SecondInfo();
        AddAvialInfo();
        m_calculate = true;
    }
    CombInfo(const CDCandidate& combParticle) {
        if (combParticle.decay().children().size() != 2) {
            cout << "Error: the numberChildren is not equal 2!" << endl;
        }
        // cout << "init with CDCandidate" << endl;
        SetName(HadronTool::Name(m_pid));
        m_firstInfo = FirstInfo(combParticle.decay().child(0));
        m_secondInfo = SecondInfo(combParticle.decay().child(1));
        m_firstInfo.SetName(m_firstInfo.GetName() + HadronTool::Name(m_pid));
        m_secondInfo.SetName(m_secondInfo.GetName() + HadronTool::Name(m_pid));
        AddAvialInfo();
        m_calculate = false;
    }
    CombInfo(FirstInfo& firsInfo, SecondInfo& secondInfo) {
        m_firstInfo = firsInfo;
        m_secondInfo = secondInfo;
        m_firstInfo.SetName(m_firstInfo.GetName() + HadronTool::Name(m_pid));
        m_secondInfo.SetName(m_secondInfo.GetName() + HadronTool::Name(m_pid));
        m_pid = pid;
        SetName(HadronTool::Name(m_pid));
        std::cout << "init CombInfo successful" << std::endl;
        AddAvialInfo();
        m_calculate = false;
        // std::cout << "CombInfo " << endl;
        // std::cout <<  firsInfo.GetName() << " and"
        //    << secondInfo.GetName() << endl;
        // cout << "name : "  << m_pid <<  endl;
        // if (!doVertexFit) {
        //     std::cout << "did not perform vertexfit!!!" << std::endl;
        // }
    }
    void Feed(const CDCandidate& combParticle) {
        if (combParticle.decay().children().size() != 2) {
            cout << "Error: the numberChildren is not equal 2!" << endl;
        }
        // cout << "init with CDCandidate" << endl;
        m_firstInfo = FirstInfo(combParticle.decay().child(0));
        m_secondInfo = SecondInfo(combParticle.decay().child(1));
        m_firstInfo.SetName(m_firstInfo.GetName() + HadronTool::Name(m_pid));
        m_secondInfo.SetName(m_secondInfo.GetName() + HadronTool::Name(m_pid));
        m_calculate = false;
    }
    void Feed(FirstInfo& firsInfo, SecondInfo& secondInfo) {
        m_firstInfo = firsInfo;
        m_secondInfo = secondInfo;
        m_firstInfo.SetName(m_firstInfo.GetName() + HadronTool::Name(m_pid));
        m_secondInfo.SetName(m_secondInfo.GetName() + HadronTool::Name(m_pid));
        m_pid = pid;
        std::cout << "init CombInfo successful" << std::endl;
        m_calculate = false;
    }
    virtual const bool& DoVertexFit() {
        // do vertexfit
        // after vertex the children information will be update,
        // except pi0, eta, kaon...
        return doVertexFit;
    }
    int Charge() { return m_firstInfo.Charge() + m_secondInfo.Charge(); }
    virtual void GetInfoI(const std::string& info_name, int& targe){
        int length = info_name.size() - (this->GetName()).size();
        // std::string firstname = m_firstInfo.GetName();
        std::string tmpname = info_name.substr(0, length);
      //  m_firstInfo.GetInfoInt(firstname, length);
      //  m_firstInfo.GetInfo(firstname, length);
       // firsInfo 
       std::vector<std::string> tmpAllInfo = m_firstInfo.GetType("int");
       if (std::find(tmpAllInfo.begin(), tmpAllInfo.end(), tmpname) != tmpAllInfo.end()) {
           m_firstInfo.GetInfoI(tmpname, targe);
           return;
       }
       tmpAllInfo = m_secondInfo.GetType("int");
       if (std::find(tmpAllInfo.begin(), tmpAllInfo.end(), tmpname) != tmpAllInfo.end()) {
           m_secondInfo.GetInfoI(tmpname, targe);
           return;
       }
       return;
    }

    virtual void GetInfoD(const std::string& info_name, double& targe){
        if (info_name == string("decayLength")) {
            targe = m_decayLength;
            return;
        } else if (info_name == string("decayLengthError")) {
            targe = m_decayLError;
            return;
        } else if (info_name == string("decayLengthRatio")) {
            targe = this->DecayLengthRatio();
            return;
        } else if (info_name == string("VertexFitChisq")) {
            targe = this->VertexFitChisq();
            return;
        } else if (info_name == string("SecondVertexFitChisq")) {
            targe = this->SecondVertexFitChisq();
            return;
        } else if (info_name == string("RawMass")) {
            targe = this->RawMass();
            return;
        } else if (info_name == string("Mass")) {
            targe = this->Mass();
            return;
        } 
        int length = info_name.size() - (this->GetName()).size();
        std::string tmpname = info_name.substr(0, length);
        // firsInfo 
        std::vector<std::string> tmpAllInfo = m_firstInfo.GetType("double");
        if (std::find(tmpAllInfo.begin(), tmpAllInfo.end(), tmpname) != tmpAllInfo.end()) {
            m_firstInfo.GetInfoD(tmpname, targe);
            return;
        }
        tmpAllInfo = m_secondInfo.GetType("double");
        if (std::find(tmpAllInfo.begin(), tmpAllInfo.end(), tmpname) != tmpAllInfo.end()) {
            m_secondInfo.GetInfoD(tmpname, targe);
            return;
        }
        return;
    }
    virtual void GetInfoH(const std::string& info_name, HepLorentzVector& targe) {
        if (info_name == string("p4")) {
            targe = this->P4();
            return;
        } else if (info_name == string("RawP4")) {
            targe = this->RawP4();
            return;
        } 
        int length = info_name.size() - (this->GetName()).size();
        std::string tmpname = info_name.substr(0, length);
        // firsInfo 
        std::vector<std::string> tmpAllInfo = m_firstInfo.GetType("HepLorentzVector");
        if (std::find(tmpAllInfo.begin(), tmpAllInfo.end(), tmpname) != tmpAllInfo.end()) {
            m_firstInfo.GetInfoH(tmpname, targe);
            return;
        }
        tmpAllInfo = m_secondInfo.GetType("HepLorentzVector");
        if (std::find(tmpAllInfo.begin(), tmpAllInfo.end(), tmpname) != tmpAllInfo.end()) {
            m_secondInfo.GetInfoH(tmpname, targe);
            return;
        }
        return;
    }
    virtual void GetInfoVi(const std::string& info_name, std::vector<int>& targe){
        int length = info_name.size() - (this->GetName()).size();
        std::string tmpname = info_name.substr(0, length);
        // firsInfo 
        std::vector<std::string> tmpAllInfo = m_firstInfo.GetType("int");
        if (std::find(tmpAllInfo.begin(), tmpAllInfo.end(), tmpname) != tmpAllInfo.end()) {
            m_firstInfo.GetInfoVi(tmpname, targe);
            return;
        }
        tmpAllInfo = m_secondInfo.GetType("int");
        if (std::find(tmpAllInfo.begin(), tmpAllInfo.end(), tmpname) != tmpAllInfo.end()) {
            m_secondInfo.GetInfoVi(tmpname, targe);
            return;
        }
        return;
    }
    virtual void GetInfoVd(const std::string& info_name, std::vector<double>& targe) {
        int length = info_name.size() - (this->GetName()).size();
        std::string tmpname = info_name.substr(0, length);
        // firsInfo 
        std::vector<std::string> tmpAllInfo = m_firstInfo.GetType("double");
        if (std::find(tmpAllInfo.begin(), tmpAllInfo.end(), tmpname) != tmpAllInfo.end()) {
            m_firstInfo.GetInfoVd(tmpname, targe);
            return;
        }
        tmpAllInfo = m_secondInfo.GetType("double");
        if (std::find(tmpAllInfo.begin(), tmpAllInfo.end(), tmpname) != tmpAllInfo.end()) {
            m_secondInfo.GetInfoVd(tmpname, targe);
            return;
        }
        return;
    }

    virtual bool Calculate() {
        if (m_calculate) {
            return true;
        }
        m_rawp4 = m_firstInfo.P4() + m_secondInfo.P4();
        m_rawMass = m_rawp4.m(); 
        if (!doVertexFit) {
            m_p4 = m_firstInfo.P4() + m_secondInfo.P4();
            m_mass = m_p4.m();
            m_calculate = true;
            return true;
        }
        // do vertex fit now!
        // please make sure that the two candidates could be performd vertexfit
        VertexFit* m_vertexFit = VertexFit::instance();
        m_vertexFit->init();
        // m_vertexFit -> setChisqCut(1000);
        m_vertexFit->AddTrack(0, m_firstInfo.WTrk());
        m_vertexFit->AddTrack(1, m_secondInfo.WTrk());

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
        m_firstInfo.UpdateWTrk(m_vertexFit->wtrk(0));
        m_secondInfo.UpdateWTrk(m_vertexFit->wtrk(1));
        if (m_firstInfo.DoVertexFit()) {
            m_firstInfo.SetPrimaryVertex(m_vpar);
        }
        if (m_secondInfo.DoVertexFit()) {
            m_secondInfo.SetPrimaryVertex(m_vpar);
        }

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

    void UpdateWTrk(const WTrackParameter& newWtrk) {
        m_wVirtualTrack = newWtrk;
        m_p4 = newWtrk.p();
        m_mass = newWtrk.mass();
    }
    const WTrackParameter& WTrk() {
        if (!m_calculate) Calculate();
        return m_wVirtualTrack;
    }
    const HepLorentzVector& P4() {
        if (!m_calculate) Calculate();
        return m_p4;
    }
    const HepLorentzVector& RawP4() {
        if (!m_calculate) Calculate();
        return m_rawp4;
    }
    const HepLorentzVector& P4Child(const int& i) {
        if (i != 0 && i != 1) {
            std::cout << this->GetName() + ".P4Child(" << i << ")" << std::endl;
            std::cout << "Error no child for index " << i << std::endl;
            return m_p4Child[0];
        }
        if (!m_calculate) Calculate();
        return m_p4Child[i];
    }
    const double& Mass() {
        if (!m_calculate) Calculate();
        return m_mass;
    }
    const double& RawMass() {
        if (!m_calculate) Calculate();
        return m_rawMass;
    }
    void SetP4(const HepLorentzVector& p4) {
        m_p4 = p4;
        m_mass = p4.m();
    }
    const double& DecayLength() {
        if (!m_calculate) Calculate();
        return m_decayLength;
    }
    const double& DecayLengthError() {
        if (!m_calculate) Calculate();
        return m_decayLError;
    }
    const double& DecayLengthRatio() {
        if (!m_calculate) Calculate();
        return m_decayLength / m_decayLError;
    }
    const double& VertexFitChisq() {
        if (!m_calculate) Calculate();
        return m_vertexFitChisq;
    }
    const double& SecondVertexFitChisq() {
        if (!m_calculate) Calculate();
        return m_secondVertexFitChisq;
    }
    // for compatiable
    const double& m() { return this->Mass(); }
    const double& chi2() { return this->SecondVertexFitChisq(); }
    const double& vtxChi2() { return this->VertexFitChisq(); }
    const double& chisq() { return this->VertexFitChisq(); }
    // ...
    void SetPrimaryVertex(VertexParameter& privtxpar) {
        m_privtxpar = privtxpar;
        m_isSetPriVtx = true;
        m_calculate = false;
    }
    std::pair<FirstInfo, SecondInfo>& Decay() {
        if (!m_calculate) Calculate();
        return std::make_pair<m_firstInfo, m_secondInfo>;
    }

   private:
    bool m_calculate, m_isSetPriVtx;
    int m_pid;
    HepLorentzVector m_p4, m_rawp4;
    HepLorentzVector m_p4Child[2];
    double m_mass, m_rawMass;
    double m_decayLength, m_decayLError;
    double m_vertexFitChisq, m_secondVertexFitChisq;
    FirstInfo m_firstInfo;
    SecondInfo m_secondInfo;
    WTrackParameter m_wVirtualTrack;
    VertexParameter m_vpar;
    VertexParameter m_privtxpar;
    void AddInfo(const vector<string>& allInfo, const string& type,
                 const string& name) {
        if (allInfo.empty()) {
            return;
        }
        string index;
        int length;
        for (vector<string>::const_iterator itr = allInfo.begin();
             itr != allInfo.end(); ++itr) {
            index = m_firstInfo.GetIndex(*itr);
            if (index != string("NULL")) {
                Add((*itr) + name, type, index);
            } else {
                length = m_firstInfo.GetLength(*itr);
                Add((*itr) + name, type, length);
            }
        }
    }
    void AddAvialInfo() {
        AddInfo(m_firstInfo.GetType("int"), "int", m_firstInfo.GetName());
        AddInfo(m_firstInfo.GetType("double"), "double", m_firstInfo.GetName());
        AddInfo(m_firstInfo.GetType("HepLorentzVector"), "HepLorentzVector",
                m_firstInfo.GetName());
        AddInfo(m_secondInfo.GetType("int"), "int", m_secondInfo.GetName());
        AddInfo(m_secondInfo.GetType("double"), "double",
                m_secondInfo.GetName());
        AddInfo(m_secondInfo.GetType("HepLorentzVector"), "HepLorentzVector",
                m_secondInfo.GetName());
        if (DoVertexFit()) {
            Add("decayLength", "double");
            Add("decayLengthError", "double");
            Add("decayLengthRatio", "double");
            Add("VertexFitChisq", "double");
            Add("SecondVertexFitChisq", "double");
            Add("RawMass", "double");
            Add("RawP4", "HepLorentzVector");
        }
        Add("Mass", "double");
        Add("p4", "HepLorentzVector");
    }
};
#endif
