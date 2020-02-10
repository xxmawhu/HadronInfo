#ifndef HadronInfo_OmegaInfo_H
#define HadronInfo_OmegaInfo_H
#include "HadronInfo/template/CombThreeInfo.h"
#include "HadronInfo/Pi0Info.h"
#include "HadronInfo/PionInfo.h"
typedef CombThreeInfo<PionInfo, PionInfo, Pi0Info, 223, 1> OmegaInfo;
#endif
