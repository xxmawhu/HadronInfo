#ifndef HadronInfo_KsInfo_H
#define HadronInfo_KsInfo_H
#include "HadronInfo/template/CombInfo.h"
#include "HadronInfo/ProtonInfo.h"
#include "HadronInfo/PionInfo.h"
typedef CombInfo<PionInfo, PionInfo, 310, 1> KsInfo;
extern KsInfo gKsInfo;
#endif
