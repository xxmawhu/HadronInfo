/* ====================================================
#   Copyright (C)2019 All rights reserved.
#
#   Author        : Xin-Xin MA
#   Email         : xxmawhu@163.com
#   File Name     : Xi0InfoDev.h
#   Create Time   : 2019-12-12 15:31
#   Last Modified : 2019-12-12 15:34
#   Describe      :
#
# ====================================================*/
#ifndef _Xi0INFODev_H
#define _Xi0INFODev_H
#include "HadronInfoDev/CombInfoDev.h"
#include "HadronInfoDev/LamInfoDev.h"
#include "HadronInfoDev/Pi0InfoDev.h"
typedef CombInfoDev<LamInfoDev, Pi0InfoDev, 3322, 0> Sigma0InfoDev;

#endif  // _SIGMA0INFODev_H
