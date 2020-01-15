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
#ifndef _UTIL_H
#define _UTIL_H
namespace HadronTool {
const string& Name(const int& pid) {
    if (pid == 11) return string("Elem");
    if (pid == -11) return string("Elep");
    if (pid == 13) return string("Muonm");
    if (pid == -13) return string("Muonp");
    if (pid == 22) return string("Gamma");
    if (pid == 211) return string("Pionp");
    if (pid == -211) return string("Pionm");
    if (pid == 111) return string("Pi0");
    if (pid == 321) return string("Kaonp");
    if (pid == -321) return string("Kaonm");
    if (pid == 310) return string("Ks");
    if (pid == 331) return string("Ep");
    if (pid == 223) return string("Omega");
    if (pid == 221) return string("Eta");
    if (pid == 2212211) return string("EtaV3P");
    if (pid == 2212) return string("Protonp");
    if (pid == -2212) return string("Protonm");
    if (pid == 3122) return string("Lambda");
    if (pid == -3122) return string("Lambdabar");
    if (pid == 333) return string("Phi");
    if (pid == 3212) return string("Sigma0");
    if (pid == -3212) return string("Sigmabar0");
    if (pid == 411) return string("D+");
    if (pid == -411) return string("D-");
    if (pid == 421) return string("D0");
    if (pid == -421) return string("D0bar");
    if (pid == 3312) return string("Xim");
    if (pid == -3312) return string("Xibarp");
    if (pid == 3322) return string("Xi0");
    if (pid == -3322) return string("Xi0bar");
    if (pid == 3334) return string("Omegam");
    if (pid == -3334) return string("OmegaBarp");
    return string("NULL");
}
}

#endif  // _UTIL_H
