#ifndef LambdacSTAlg_DTagModeInfL_H
#define LambdacSTAlg_DTagModeInfL_H
#include <vector>
#include <iostream>
using std::cout;
using std::endl;
using std::vector;
class DTagModeInf {
   public:
    DTagModeInf();
    ~DTagModeInf();
    vector<int> ProtonId(const int &);
    int Charm(const int &);
    vector<int> LambdaId(const int &);
    vector<int> FinalID(const int &mode);
    vector<int> KsId(const int &);
    vector<int> PionId(const int &);
    vector<int> Pi0Id(const int &);
    vector<int> EtaId(const int &);
    vector<int> ChargedPid(const int &);
    vector<int> KaonId(const int &mode);
    int NShowers(const int &pid);
};
#endif
