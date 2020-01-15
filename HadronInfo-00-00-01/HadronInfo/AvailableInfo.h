/* ====================================================
#   Copyright (C)2019 All rights reserved.
#
#   Author        : Xin-Xin MA
#   Email         : xxmawhu@163.com
#   File Name     : AvailableInfo.h
#   Create Time   : 2019-12-04 15:17
#   Last Modified : 2019-12-04 15:17
#   Describe      :
#
# ====================================================*/
#ifndef _AVAILABLEInfo_H
#define _AVAILABLEInfo_H
#include "CLHEP/Vector/LorentzVector.h"
#include <string>
#include <vector>
using std::string;
using std::vector;
using CLHEP::HepLorentzVector;
class AvailableInfo {
   public:
    AvailableInfo(){};
    ~AvailableInfo();
    virtual const string GetName() {
        return "AvailableInfo";
    };
    virtual const double& GetDoubleInfo(const string&);
    virtual const HepLorentzVector& GetLorentzVector(const string&);
    const vector<string>& GetDoubleInf();
    const vector<string>& GetIntInf();
    const vector<string>& GetP4Inf();
    void add(const string& info_name, const string& type = "double");

   private:
    vector<string> m_doubleInfo;
    vector<string> m_intInfo;
    vector<string> m_P4Info;
};

#endif  // _AVAILABLEInfo_H
