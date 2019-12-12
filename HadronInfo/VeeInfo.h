#ifndef CLASS_VEEINFO_H
#define CLASS_VEEINFO_H

//#include "GaudiKernel/ObjectVector.h"
//#include "GaudiKernel/AlgFactory.h"
//#include "GaudiKernel/Algorithm.h"
//#include "GaudiKernel/NTuple.h"
//#include "GaudiKernel/IDataProviderSvc.h"

#include "EvtRecEvent/EvtRecTrack.h"
//#include "EvtRecEvent/EvtRecDTag.h"
#include "VertexFit/VertexFit.h"
#include "VertexFit/SecondVertexFit.h"
#include "VertexFit/IVertexDbSvc.h"
#include "CLHEP/Vector/LorentzVector.h"
#include "HadronInfo/AvailableInfo.h"
#include "GaudiKernel/ISvcLocator.h"
#include "GaudiKernel/Bootstrap.h"

#include "BesDChain/CDDecay.h"
#include <iostream>
using namespace std;

class VeeInfo : public AvailableInfo {
   public:
    VeeInfo(const string &name1 = "First", const string &name2 = "Second")
        : AvailableInfo() {
        m_cal = false;
        m_childName[0] = name1;
        m_childName[1] = name2;
        addAvialInfo();
    }
    VeeInfo(const CDCandidate &aVee, const string &name1 = "First",
            const string &name2 = "Second")
        : AvailableInfo() {
        const EvtRecTrack *trk0 = aVee.finalChildren().first[0];
        const EvtRecTrack *trk1 = aVee.finalChildren().first[1];
        m_track0 = const_cast<EvtRecTrack *>(trk0);
        m_track1 = const_cast<EvtRecTrack *>(trk1);
        m_cal = false;
        m_childName[0] = name1;
        m_childName[1] = name2;
        addAvialInfo();
    }
    VeeInfo(const EvtRecTrack *track0, const EvtRecTrack *track1,
            const string &name1 = "First", const string &name2 = "Second")
        : AvailableInfo() {
        this->setchild(0, track0);
        this->setchild(1, track1);
        m_childName[0] = name1;
        m_childName[1] = name2;
        addAvialInfo();
    }
    void setchild(const int &n, const EvtRecTrack *track) {
        if (n == 0) {
            m_track0 = const_cast<EvtRecTrack *>(track);
        } else if (n == 1) {
            m_track1 = const_cast<EvtRecTrack *>(track);
        }
        m_cal = false;
    }
    void setchilds(const EvtRecTrack *track0, const EvtRecTrack *track1) {
        m_track0 = const_cast<EvtRecTrack *>(track0);
        m_track1 = const_cast<EvtRecTrack *>(track1);
        m_cal = false;
    }
    virtual const string GetName() { return "Vee";}

    string getChildName(const int &i) { return m_childName[i]; }
    void setChildName(const int &i, const string &name) {
        m_childName[i] = name;
    }
    void setChildName(const string &name1, const string &name2) {
        m_childName[0] = name1;
        m_childName[1] = name2;
    }
    ~VeeInfo() {}
    virtual const double &GetDoubleInfo(const string &info_name) {
        if (info_name == "mass") return this->m();
        if (info_name == "vtxChi2") return this->vtxChi2();
        if (info_name == "chisq") return this->chisq();
        if (info_name == "decayLength") return this->decayLength();
        if (info_name == "decayLengthRatio") return this->decayLengthRatio();
        if (info_name == "decayLengthError") return this->decayLengthError();
        return -110;
    }
    virtual const HepLorentzVector &GetLorentzVector(const string &info_name) {
        if (info_name == "p4") return this->p4();
        if (info_name == "p4" + getChildName(0)) return this->p4child(0);
        if (info_name == "p4" + getChildName(1)) return this->p4child(1);
        if (info_name == "p4Fit" + getChildName(0)) return this->p4fit(0);
        if (info_name == "p4Fit" + getChildName(1)) return this->p4fit(1);
        return HepLorentzVector(0, 0, 0, -110);
    }
    EvtRecTrack *getchild(const int &i) {
        if (i == 0) {
            return m_track0;
        } else {
            return m_track1;
        }
    }
    bool calculated() { return m_cal; }
    void setCalculated(const bool &cal) { m_cal = cal; }
    virtual bool calculate() {
        if (m_cal) {
            return true;
        }
        m_cal = true;
        return true;
    }

