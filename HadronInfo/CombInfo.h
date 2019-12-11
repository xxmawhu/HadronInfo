/* ====================================================
#   Copyright (C)2019 All rights reserved.
#
#   Author        : Xin-Xin MA
#   Email         : xxmawhu@163.com
#   File Name     : CombInfo.h
#   Create Time   : 2019-12-11 10:37
#   Last Modified : 2019-12-11 10:37
#   Describe      :
# get the combinate information of two particles, three particles
# for example, (pi0, pi0), (pi+, pi-, eta)
# ====================================================*/
#ifndef  HadronInfo_COMBINFO_H
#define  HadronInfo_COMBINFO_H
#include "TupleSvc/DecayTree.h"
class CombInfo: public AvailableInfo {
    public:
        CombInfo();
    private:
        DecayTree m_decayTree;
};

#endif // _COMBINFO_H


