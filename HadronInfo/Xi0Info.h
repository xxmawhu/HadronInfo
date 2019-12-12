/* ====================================================
#   Copyright (C)2019 All rights reserved.
#
#   Author        : Xin-Xin MA
#   Email         : xxmawhu@163.com
#   File Name     : Xi0Info.h
#   Create Time   : 2019-12-12 15:31
#   Last Modified : 2019-12-12 15:34
#   Describe      :
#
# ====================================================*/
#ifndef _Xi0INFO_H
#define _Xi0INFO_H
#include "HadronInfo/CombInfo.h"
#include "HadronInfo/LamInfo.h"
#include "HadronInfo/Pi0Info.h"
bool doVertexFit = false;
typedef CombInfo<LamInfo, Pi0Info, 3322, doVertexFit> Sigma0Info;

#endif  // _SIGMA0INFO_H
