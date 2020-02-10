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
template <class T1, class T2, int pid, int doFit>
CombInfo<T1, T2, pid, doFit>::CombInfo() {
    m_pid = pid;
    AvailableInfo::SetName(HadronTool::Name(m_pid));
    // std::cout << "SetName(" << HadronTool::Name(m_pid)<< ")" <<
    // std::endl;
    m_firstInfo = T1();
    m_secondInfo = T2();
    this->AddAvialInfo();
    // std::cout << "GetName = " << GetName() << std::endl;
    m_calculate = true;
}

template <class T1, class T2, int pid, int doFit>
CombInfo<T1, T2, pid, doFit>::CombInfo(const CDCandidate& combParticle) {
    if (combParticle.decay().children().size() != 2) {
        cout << "Error: the numberChildren is not equal 2!" << endl;
    }
    // cout << "init with CDCandidate" << endl;
    SetName(HadronTool::Name(m_pid));
    m_firstInfo = T1(combParticle.decay().child(0));
    m_secondInfo = T2(combParticle.decay().child(1));
    m_firstInfo.SetName(m_firstInfo.GetName() + HadronTool::Name(m_pid));
    m_secondInfo.SetName(m_secondInfo.GetName() + HadronTool::Name(m_pid));
    AddAvialInfo();
    m_calculate = false;
}

template <class T1, class T2, int pid, int doFit>
CombInfo<T1, T2, pid, doFit>::CombInfo(T1& firsInfo, T2& secondInfo) {
    m_firstInfo = firsInfo;
    m_secondInfo = secondInfo;
    m_firstInfo.SetName(m_firstInfo.GetName() + HadronTool::Name(m_pid));
    m_secondInfo.SetName(m_secondInfo.GetName() + HadronTool::Name(m_pid));
    m_pid = pid;
    SetName(HadronTool::Name(m_pid));
    std::cout << "init CombInfo successful" << std::endl;
    AddAvialInfo();
    m_calculate = false;
}

template <class T1, class T2, int pid, int doFit>
void CombInfo<T1, T2, pid, doFit>::Feed(const CDCandidate& combParticle) {
    if (combParticle.decay().children().size() != 2) {
        cout << "Error: the numberChildren is not equal 2!" << endl;
    }
    // cout << "init with CDCandidate" << endl;
    m_firstInfo = T1(combParticle.decay().child(0));
    m_secondInfo = T2(combParticle.decay().child(1));
    m_firstInfo.SetName(m_firstInfo.GetName() + HadronTool::Name(m_pid));
    m_secondInfo.SetName(m_secondInfo.GetName() + HadronTool::Name(m_pid));
    m_calculate = false;
}

template <class T1, class T2, int pid, int doFit>
void CombInfo<T1, T2, pid, doFit>::Feed(T1& firsInfo, T2& secondInfo) {
    m_firstInfo = firsInfo;
    m_secondInfo = secondInfo;
    m_firstInfo.SetName(m_firstInfo.GetName() + HadronTool::Name(m_pid));
    m_secondInfo.SetName(m_secondInfo.GetName() + HadronTool::Name(m_pid));
    m_pid = pid;
    std::cout << "init CombInfo successful" << std::endl;
    m_calculate = false;
}

template <class T1, class T2, int pid, int doFit>
const bool CombInfo<T1, T2, pid, doFit>::DoVertexFit() {
    // do vertexfit
    // after vertex the children information will be update,
    // except pi0, eta, kaon...
    return doFit;
}

template <class T1, class T2, int pid, int doFit>
int CombInfo<T1, T2, pid, doFit>::Charge() {
    return m_firstInfo.Charge() + m_secondInfo.Charge();
}

template <class T1, class T2, int pid, int doFit>
void CombInfo<T1, T2, pid, doFit>::GetInfoI(const std::string& info_name,
                                            int& targe) {
    int length = info_name.size() - (this->GetName()).size();
    // std::string firstname = m_firstInfo.GetName();
    std::string tmpname = info_name.substr(0, length);
    //  m_firstInfo.GetInfoInt(firstname, length);
    //  m_firstInfo.GetInfo(firstname, length);
    // firsInfo
    std::vector<std::string> tmpAllInfo = m_firstInfo.GetType("int");
    if (std::find(tmpAllInfo.begin(), tmpAllInfo.end(), tmpname) !=
        tmpAllInfo.end()) {
        m_firstInfo.GetInfoI(tmpname, targe);
        return;
    }
    tmpAllInfo = m_secondInfo.GetType("int");
    if (std::find(tmpAllInfo.begin(), tmpAllInfo.end(), tmpname) !=
        tmpAllInfo.end()) {
        m_secondInfo.GetInfoI(tmpname, targe);
        return;
    }
    return;
}

