#ifndef CLASS_ShowerINFO_H
#define CLASS_ShowerINFO_H

//#include "GaudiKernel/ObjectVector.h"
//#include "GaudiKernel/AlgFactory.h"
//#include "GaudiKernel/Algorithm.h"
//#include "GaudiKernel/NTuple.h"
//#include "GaudiKernel/IDataProviderSvc.h"

#include "EvtRecEvent/EvtRecTrack.h"
//#include "EvtRecEvent/EvtRecDTag.h"

#include <iostream>
#include "CLHEP/Vector/LorentzVector.h"
#include "VertexFit/KalmanKinematicFit.h"
#include "HadronInfo/AvailableInfo.h"

using namespace std;
class ShowerInfo : public AvailableInfo {
   public:
    ShowerInfo();
    ~ShowerInfo();
    virtual double GetDoubleInfo(const string &);
    virtual HepLorentzVector GetLorentzVector(const string &info_name);

    void setchilds(EvtRecTrack *shower) { m_shower = shower; }
    EvtRecTrack *getchild() { return m_shower; }
    HepLorentzVector p4() { return m_p4; }
    void setEnergyThreshold(double energyThreshold_b,
                            double energyThreshold_e) {
        m_energyThreshold_b = energyThreshold_b;
        m_energyThreshold_e = energyThreshold_e;
    }
    void setCosTheta(double costheta_b, double costheta_e1,
                     double costheta_e2) {
        m_costheta_b = costheta_b;
        m_costheta_e1 = costheta_e1;
        m_costheta_e2 = costheta_e2;
    }
    bool isBad() { return m_badpi0; }
    ShowerInfo &operator=(ShowerInfo &aShowerInfo);
    bool calculate();

   private:
    EvtRecTrack *m_shower;

    HepLorentzVector m_p4;
    double m_energyThreshold_b;
    double m_energyThreshold_e;
    double m_costheta_b;
    double m_costheta_e1;
    double m_costheta_e2;
    bool m_badpi0;
};
#endif
