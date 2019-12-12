/* ====================================================
#   Copyright (C)2019 All rights reserved.
#
#   Author        : Xin-Xin MA
#   Email         : xxmawhu@163.com
#   File Name     : Sigma0Info.h
#   Create Time   : 2019-12-12 15:31
#   Last Modified : 2019-12-12 15:31
#   Describe      :
#
# ====================================================*/
#ifndef _SIGMA0INFO_H
#define _SIGMA0INFO_H
#include "HadronInfo/CombInfo.h"
#include "HadronInfo/LamInfo.h"
#include "HadronInfo/ShowerInfo.h"
bool doVertexFit = false;
typedef CombInfo<LamInfo, ShowerInfo, 3212, doVertexFit> Sigma0Info;

#endif  // _SIGMA0INFO_H
