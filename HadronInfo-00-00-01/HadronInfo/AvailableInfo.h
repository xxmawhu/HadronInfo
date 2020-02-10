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
#include <algorithm>
using CLHEP::HepLorentzVector;
class AvailableInfo {
   public:
    AvailableInfo() { m_name = "NULL"; }
    ~AvailableInfo();
    void SetName(const std::string& name) { m_name = name; }
    const std::string GetName() const { return m_name; }
    const std::vector<std::string>& GetType(const std::string&) const;
    const int GetLength(const std::string&) const;
    const std::string GetIndex(const std::string&) const;
    const std::vector<std::string>& GetAllIndex() const { return m_allindex; }
    const std::map<std::string, std::string>& GetAllIndexInfo() const {
        return m_indexInfo;
    }
    const std::map<std::string, int>& GetAllLengthInfo() const {
        return m_lengthInfo;
    }
    //  virtual const double& GetDoubleInfo(const std::string&);
    //  virtual const HepLorentzVector& GetLorentzVector(const std::string&);
    // only five type are allowed in the code
    // void GetInfo(const std::string& info_name, int& targe){};
    virtual void GetInfoI(const std::string& info_name, int& targe) {};
    virtual void GetInfoD(const std::string& info_name, double& targe) {};
    virtual void GetInfoH(const std::string& info_name,
                          HepLorentzVector& targe) {};
    virtual void GetInfoVi(const std::string& info_name,
                           std::vector<int>& targe) {};
    virtual void GetInfoVd(const std::string& info_name,
                           std::vector<double>& targe) {};
    // if you want to store more than one, please insrease the length.
    // For example,
    // the length of one info, for HepLorentzVector, the length is 4
    // for mass the length is 1
    void Add(const std::string& info_name, const std::string& type,
             const int& length = 1);
    // it's designed to store variable info, such as the decay chain.
    // use the "index" to store the length
    // the index also should be stored first.
    void Add(const std::string& info_name, const std::string& type,
             const std::string& index);
    void Clear() {
        m_allInfo.clear();
        m_lengthInfo.clear();
        m_indexInfo.clear();
        m_allindex.clear();
    }

   private:
    // the name
    std::string m_name;
    std::vector<std::string> empty;
    std::vector<std::string> m_allindex;
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
