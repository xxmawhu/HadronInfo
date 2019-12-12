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
#ifndef HadronInfo_OmegamInfo_H
#define HadronInfo_OmegamInfo_H
#include "HadronInfo/CombInfo.h"
#include "HadronInfo/LamInfo.h"
#include "HadronInfo/KaonInfo.h"

typedef CombInfo<LamInfo, KaonInfo, 3334, 1> OmegamInfo;
#endif  // _SIGMA0Info_H
