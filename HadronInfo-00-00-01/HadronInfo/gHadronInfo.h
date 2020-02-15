/* ====================================================
#   Copyright (C)2020 All rights reserved.
#
#   Author        : Xin-Xin MA
#   Email         : xxmawhu@163.com
#   File Name     : gHadronInfo.h
#   Create Time   : 2020-02-05 21:57
#   Last Modified : 2020-02-05 21:57
#   Describe      :
#
# ====================================================*/

#ifndef HadronInfo_gHadromInfo_H
#define HadronInfo_gHadromInfo_H
#include "HadronInfo/ShowerInfo.h"
#include "HadronInfo/ElectronInfo.h"
#include "HadronInfo/KaonInfo.h"
#include "HadronInfo/PionInfo.h"
#include "HadronInfo/ProtonInfo.h"
#include "HadronInfo/Pi0Info.h"
#include "HadronInfo/EtaInfo.h"
#include "HadronInfo/LambdaInfo.h"
#include "HadronInfo/KsInfo.h"
#include "HadronInfo/OmegamInfo.h"
// #include "HadronInfo/SigmamInfo.h"
#include "HadronInfo/Sigma0Info.h"
#include "HadronInfo/SigmapInfo.h"
#include "HadronInfo/XimInfo.h"
#include "HadronInfo/Xi0Info.h"

#include "HadronInfo/OmegaInfo.h"
#include "HadronInfo/PhiInfo.h"
#include "HadronInfo/EtaV3PiInfo.h"
// #include <cstdlib>
static PionInfo gPionInfo;
static KaonInfo gKaonInfo;
static ProtonInfo gProtonInfo;
static ElectronInfo gElectronInfo;
static ShowerInfo gShowerInfo;

static Pi0Info gPi0Info;
static EtaInfo gEtaInfo;

static KsInfo gKsInfo;
static LambdaInfo gLambdaInfo;

static OmegamInfo gOmegamInfo;
static Sigma0Info gSigma0Info;
static SigmapInfo gSigmapInfo;
static XimInfo gXimInfo;
static Xi0Info gXi0Info;

static OmegaInfo gOmegaInfo;
static PhiInfo gPhiInfo;
static EtaV3PiInfo gEtaV3PiInfo;
namespace Type {
enum PID {
    ElectronInfo = 11,
    ShowerInfo = 22,
    Pi0Info = 111,
    PionInfo = 211,
    EtaInfo = 221,
    OmegaInfo = 223,
    KsInfo = 310,
    KaonInfo = 321,
    PhiInfo = 333,
    ProtonInfo = 2212,
    LambdaInfo = 3122,
    SigmapInfo = 3112,
    Sigma0Info = 3212,
    XimInfo = 3312,
    Xi0Info = 3322,
    OmegamInfo = 3334,
    EtaV3PiInfo = 2212211,
};
}
#endif
