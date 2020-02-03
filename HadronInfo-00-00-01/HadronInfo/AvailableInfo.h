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
#include <map>
using CLHEP::HepLorentzVector;
class AvailableInfo {
   public:
    AvailableInfo() {};
    ~AvailableInfo();
    virtual const std::string GetName() {
        return "AvailableInfo";
    };
    const std::vector<std::string> GetType(const std::string&);
    const int GetLength(const std::string&);
    const std::string GetIndex(const std::string&);
    virtual const double& GetDoubleInfo(const std::string&);
    virtual const HepLorentzVector& GetLorentzVector(const std::string&);
    template <class T>
    void GetInfo(const std::string&, T& targe){};
    // if you want to store more than one, please insrease the length.
    // For example, 
    // the length of one info, for HepLorentzVector, the length is 4
    // for mass the length is 1
    void add(const std::string& info_name, const std::string& type,
             const int& length = 1);
    // it's designed to store variable info, such as the decay chain.
    // use the "index" to store the length
    // the index also should be stored first.
    void add(const std::string& info_name, const std::string& type,
             const std::string& index);

   private:
    // key: type of info, must in [int, double, HepLorentzVector]
    // HepLorentzVector is sepcially because it's used freauently 
    // value: name, i.e PionP4 
    std::map<std::string, std::vector<std::string> > m_allInfo;
    // the length of one info, for HepLorentzVector, the length is 4
    // for mass the length is 1
    std::map<std::string, int> m_lengthInfo;
    // it's designed to store variable info, such as the decay chain.
    // use the "index" to store the length
    // the index also should be stored first.
    std::map<std::string, std::string> m_indexInfo;
};

#endif  // _AVAILABLEInfo_H
