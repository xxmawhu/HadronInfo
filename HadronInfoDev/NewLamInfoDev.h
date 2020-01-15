/* ====================================================
#   Copyright (C)2019 All rights reserved.
#
#   Author        : Xin-Xin MA
#   Email         : xxmawhu@163.com
#   File Name     : NewLamInfoDev.h
#   Create Time   : 2019-12-12 15:31
#   Last Modified : 2020-01-15 22:29
#   Describe      :
#
# ====================================================*/
#ifndef HadronInfoDev_NewLamInfoDev_H
#define HadronInfoDev_NewLamInfoDev_H
#include "HadronInfoDev/CombInfoDev.h"
#include "HadronInfoDev/ProtonInfoDev.h"
#include "HadronInfoDev/PionInfoDev.h"
bool doVertexFit = true;
typedef CombInfoDev<ProtonInfoDev, PionInfoDev, 3122, doVertexFit> NewLamInfoDev;

#endif
