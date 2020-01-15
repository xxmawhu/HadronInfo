/* ====================================================
#   Copyright (C)2019 All rights reserved.
#
#   Author        : Xin-Xin MA
#   Email         : xxmawhu@163.com
#   File Name     : OmegamInfoDev.h
#   Create Time   : 2019-12-12 15:31
#   Last Modified : 2019-12-12 15:38
#   Describe      :
#
# ====================================================*/
#ifndef HadronInfoDev_OmegamINFODev_H
#define HadronInfoDev_OmegamINFODev_H
#include "HadronInfoDev/CombInfoDev.h"
#include "HadronInfoDev/LamInfoDev.h"
#include "HadronInfoDev/KaonInfoDev.h"
bool doVertexFit = true;
typedef CombInfoDev<LamInfoDev, KaonInfoDev, 3334, doVertexFit> OmegamInfoDev;

#endif  // _SIGMA0INFODev_H
