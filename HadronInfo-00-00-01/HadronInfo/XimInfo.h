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
#ifndef HadronInfo_XimInfo_H
#define HadronInfo_XimInfo_H
#include "HadronInfo/CombInfo.h"
#include "HadronInfo/LamInfo.h"
#include "HadronInfo/PionInfo.h"
typedef CombInfo<LamInfo, PionInfo, 3312, 1> XimInfo;

#endif  // _SIGMA0Info_H
