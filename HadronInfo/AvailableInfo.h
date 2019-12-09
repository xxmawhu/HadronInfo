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
#ifndef _AVAILABLEINFO_H
#define _AVAILABLEINFO_H
#include "CLHEP/Vector/LorentzVector.h"
#include <string>
using std::string;
using CLHEP::HepLorentzVector;
class AvailableInfo {
   public:
    AvailableInfo() {};
    ~AvailableInfo() {
        m_doubleInfo.clear();
        m_P4Info.clear();
    }
    virtual double GetDoubleInfo(const string &) { return -999.0; }
    virtual HepLorentzVector GetLorentzVector(const string &) {
        return HepLorentzVector(0, 0, 0, -999.9);
    }
    const vector<string>& GetDoubleInf() { return m_doubleInfo; }
    const vector<string>& GetIntInf() { return m_intInfo; }
    const vector<string>& GetP4Inf() { return m_P4Info; }
    void add(const string &info_name, const string &type = "double") {
        if (type == "double") {
            m_doubleInfo.push_back(info_name);
        } else if (type == "int") {
            m_intInfo.push_back(info_name);
        } else {
            m_P4Info.push_back(info_name);
        }
    }

   private:
    vector<string> m_doubleInfo;
    vector<string> m_intInfo;
    vector<string> m_P4Info;
};

#endif  // _AVAILABLEINFO_H
