/* ====================================================
#   Copyright (C)2019 All rights reserved.
#
#   Author        : Xin-Xin MA
#   Email         : xxmawhu@163.com
#   File Name     : XimInfo.h
#   Create Time   : 2019-12-12 15:31
#   Last Modified : 2019-12-12 15:35
#   Describe      :
#
# ====================================================*/
#ifndef HadronInfo_XimINFO_H
#define HadronInfo_XimINFO_H
#include "HadronInfo/CombInfo.h"
#include "HadronInfo/LamInfo.h"
#include "HadronInfo/PionInfo.h"
bool doVertexFit = true;
typedef CombInfo<LamInfo, PionInfo, 3312, doVertexFit> XimInfo;

#endif  // _SIGMA0INFO_H
