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
#ifndef _SIGMApInfo_H
#define _SIGMApInfo_H
#include "HadronInfo/CombInfo.h"
#include "HadronInfo/ProtonInfo.h"
#include "HadronInfo/Pi0Info.h"
typedef CombInfo<ProtonInfo, Pi0Info, 3112, 0> SigmapInfo;

#endif  // _SIGMA0Info_H
