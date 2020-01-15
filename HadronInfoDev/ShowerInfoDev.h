#ifndef CLASS_ShowerINFODev_H
#define CLASS_ShowerINFODev_H

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
#include "BesDChain/CDDecay.h"
#include "HadronInfoDev/AvailableInfoDev.h"

using namespace std;
class ShowerInfoDev : public AvailableInfoDev {
   public:
    ShowerInfoDev();
    ShowerInfoDev(const CDCandidate &aTrk);
    ~ShowerInfoDev();
    virtual const string GetName() { return "Shower"; }
    virtual const double& GetDoubleInfoDev(const string &);
    virtual const HepLorentzVector &GetLorentzVector(const string &info_name);

    void setchild(EvtRecTrack *shower) { m_shower = shower; }
    EvtRecTrack *getchild() { return m_shower; }
    HepLorentzVector p4();
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
    bool isBad() { return m_badshower; }
    ShowerInfoDev &operator=(ShowerInfoDev &aShowerInfoDev);
    bool calculate();

   private:
    EvtRecTrack *m_shower;

    HepLorentzVector m_p4;
    double m_energyThreshold_b;
    double m_energyThreshold_e;
    double m_costheta_b;
    double m_costheta_e1;
    double m_costheta_e2;
    bool m_badshower;
    bool m_cal;
    void addAvialInfoDev() { AvailableInfoDev::add("p4", "HepLorentzVector"); }
};
#endif
