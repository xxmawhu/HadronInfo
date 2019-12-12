#ifndef Hadron_ParticleInf_h
#define Hadron_ParticleInf_h
#include <iostream>
//#include <map>
#include <vector>
#include <string>
using std::vector;
using std::string;
class ParticleInf {
   public:
    string Name(int);
    double Mass(int);
    void SetChildren(vector<int>);
    vector<int> ChargedChildren(int);
    vector<int> GammaCov();
    bool NeedPion();
    bool NeedKaon();
    bool NeedKs();
    bool NeedPi0();
    bool NeedEta();
    bool NeedProton();
    bool NeedPhoton();
    bool NeedElectron();
    bool NeedMuon();
    bool Find(int);

   private:
    vector<int> m_pids;
};

#endif
