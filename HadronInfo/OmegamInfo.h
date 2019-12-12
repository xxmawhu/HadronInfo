/* ====================================================
#   Copyright (C)2019 All rights reserved.
#
#   Author        : Xin-Xin MA
#   Email         : xxmawhu@163.com
#   File Name     : OmegamInfo.h
#   Create Time   : 2019-12-12 15:31
#   Last Modified : 2019-12-12 15:38
#   Describe      :
#
# ====================================================*/
#ifndef HadronInfo_OmegamINFO_H
#define HadronInfo_OmegamINFO_H
#include "HadronInfo/CombInfo.h"
#include "HadronInfo/LamInfo.h"
#include "HadronInfo/KaonInfo.h"
bool doVertexFit = true;
typedef CombInfo<LamInfo, KaonInfo, 3334, doVertexFit> OmegamInfo;

#endif  // _SIGMA0INFO_H
