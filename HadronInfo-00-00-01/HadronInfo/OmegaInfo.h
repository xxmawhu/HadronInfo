/* ====================================================
#   Copyright (C)2019 All rights reserved.
#
#   Author        : Xin-Xin MA
#   Email         : xxmawhu@163.com
#   File Name     : OmegaInfo.h
#   Create Time   : 2019-12-12 15:31
#   Last Modified : 2020-02-06 18:30
#   Describe      :
#
# ====================================================*/
#ifndef HadronInfo_OmegaInfo_H
#define HadronInfo_OmegaInfo_H
#include "HadronInfo/CombThreeInfo.h"
#include "HadronInfo/Pi0Info.h"
#include "HadronInfo/PionInfo.h"
typedef CombThreeInfo<PionInfo, PionInfo, Pi0Info, 223, 1> OmegaInfo;

#endif
