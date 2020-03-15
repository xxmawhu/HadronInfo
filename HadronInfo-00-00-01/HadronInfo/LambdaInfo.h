#ifndef HadronInfo_LambdaInfo_H
#define HadronInfo_LambdaInfo_H
#include "HadronInfo/template/CombInfo.h"
#include "HadronInfo/ProtonInfo.h"
#include "HadronInfo/PionInfo.h"
typedef CombInfo<ProtonInfo, PionInfo, 3122, 1> LambdaInfo;
extern LambdaInfo gLambdaInfo;
#endif
