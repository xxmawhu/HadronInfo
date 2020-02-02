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

AvailableInfo::~AvailableInfo() { m_allInfo.clear(); }

const double& AvailableInfo::GetDoubleInfo(const string&) { return -999; }

const HepLorentzVector& AvailableInfo::GetLorentzVector(const string&) {
    return HepLorentzVector(0, 0, 0, -999);
}

void AvailableInfo::add(const string& info_name, const string& type) {
    // check wether the type exist in the map
    if (m_allInfo.find(type) == m_allInfo.end()) {
        vector<string> tmp;
        tmp.push_back(info_name);
        m_allInfo.insert(std::make_pair(type, tmp));
    } else {
        m_allInfo[type].push_back(info_name);
    }
}
const vector<string>& AvailableInfo::GetDoubleInf() {
    return m_allInfo["double"];
}
const vector<string>& AvailableInfo::GetIntInf() { return m_allInfo["int"]; }
const vector<string>& AvailableInfo::GetP4Inf() {
    return m_allInfo["HepLorentzVector"];
}
const vector<string>& AvailableInfo::GetVectorInf() {
    return m_allInfo["vector"];
}
const vector<string>& AvailableInfo::GetType(const std::string& type) {
    return m_allInfo[type];
}