    void setMass(const double &mass) { m_mass = mass; }
    void setM(const double &mass) { this->setMass(mass); }
    void setRawMass(const double &mass) { m_rawmass = mass; }
    void setChi2(const double &chisq) { m_chisqSecond = chisq; }
    void setVtxChi2(const double &chisq) { m_chisqFirst = chisq; }
    void setDecayLength(const double &dL) { m_decayLength = dL; }
    void setDecayLengthRatio(const double &ratio) {
        m_decayLengthRatio = ratio;
    }
    void setDecayLengthError(const double &decayError) {
        m_decayLengthError = decayError;
    }
    double mass() {
        if (!m_cal) {
            calculate();
            m_cal = true;
        }
        return m_mass;
    }
    inline double m() { return this->mass(); }
    double rawmass() {
        if (!m_cal) {
            calculate();
            m_cal = true;
        }
        return m_rawmass;
    }
    double chisqFirst() {
        if (!m_cal) {
            calculate();
            m_cal = true;
        }
        return m_chisqFirst;
    }
    inline double vtxChi2() { return this->chisqFirst(); }
    double chisqSecond() {
        if (!m_cal) {
            calculate();
            m_cal = true;
        }
        return m_chisqSecond;
    }
    inline double chi2() { return this->chisqSecond(); }
    inline double chisq() { return this->chisqSecond(); }
    double decayLength() {
        if (!m_cal) {
            calculate();
            m_cal = true;
        }
        return m_decayLength;
    }
    double decayLengthRatio() {
        if (!m_cal) {
            calculate();
            m_cal = true;
        }
        return m_decayLengthRatio;
    }
    double decayLengthError() {
        if (!m_cal) {
            calculate();
            m_cal = true;
        }
        return m_decayLengthError;
    }
    void setP4Child(const HepLorentzVector &p4, const int &i) {
        m_p4child[i] = p4;
    }
    void setP4Fit(const HepLorentzVector &p4, const int &i) { m_p4fit[i] = p4; }
    void setP4(const HepLorentzVector &p4) {
        m_p4 = p4;
        m_mass = p4.m();
    }
    HepLorentzVector &p4() {
        if (!m_cal) {
            calculate();
            m_cal = true;
        }
        return m_p4;
    }
    HepLorentzVector &p4child(const int &i) {
        if (!m_cal) {
            calculate();
            m_cal = true;
        }
        return m_p4child[i];
    }
    HepLorentzVector &p4fit(const int &i) {
        if (!m_cal) {
            calculate();
            m_cal = true;
        }
        return m_p4fit[i];
    }
    HepLorentzVector &pfit(const int &i) { return this->p4fit(i); }
    WTrackParameter wtrk() {
        if (!m_cal) {
            calculate();
            m_cal = true;
        }
        return m_wVirtualTrack;
    }
    void setWTrackParameter(const WTrackParameter &wTrack) {
        m_wVirtualTrack = wTrack;
    }
    VertexParameter vtxPar() {
        if (!m_cal) {
            calculate();
            m_cal = true;
        }
        return m_vpar;
    }
    void setWTrk(const WTrackParameter &wTrack) { m_wVirtualTrack = wTrack; }
    WTrackParameter &wtrk(const int &n) {
        if (!m_cal) {
            calculate();
            m_cal = true;
        }
        return m_wtrk[n];
    }
    void setWTrk(const int &i, const WTrackParameter &wTrack) {
        m_wtrk[i] = wTrack;
    }
    void setPrimaryVtxPar(VertexParameter &privtxpar);
    VertexParameter &getPrimaryVertex() {
        if (m_cal) {
            return m_privtxpar;
        } else {
            VertexParameter beamSpot;
            HepPoint3D vBeamSpot(0., 0., 0.);
            HepSymMatrix evBeamSpot(3, 0);
            IVertexDbSvc *vtxsvc;
            Gaudi::svcLocator()->service("VertexDbSvc", vtxsvc);
            double *dbv = vtxsvc->PrimaryVertex();
            double *vv = vtxsvc->SigmaPrimaryVertex();
            for (unsigned int ivx = 0; ivx < 3; ivx++) {
                vBeamSpot[ivx] = dbv[ivx];
                evBeamSpot[ivx][ivx] = vv[ivx] * vv[ivx];
            }
            beamSpot.setVx(vBeamSpot);
            beamSpot.setEvx(evBeamSpot);
            return beamSpot;
        }
    }
    VertexParameter &getWideVertex() {
        VertexParameter wideVertex;
        HepPoint3D vWideVertex(0., 0., 0.);
        HepSymMatrix evWideVertex(3, 0);

        evWideVertex[0][0] = 1.0e12;
        evWideVertex[1][1] = 1.0e12;
        evWideVertex[2][2] = 1.0e12;

        wideVertex.setVx(vWideVertex);
        wideVertex.setEvx(evWideVertex);
        return wideVertex;
    }
    VertexParameter primaryVtxPar() {
        if (!m_cal) {
            calculate();
            m_cal = true;
        }
        return m_privtxpar;
    }
    bool init();