template <class T1, class T2, int pid, int doFit>
void CombInfo<T1, T2, pid, doFit>::GetInfoD(const std::string& info_name,
                                            double& targe) {
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
    if (std::find(tmpAllInfo.begin(), tmpAllInfo.end(), tmpname) !=
        tmpAllInfo.end()) {
        m_firstInfo.GetInfoD(tmpname, targe);
        return;
    }
    tmpAllInfo = m_secondInfo.GetType("double");
    if (std::find(tmpAllInfo.begin(), tmpAllInfo.end(), tmpname) !=
        tmpAllInfo.end()) {
        m_secondInfo.GetInfoD(tmpname, targe);
        return;
    }
    return;
}

template <class T1, class T2, int pid, int doFit>
void CombInfo<T1, T2, pid, doFit>::GetInfoH(const std::string& info_name,
                                            HepLorentzVector& targe) {
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
    std::vector<std::string> tmpAllInfo =
        m_firstInfo.GetType("HepLorentzVector");
    if (std::find(tmpAllInfo.begin(), tmpAllInfo.end(), tmpname) !=
        tmpAllInfo.end()) {
        m_firstInfo.GetInfoH(tmpname, targe);
        return;
    }
    tmpAllInfo = m_secondInfo.GetType("HepLorentzVector");
    if (std::find(tmpAllInfo.begin(), tmpAllInfo.end(), tmpname) !=
        tmpAllInfo.end()) {
        m_secondInfo.GetInfoH(tmpname, targe);
        return;
    }
    return;
}

template <class T1, class T2, int pid, int doFit>
void CombInfo<T1, T2, pid, doFit>::GetInfoVi(const std::string& info_name,
                                             std::vector<int>& targe) {
    int length = info_name.size() - (this->GetName()).size();
    std::string tmpname = info_name.substr(0, length);
    // firsInfo
    std::vector<std::string> tmpAllInfo = m_firstInfo.GetType("int");
    if (std::find(tmpAllInfo.begin(), tmpAllInfo.end(), tmpname) !=
        tmpAllInfo.end()) {
        m_firstInfo.GetInfoVi(tmpname, targe);
        return;
    }
    tmpAllInfo = m_secondInfo.GetType("int");
    if (std::find(tmpAllInfo.begin(), tmpAllInfo.end(), tmpname) !=
        tmpAllInfo.end()) {
        m_secondInfo.GetInfoVi(tmpname, targe);
        return;
    }
    return;
}

template <class T1, class T2, int pid, int doFit>
void CombInfo<T1, T2, pid, doFit>::GetInfoVd(const std::string& info_name,
                                             std::vector<double>& targe) {
    int length = info_name.size() - (this->GetName()).size();
    std::string tmpname = info_name.substr(0, length);
    // firsInfo
    std::vector<std::string> tmpAllInfo = m_firstInfo.GetType("double");
    if (std::find(tmpAllInfo.begin(), tmpAllInfo.end(), tmpname) !=
        tmpAllInfo.end()) {
        m_firstInfo.GetInfoVd(tmpname, targe);
        return;
    }
    tmpAllInfo = m_secondInfo.GetType("double");
    if (std::find(tmpAllInfo.begin(), tmpAllInfo.end(), tmpname) !=
        tmpAllInfo.end()) {
        m_secondInfo.GetInfoVd(tmpname, targe);
        return;
    }
    return;
}

