#ifndef CLASS_HadronInfo_GGInfo_H
#define CLASS_HadronInfo_GGInfo_H

#include "EvtRecEvent/EvtRecTrack.h"

#include "CLHEP/Vector/LorentzVector.h"
#include "VertexFit/KalmanKinematicFit.h"
#include "BesDChain/CDDecay.h"
#include "HadronInfo/AvailableInfo.h"

#include <iostream>

using namespace std;
class GGInfo : public AvailableInfo {
   public:
    GGInfo():AvailableInfo(){
    }
    ~GGInfo(){};
    virtual double GetDoubleInfo(const string & info_name){
        return -999;
    }
    virtual HepLorentzVector GetLorentzVector(const string &info_name){
        return HepLorentzVector(0, 0, 0, -999);
    }
    double m(){
        if (!m_calculate) calculate();
        return m_mpi0;
    }
    double m1c(){
        if (!m_calculate) calculate();
        return m_mpi01c;
    }
    double angle(){
        if (!m_calculate) calculate();
        return m_pi0_heliAngle;
    }
    double openAngle(){
        if (!m_calculate) calculate();
        return m_openAngle;
    }
    double helicity(){
        if (!m_calculate) calculate();
        return m_helicity;
    }
    HepLorentzVector p4(){
        if (!m_calculate) calculate();
        return m_rawP4; 
    }
    HepLorentzVector p41c(){
        if (!m_calculate) calculate();
        return m_P41C; 
    }
    HepLorentzVector p4child(const int &i){
        if (!m_calculate) calculate();
        return m_rawP4Child[i];
    }
    HepLorentzVector p4GammHigh(){
        if (!m_calculate) calculate();
        if (m_rawP4Child[0].e()  > m_rawP4Child[1].e()){
            return m_rawP4Child[0];
        } else {
            return m_rawP4Child[1];
        }
    }

    HepLorentzVector p4GammLow(){
        if (!m_calculate) calculate();
        if (m_rawP4Child[0].e()  < m_rawP4Child[1].e()){
            return m_rawP4Child[0];
        } else {
            return m_rawP4Child[1];
        }
    }
    double chisq(){
        if (!m_calculate) calculate();
        return m_chisq;
    }
    bool isGood(){
        if (!m_calculate) calculate();
        return m_isgoodpi0;
    }
    WTrackParameter wtrk(){
        if (!m_calculate) calculate();
        return m_wtrk; 
    }
    // GGInfo &operator=(GGInfo &aGGInfo);
    virtual bool calculate(){
        m_calculate = true;
    }
    void setWTrackParameter(const WTrackParameter& wtrk){
        m_wtrk = wtrk;
    }
    void setRawMass(const double& mass){
        m_mpi0 = mass;
    }
    void setHelicity(const double& helicity){
        m_helicity = helicity;
    }
    void setOpenAngle(const double& openangle){
        m_openAngle = openangle;
    }
    void setChisq(const double& chisq){
        m_chisq = chisq;
    }
    void setP41C(const HepLorentzVector& p4) {
        m_P41C = p4;
    }
    void setRawP4(const HepLorentzVector& p4){
        m_rawP4 = p4;
    }
    void setP4Child(const HepLorentzVector& p4, const int& i){
        m_rawP4Child[i] = p4;
    }

   private:
    WTrackParameter m_wtrk;
    bool isGoodPhoton(EvtRecTrack *);
    HepLorentzVector m_rawP4;
    HepLorentzVector m_P41C;
    HepLorentzVector m_rawP4Child[2];
    double constrain_mass;
    double m_mpi0;
    double m_mpi01c;
    double m_pi0_heliAngle;
    double m_helicity;
    double m_openAngle;
    double m_chisq;
    bool m_isgoodpi0, m_calculate;
    void initAvialableInfo() {
        AvailableInfo::add("mass", "double");
        AvailableInfo::add("mass1C", "double");
        AvailableInfo::add("angle", "double");
        AvailableInfo::add("openAngle", "double");
        AvailableInfo::add("helicity", "double");
        AvailableInfo::add("p4", "HepLorentzVector");
        AvailableInfo::add("p41C", "HepLorentzVector");
        AvailableInfo::add("p4GammaHigh", "HepLorentzVector");
        AvailableInfo::add("p4GammaLow", "HepLorentzVector");
    }
};
#endif
