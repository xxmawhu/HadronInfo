/* ====================================================
#   Copyright (C)2019 All rights reserved.
#
#   Author        : Xin-Xin MA
#   Email         : xxmawhu@163.com
#   File Name     : KsInfo.h
#   Create Time   : 2019-12-12 15:31
#   Last Modified : 2020-01-15 22:29
#   Describe      :
#
# ====================================================*/
#ifndef HadronInfo_KsInfo_H
#define HadronInfo_KsInfo_H
#include "HadronInfo/CombInfo.h"
#include "HadronInfo/PionInfo.h"
typedef CombInfo<PionInfo, PionInfo, 310, 1> KsInfo;
#endif
