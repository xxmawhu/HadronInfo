/* ====================================================
#   Copyright (C)2019 All rights reserved.
#
#   Author        : Xin-Xin MA
#   Email         : xxmawhu@163.com
#   File Name     : util.h
#   Create Time   : 2019-12-12 14:15
#   Last Modified : 2019-12-12 14:15
#   Describe      :
#
# ====================================================*/
#ifndef HadronInfo_UTIL_H
#define HadronInfo_UTIL_H
#include <iostream>
#include <string>

namespace HadronTool {
std::string Name(const int& pid);
}

namespace PDG {
const double mPion = 139.57061E-3;
const double mPi0 = 134.9770E-3;
const double mEta = 547.862E-3;
const double mKaon = 493.677E-3;
const double mKs = 497.611E-3;
const double mElectron = 0.5109989461E-3;
const double mMuon = 105.6583745E-3;
const double mProton = 938.272013E-3;
const double mN = 939.5654133E-3;
const double mLambda = 1115.683E-3;
double mass(int pid);
}
namespace BOSS {
std::string name(int i);
}
#endif
