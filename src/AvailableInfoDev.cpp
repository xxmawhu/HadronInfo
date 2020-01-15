/* ====================================================
#   Copyright (C)2019 All rights reserved.
#
#   Author        : Xin-Xin MA
#   Email         : xxmawhu@163.com
#   File Name     : AvailableInfoDev.cxx
#   Create Time   : 2019-12-04 15:17
#   Last Modified : 2019-12-12 09:51
#   Describe      :
#
# ====================================================*/
#include "CLHEP/Vector/LorentzVector.h"
#include "HadronInfoDev/AvailableInfoDev.h"
#include <string>
#include <vector>
using std::string;
using std::vector;
using CLHEP::HepLorentzVector;

AvailableInfoDev::~AvailableInfoDev() {
    m_doubleInfoDev.clear();
    m_P4InfoDev.clear();
}

const double& AvailableInfoDev::GetDoubleInfoDev(const string&) { return -999; }

const HepLorentzVector& AvailableInfoDev::GetLorentzVector(const string&) {
    return HepLorentzVector(0, 0, 0, -999);
}

void AvailableInfoDev::add(const string& info_name, const string& type) {
    if (type == "double") {
        m_doubleInfoDev.push_back(info_name);
    } else if (type == "int") {
        m_intInfoDev.push_back(info_name);
    } else {
        m_P4InfoDev.push_back(info_name);
    }
}
const vector<string>& AvailableInfoDev::GetDoubleInf() { return m_doubleInfoDev; }
const vector<string>& AvailableInfoDev::GetIntInf() { return m_intInfoDev; }
const vector<string>& AvailableInfoDev::GetP4Inf() { return m_P4InfoDev; }
