#ifndef LambdacSTAlg_LambdacModeInfL_H
#define LambdacSTAlg_LambdacModeInfL_H
#include <vector>
#include <iostream>
using std::cout;
using std::endl;
using std::vector;
class LambdacModeInf {
   public:
    LambdacModeInf();
    ~LambdacModeInf();
    vector<int> getProtonId(int, int);
    vector<int> getLambdaId(int, int);
    vector<int> getKsId(int, int);
    vector<int> getPionId(int, int);
    vector<int> getFinalPid(int, int);
};
#endif
