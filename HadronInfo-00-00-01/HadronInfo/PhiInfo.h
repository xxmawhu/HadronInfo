#ifndef HadronInfo_PhiInfo_H
#define HadronInfo_PhiInfo_H
#include "HadronInfo/template/CombInfo.h"
#include "HadronInfo/KaonInfo.h"
typedef CombInfo<KaonInfo, KaonInfo, 333, 1> PhiInfo;
extern PhiInfo gPhiInfo;
#endif
