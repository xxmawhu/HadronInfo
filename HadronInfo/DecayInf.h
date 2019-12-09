#ifndef LambdacSTAlg_DecayInfL_H
#define LambdacSTAlg_DecayInfL_H
#include <vector>
#include <iostream>
using std::cout;
using std::endl;
using std::vector;
class DecayInf {
   public:
    DecayInf();
    ~DecayInf();
    vector<int> getChildren(int);
};
#endif
