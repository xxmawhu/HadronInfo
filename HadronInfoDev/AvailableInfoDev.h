/* ====================================================
#   Copyright (C)2019 All rights reserved.
#
#   Author        : Xin-Xin MA
#   Email         : xxmawhu@163.com
#   File Name     : AvailableInfoDev.h
#   Create Time   : 2019-12-04 15:17
#   Last Modified : 2019-12-04 15:17
#   Describe      :
#
# ====================================================*/
#ifndef _AVAILABLEINFODev_H
#define _AVAILABLEINFODev_H
#include "CLHEP/Vector/LorentzVector.h"
#include <string>
#include <vector>
using std::string;
using std::vector;
using CLHEP::HepLorentzVector;
class AvailableInfoDev {
   public:
    AvailableInfoDev(){};
    ~AvailableInfoDev();
    virtual const string GetName() {
        return "AvailableInfoDev";
    };
    virtual const double& GetDoubleInfoDev(const string&);
    virtual const HepLorentzVector& GetLorentzVector(const string&);
    const vector<string>& GetDoubleInf();
    const vector<string>& GetIntInf();
    const vector<string>& GetP4Inf();
    void add(const string& info_name, const string& type = "double");

   private:
    vector<string> m_doubleInfoDev;
    vector<string> m_intInfoDev;
    vector<string> m_P4InfoDev;
};

#endif  // _AVAILABLEINFODev_H
