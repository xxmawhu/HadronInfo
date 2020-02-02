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
    virtual const double& GetDoubleInfo(const std::string&);
    const std::vector<std::string>& GetType(const std::string&);
    virtual const HepLorentzVector& GetLorentzVector(const std::string&);
    const std::vector<std::string>& GetDoubleInf();
    const std::vector<std::string>& GetIntInf();
    const std::vector<std::string>& GetP4Inf();
    const std::vector<std::string>& GetVectorInf();
    void add(const std::string& info_name, const std::string& type = "double");

   private:
    std::map<std::string, std::vector<std::string> > m_allInfo;
};

#endif  // _AVAILABLEInfo_H
