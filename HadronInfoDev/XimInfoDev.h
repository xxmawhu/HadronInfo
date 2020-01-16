/* ====================================================
#   Copyright (C)2019 All rights reserved.
#
#   Author        : Xin-Xin MA
#   Email         : xxmawhu@163.com
#   File Name     : XimInfoDev.h
#   Create Time   : 2019-12-12 15:31
#   Last Modified : 2019-12-12 15:35
#   Describe      :
#
# ====================================================*/
#ifndef HadronInfoDev_XimINFODev_H
#define HadronInfoDev_XimINFODev_H
#include "HadronInfoDev/CombInfoDev.h"
#include "HadronInfoDev/LamInfoDev.h"
#include "HadronInfoDev/PionInfoDev.h"
typedef CombInfoDev<LamInfoDev, PionInfoDev, 3312, 1> XimInfoDev;

#endif  // _SIGMA0INFODev_H
