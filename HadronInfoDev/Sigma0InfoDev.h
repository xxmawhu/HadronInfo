/* ====================================================
#   Copyright (C)2019 All rights reserved.
#
#   Author        : Xin-Xin MA
#   Email         : xxmawhu@163.com
#   File Name     : Sigma0InfoDev.h
#   Create Time   : 2019-12-12 15:31
#   Last Modified : 2019-12-12 15:31
#   Describe      :
#
# ====================================================*/
#ifndef _SIGMA0INFODev_H
#define _SIGMA0INFODev_H
#include "HadronInfoDev/CombInfoDev.h"
#include "HadronInfoDev/LamInfoDev.h"
#include "HadronInfoDev/ShowerInfoDev.h"
bool doVertexFit = false;
typedef CombInfoDev<LamInfoDev, ShowerInfoDev, 3212, doVertexFit> Sigma0InfoDev;

#endif  // _SIGMA0INFODev_H
