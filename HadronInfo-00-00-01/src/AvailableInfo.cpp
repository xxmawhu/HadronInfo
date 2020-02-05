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

// const double& AvailableInfo::GetDoubleInfo(const string&) { return -999; }

// const HepLorentzVector& AvailableInfo::GetLorentzVector(const string&) {
//    return HepLorentzVector(0, 0, 0, -999);
// }

void AvailableInfo::Add(const string& info_name, const string& type,
                        const std::string& index) {
    // check wether the type exist in the map
    if (m_allInfo.find(type) == m_allInfo.end()) {
        vector<string> tmp;
        tmp.push_back(info_name);
        m_allInfo.insert(std::make_pair(type, tmp));
    } else {
        m_allInfo[type].push_back(info_name);
    }
    // store the length and index
    m_indexInfo.insert(std::make_pair(info_name, index));
    // the default length is 4 for HepLorentzVector, 1 for others
    if (type == "HepLorentzVector") {
        m_lengthInfo.insert(std::make_pair(info_name, 4));
    } else {
        m_lengthInfo.insert(std::make_pair(info_name, 1));
    }
}

void AvailableInfo::Add(const string& info_name, const string& type,
                        const int& length) {
    // check wether the type exist in the map
    if (m_allInfo.find(type) == m_allInfo.end()) {
        vector<string> tmp;
        tmp.push_back(info_name);
        m_allInfo.insert(std::make_pair(type, tmp));
    } else {
        m_allInfo[type].push_back(info_name);
    }
    // store the length and index
    // the default index is "NULL"
    m_indexInfo.insert(std::make_pair(info_name, "NULL"));

    // the default length is 4 for HepLorentzVector, 1 for others
    if (type == "HepLorentzVector") {
        m_lengthInfo.insert(std::make_pair(info_name, 4));
    } else {
        m_lengthInfo.insert(std::make_pair(info_name, length));
    }
}

const vector<string> AvailableInfo::GetType(const std::string& type) {
    if (m_allInfo.find(type) != m_allInfo.end()) {
        return m_allInfo[type];
    } else {
        vector<string> tmp;
        return tmp;
    }
}

const int AvailableInfo::GetLength(const std::string& info_name) {
    return m_lengthInfo[info_name];
}
const string AvailableInfo::GetIndex(const std::string& info_name) {
    return m_indexInfo[info_name];
}