template <class T1, class T2, int pid, int doFit>
bool CombInfo<T1, T2, pid, doFit>::Calculate() {
    if (m_calculate) {
        return true;
    }
    m_rawp4 = m_firstInfo.P4() + m_secondInfo.P4();
    m_rawMass = m_rawp4.m();
    if (!doFit) {
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

template <class T1, class T2, int pid, int doFit>
void CombInfo<T1, T2, pid, doFit>::UpdateWTrk(const WTrackParameter& newWtrk) {
    m_wVirtualTrack = newWtrk;
    m_p4 = newWtrk.p();
    m_mass = newWtrk.mass();
}
template <class T1, class T2, int pid, int doFit>
const WTrackParameter& WTrk() {
    if (!m_calculate) Calculate();
    return m_wVirtualTrack;
}
template <class T1, class T2, int pid, int doFit>
const HepLorentzVector& CombInfo<T1, T2, pid, doFit>::P4() {
    if (!m_calculate) Calculate();
    return m_p4;
}
template <class T1, class T2, int pid, int doFit>
const HepLorentzVector& CombInfo<T1, T2, pid, doFit>::RawP4() {
    if (!m_calculate) Calculate();
    return m_rawp4;
}
template <class T1, class T2, int pid, int doFit>
const HepLorentzVector& CombInfo<T1, T2, pid, doFit>::P4Child(const int& i) {
    if (i != 0 && i != 1) {
        std::cout << this->GetName() + ".P4Child(" << i << ")" << std::endl;
        std::cout << "Error no child for index " << i << std::endl;
        return m_p4Child[0];
    }
    if (!m_calculate) Calculate();
    return m_p4Child[i];
}
template <class T1, class T2, int pid, int doFit>
const double& CombInfo<T1, T2, pid, doFit>::Mass() {
    if (!m_calculate) Calculate();
    return m_mass;
}
template <class T1, class T2, int pid, int doFit>
const double& CombInfo<T1, T2, pid, doFit>::RawMass() {
    if (!m_calculate) Calculate();
    return m_rawMass;
}
template <class T1, class T2, int pid, int doFit>
void CombInfo<T1, T2, pid, doFit>::SetP4(const HepLorentzVector& p4) {
    m_p4 = p4;
    m_mass = p4.m();
}
template <class T1, class T2, int pid, int doFit>
const double& CombInfo<T1, T2, pid, doFit>::DecayLength() {
    if (!m_calculate) Calculate();
    return m_decayLength;
}
template <class T1, class T2, int pid, int doFit>
const double& CombInfo<T1, T2, pid, doFit>::DecayLengthError() {
    if (!m_calculate) Calculate();
    return m_decayLError;
}
template <class T1, class T2, int pid, int doFit>
const double& CombInfo<T1, T2, pid, doFit>::DecayLengthRatio() {
    if (!m_calculate) Calculate();
    return m_decayLength / m_decayLError;
}
template <class T1, class T2, int pid, int doFit>
const double& CombInfo<T1, T2, pid, doFit>::VertexFitChisq() {
    if (!m_calculate) Calculate();
    return m_vertexFitChisq;
}
template <class T1, class T2, int pid, int doFit>
const double& CombInfo<T1, T2, pid, doFit>::SecondVertexFitChisq() {
    if (!m_calculate) Calculate();
    return m_secondVertexFitChisq;
}
template <class T1, class T2, int pid, int doFit>
void CombInfo<T1, T2, pid, doFit>::SetPrimaryVertex(
    VertexParameter& privtxpar) {
    m_privtxpar = privtxpar;
    m_isSetPriVtx = true;
    m_calculate = false;
}
template <class T1, class T2, int pid, int doFit>
std::pair<T1, T2>& CombInfo<T1, T2, pid, doFit>::Decay() {
    if (!m_calculate) Calculate();
    return std::make_pair<m_firstInfo, m_secondInfo>;
}

template <class T1, class T2, int pid, int doFit>
void CombInfo<T1, T2, pid, doFit>::AddInfo(
    const vector<string>& allInfo, const std::map<string, string>& allindexInfo,
    const std::map<string, int>& allLengthInfo, const string& type,
    const string& name) {
    cout << "Info in <CombInfo::AddInfo>: "
         << "type = " << type << endl;
    if (allInfo.empty()) {
        cout << "Info in <CombInfo::AddInfo>: "
             << "allInfo is empty " << endl;
        return;
    }
    string index;
    int length;
    for (vector<string>::const_iterator itr = allInfo.begin();
         itr != allInfo.end(); ++itr) {
        index = allindexInfo.find(*itr)->second;
        if (index != string("NULL")) {
            Add((*itr) + name, type, index);
        } else {
            length = allLengthInfo.find(*itr)->second;
            Add((*itr) + name, type, length);
        }
    }
}
template <class T1, class T2, int pid, int doFit>
void CombInfo<T1, T2, pid, doFit>::AddAvialInfo() {
    AddInfo(m_firstInfo);
    AddInfo(m_secondInfo);
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
