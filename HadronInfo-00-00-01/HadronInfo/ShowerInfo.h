#ifndef CLASS_ShowerInfo_H
#define CLASS_ShowerInfo_H

//#include "GaudiKernel/ObjectVector.h"
//#include "GaudiKernel/AlgFactory.h"
//#include "GaudiKernel/Algorithm.h"
//#include "GaudiKernel/NTuple.h"
//#include "GaudiKernel/IDataProviderSvc.h"

#include "EvtRecEvent/EvtRecTrack.h"
#include "VertexFit/WTrackParameter.h"
#include "VertexFit/VertexFit.h"
//#include "EvtRecEvent/EvtRecDTag.h"

#include <iostream>
#include "CLHEP/Vector/LorentzVector.h"
#include "VertexFit/KalmanKinematicFit.h"
#include "BesDChain/CDDecay.h"
#include "HadronInfo/AvailableInfo.h"

class ShowerInfo : virtual public AvailableInfo {
   public:
    ShowerInfo();
    ShowerInfo(const CDCandidate &aTrk);
    void Feed(const CDCandidate &aTrk);
    ~ShowerInfo();
    //  virtual const double &GetDoubleInfo(const std::string &);
    // virtual const HepLorentzVector &GetLorentzVector(const std::string
    // &info_name);
    virtual void GetInfoH(const std::string &info_name,
                         HepLorentzVector &targe) {
        if (info_name == "p4") {
            targe = this->P4();
            return;
        }
    }
    int Charge() { return 0; }

    void SetChild(EvtRecTrack *shower) { m_shower = shower; }
    EvtRecTrack *GetChild() { return m_shower; }
    HepLorentzVector P4();
    void SetEnergyThreshold(double energyThreshold_b,
                            double energyThreshold_e) {
        m_energyThreshold_b = energyThreshold_b;
        m_energyThreshold_e = energyThreshold_e;
    }
    void SetCosTheta(double costheta_b, double costheta_e1,
                     double costheta_e2) {
        m_costheta_b = costheta_b;
        m_costheta_e1 = costheta_e1;
        m_costheta_e2 = costheta_e2;
    }
    WTrackParameter& WTrk() {
        RecEmcShower *shower = m_shower->emcShower();
        double eraw = shower->energy();
        double phi = shower->phi();
        double the = shower->theta();
        m_p4.setPx(eraw * sin(the) * cos(phi));
        m_p4.setPy(eraw * sin(the) * sin(phi));
        m_p4.setPz(eraw * cos(the));
        m_p4.setE(eraw);

        double dphi = shower->dphi();
        double dtheta = shower->dtheta();
        double dE = shower->dE();
        m_wtrk = WTrackParameter(m_p4, dphi, dtheta, dE);
        return m_wtrk;
    }
    virtual bool DoVertexFit() {return false;}
    void SetPrimaryVertex(VertexParameter &vpar) {};
    void UpdateWTrk(const WTrackParameter &newWtrk){};
    bool IsBad() { return m_badshower; }
    // ShowerInfo &operator=(ShowerInfo &aShowerInfo);
    bool Calculate();

   private:
    EvtRecTrack *m_shower;
    WTrackParameter m_wtrk;
    HepLorentzVector m_p4;
    double m_energyThreshold_b;
    double m_energyThreshold_e;
    double m_costheta_b;
    double m_costheta_e1;
    double m_costheta_e2;
    bool m_badshower;
    bool m_cal;
    void AddAvialInfo() { AvailableInfo::Add("p4", "HepLorentzVector"); }
};
#endif
