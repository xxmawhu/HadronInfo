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
    void SetChildren(const vector<int>&);
    vector<int> ChargedChildren(int);
    vector<int> GammaCov();
    int NeedPion() const;
    int NeedKaon() const;
    int NeedKs() const;
    int NeedPi0() const;
    int NeedEta() const;
    int NeedProton() const;
    int NeedPhoton() const;
    int NeedElectron() const;
    int NeedMuon() const;
    int Need(const int&) const;
    void GetDaughterList(const int&, vector<int>&);

   private:
    vector<int> m_pids;
    vector<int> m_daughterList;
};

#endif
