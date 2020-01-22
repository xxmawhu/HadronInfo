/* ====================================================
#   Copyright (C)2019 All rights reserved.
#
#   Author        : Xin-Xin MA
#   Email         : xxmawhu@163.com
#   File Name     : LambdaInfo.h
#   Create Time   : 2019-12-12 15:31
#   Last Modified : 2020-01-15 22:29
#   Describe      :
#
# ====================================================*/
#ifndef HadronInfo_LambdaInfo_H
#define HadronInfo_LambdaInfo_H
#include "HadronInfo/CombInfo.h"
#include "HadronInfo/ProtonInfo.h"
#include "HadronInfo/PionInfo.h"
typedef CombInfo<ProtonInfo, PionInfo, 3122, 1> LambdaInfo;

#endif
