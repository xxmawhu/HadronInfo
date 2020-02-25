#include "HadronInfo/ParticleInf.h"
#include "HadronInfo/util.h"
#include <iostream>
#include <string>
#include <algorithm>
using std::find;
using std::string;

string ParticleInf::Name(int pid) { return HadronTool::Name(pid); }
vector<int> ParticleInf::ChargedChildren(int pid) {
    int PID = pid > 0 ? pid : -pid;
    vector<int> m_pids;
    if (PID == 11 || PID == 13 || PID == 321 || PID == 211 || PID == 2212) {
        m_pids.push_back(PID);
        return m_pids;
    }

    if (PID == 3122 || PID == 3212) {
        m_pids.push_back(2212);
        m_pids.push_back(211);
        return m_pids;
    }

    if (PID == 310 || PID == 331 || PID == 223 || PID == 2212211) {
        m_pids.push_back(211);
        m_pids.push_back(211);
        return m_pids;
    }
    if (PID == 333) {
        m_pids.push_back(321);
        m_pids.push_back(321);
        return m_pids;
    }
}

void ParticleInf::GetDaughterList(const int& pid, vector<int> & pidList) {
    // e+ e- pi K mu, p
    if (pid == 11 || pid == 13 || pid == 321 || pid == 211 || pid == 2212
        ||pid == -11 || pid == -13 || pid == -321 || pid == -211 
        || pid == -2212 || pid == 22 || pid == 111 || pid == 221
            ) {
        pidList.push_back(pid);
        return;
    }
    switch (pid) {
        // Ks
        case 310: 
            pidList.push_back(211);
            pidList.push_back(-211);
            return;
            // Lambda
        case 3122:
            pidList.push_back(2212);
            pidList.push_back(-211);
            return;
            // anti-Lambda
        case -3122:
            pidList.push_back(-2212);
            pidList.push_back(211);
            return;
            // pi0 111 -> 22 22
        case 111:
            pidList.push_back(22);
        pidList.push_back(22);
        return;
        // eta 221 -> 22 22
        case 221:
        pidList.push_back(22);
        pidList.push_back(22);
        return;
        // omega 223 -> 211 -211 111
        case 223:
        pidList.push_back(211);
        pidList.push_back(-211);
        pidList.push_back(111);
        return;
        // EtaV3P 2212211 -> 211, -211, 111
        case 2212211:
        pidList.push_back(-2212);
        pidList.push_back(211);
        pidList.push_back(111);
        return;
        // phi 333 -> 321, -321
        case 333:
        pidList.push_back(321);
        pidList.push_back(-321);
        return;
        // Sigmap -> p pi0
        case 3112:
        pidList.push_back(2212);
        pidList.push_back(111);
        return;
        case -3112:
        pidList.push_back(-2212);
        pidList.push_back(111);
        return;
        // Sigma0-> Lambda gamma 3122, 22
        case 3212:
        pidList.push_back(3122);
        pidList.push_back(22);
        return;
        case -3212:
        pidList.push_back(-3122);
        pidList.push_back(22);
        return;
        // Xi0 -> Lambda pi0
        case 3322:
        pidList.push_back(3122);
        pidList.push_back(111);
        return;
        case -3322:
        pidList.push_back(-3122);
        pidList.push_back(111);
        return;
        // Xi- -> Lambda pi-
        case 3312:
        pidList.push_back(3122);
        pidList.push_back(-211);
        return;
        case -3312:
        pidList.push_back(-3122);
        pidList.push_back(211);
        return;
        // Omega- -> Lambda K
        case 3334:
        pidList.push_back(3122);
        pidList.push_back(321);
        return;
        case -3334:
        pidList.push_back(-3122);
        pidList.push_back(-321);
        return;
        default:
        pidList.push_back(pid);
         return; 
    }
    vector<int> tmpList;
    GetDaughterList(pid, tmpList);
    if (tmpList.empty()) return;
    for(vector<int>::iterator itr = tmpList.begin(); itr != tmpList.end();
            ++ itr) {
        GetDaughterList(*itr, pidList);
    }
}

int ParticleInf::Need(const int& pid) const{
    return std::count(m_daughterList.begin(), m_daughterList.end(), pid);
}

double ParticleInf::Mass(int pid) {
    int PID = pid > 0 ? pid : -pid;
    if (PID == 11) return 0.000510998928;
    if (PID == 13) return 0.1056583715;
    if (PID == 22) return 0.0;
    if (PID == 211) return 0.13957018;
    if (PID == 111) return 0.1349766;
    if (PID == 221) return 0.547862;
    if (PID == 2212211) return 0.547862;
    if (PID == 321) return 0.493677;
    if (PID == 310) return 0.497614;
    if (PID == 411) return 1.86959;
    if (PID == 421) return 1.86483;
    return -1.0;
}

void ParticleInf::SetChildren(const vector<int>& pids) { 
    m_pids = pids;
    for(vector<int>::iterator itr = m_pids.begin();
            itr != m_pids.end();
            ++ itr) {
        GetDaughterList(*itr, m_daughterList);
    }
}
int ParticleInf::NeedPion() const{
    return Need(211) + Need(-211);
}
int ParticleInf::NeedKaon() const{ 
    return Need(321) + Need(-321);
}
int ParticleInf::NeedPi0() const{
    return Need(111);
}
int ParticleInf::NeedProton() const{
    return Need(2212) + Need(-2212) ;
}
int ParticleInf::NeedEta() const{ return Need(221) + Need(331); }
int ParticleInf::NeedKs() const{ 
    return Need(310); }
int ParticleInf::NeedElectron() const { 
    return Need(11) + Need(-11); }
int ParticleInf::NeedMuon() const { return Need(13) + Need(-13); }
int ParticleInf::NeedPhoton() const{
    return Need(22);
}

vector<int> ParticleInf::GammaCov() {
    vector<int> tmp;
    for (int i = 0; i < m_pids.size(); i++) {
        if (abs(m_pids[i]) == 11) {
            tmp.push_back(i);
        }
    }
    if (tmp.empty()) return tmp;
    vector<int> idpairs;
    for (int i = 0; i < tmp.size(); i++) {
        for (int j = 0; j < tmp.size(); j++) {
            if (m_pids[tmp[i]] < 0 || m_pids[tmp[j]] > 0) continue;
            idpairs.push_back(tmp[i]);
            idpairs.push_back(tmp[j]);
        }
    }
    return idpairs;
}
