#ifndef HadronInfo_LamInfo_H
#define HadronInfo_LamInfo_H
#include "HadronInfo/template/CombInfo.h"
#include "HadronInfo/ProtonInfo.h"
#include "HadronInfo/PionInfo.h"
typedef CombInfo<ProtonInfo, PionInfo, 3122, 1> LamInfo;
#endif