   private:
    HepLorentzVector m_p4;
    HepLorentzVector m_p4fit[2];
    HepLorentzVector m_p4child[2];
    HepLorentzVector m_p4child0;
    HepLorentzVector m_p4child1;
    VertexParameter m_vpar;
    VertexParameter m_privtxpar;
    WTrackParameter m_wVirtualTrack;
    WTrackParameter m_wtrk[2];
    HepPoint3D m_2ndVtx;
    bool m_cal, m_isSetPriVtx;
    double m_rawmass, m_mass;
    double m_chisqFirst, m_chisqSecond;
    double m_decayLength, m_decayLengthError, m_decayLengthRatio;
    string m_childName[2];
    EvtRecTrack *m_track0, *m_track1;
    virtual void addAvialInfo() {
        AvailableInfo::add("mass", "double");
        AvailableInfo::add("rawmass", "double");
        AvailableInfo::add("vertexFitChisq", "double");
        AvailableInfo::add("secondVertexFitChisq", "double");
        AvailableInfo::add("decayLength", "double");
        AvailableInfo::add("decayLengthError", "double");
        AvailableInfo::add("decayLengthRatio", "double");
        AvailableInfo::add("p4", "HepLorentzVector");
        AvailableInfo::add("p4" + getChildName(0), "HepLorentzVector");
        AvailableInfo::add("p4" + getChildName(1), "HepLorentzVector");
        AvailableInfo::add("p4Fit" + getChildName(0), "HepLorentzVector");
        AvailableInfo::add("p4Fit" + getChildName(1), "HepLorentzVector");
    }

   protected:
    //  VeeInfo &operator=(VeeInfo &aVeeInfo) {
    //      this->setM(aVeeInfo.m());
    //      m_p4 = aVeeInfo.p4();
    //      m_rawmass = aVeeInfo.rawmass();
    //      m_mass = aVeeInfo.m();
    //      m_chisqFirst = aVeeInfo.chisqFirst();
    //      m_chisqSecond = aVeeInfo.chi2();
    //      m_decayLength = aVeeInfo.decayLength();
    //      m_decayLengthRatio = aVeeInfo.decayLengthRatio();
    //      m_decayLengthError = aVeeInfo.decayLengthError();
    //      return *this;
    //  }
};
#endif
