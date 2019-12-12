/* ====================================================
#   Copyright (C)2019 All rights reserved.
#
#   Author        : Xin-Xin MA
#   Email         : xxmawhu@163.com
#   File Name     : AvailableInfo.cxx
#   Create Time   : 2019-12-04 15:17
#   Last Modified : 2019-12-12 09:51
#   Describe      :
#
# ====================================================*/
#include "CLHEP/Vector/LorentzVector.h"
#include "HadronInfo/AvailableInfo.h"
#include <string>
#include <vector>
using std::string;
using std::vector;
using CLHEP::HepLorentzVector;

AvailableInfo::~AvailableInfo() {
    m_doubleInfo.clear();
    m_P4Info.clear();
}

const double& AvailableInfo::GetDoubleInfo(const string&) { return -999; }

const HepLorentzVector& AvailableInfo::GetLorentzVector(const string&) {
    return HepLorentzVector(0, 0, 0, -999);
}

void AvailableInfo::add(const string& info_name, const string& type) {
    if (type == "double") {
        m_doubleInfo.push_back(info_name);
    } else if (type == "int") {
        m_intInfo.push_back(info_name);
    } else {
        m_P4Info.push_back(info_name);
    }
}
const vector<string>& AvailableInfo::GetDoubleInf() { return m_doubleInfo; }
const vector<string>& AvailableInfo::GetIntInf() { return m_intInfo; }
const vector<string>& AvailableInfo::GetP4Inf() { return m_P4Info; }
