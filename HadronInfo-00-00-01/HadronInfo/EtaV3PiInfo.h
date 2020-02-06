/* ====================================================
#   Copyright (C)2019 All rights reserved.
#
#   Author        : Xin-Xin MA
#   Email         : xxmawhu@163.com
#   File Name     : EtaV3piInfo.h
#   Create Time   : 2019-12-12 15:31
#   Last Modified : 2020-02-06 18:30
#   Describe      :
#
# ====================================================*/
#ifndef HadronInfo_EtaV3piInfo_H
#define HadronInfo_EtaV3piInfo_H
#include "HadronInfo/CombThreeInfo.h"
#include "HadronInfo/Pi0Info.h"
#include "HadronInfo/PionInfo.h"
typedef CombThreeInfo<PionInfo, PionInfo, Pi0Info, 2212211, 0> EtaV3PiInfo;

#endif
