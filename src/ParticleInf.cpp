#include "HadronInfoDev/ParticleInf.h"
#include <iostream>
#include <string>
#include <algorithm>
using std::find;
using std::string;

string ParticleInf::Name(int pid) {
    if (pid == 11) return string("Elem");
    if (pid == -11) return string("Elep");
    if (pid == 13) return string("Muonm");
    if (pid == -13) return string("Muonp");
    if (pid == 22) return string("Gamma");
    if (pid == 211) return string("Pionp");
    if (pid == -211) return string("Pionm");
    if (pid == 111) return string("Pi0");
    if (pid == 321) return string("Kaonp");
    if (pid == -321) return string("Kaonm");
    if (pid == 310) return string("Ks");
    if (pid == 331) return string("Ep");
    if (pid == 223) return string("Omega");
    if (pid == 221) return string("Eta");
    if (pid == 2212211) return string("EtaV3P");
    if (pid == 2212) return string("Protonp");
    if (pid == -2212) return string("Protonm");
    if (pid == 3122) return string("Lambda");
    if (pid == -3122) return string("Lambdabar");
    if (pid == 333) return string("Phi");
    if (pid == 3212) return string("Sigma0");
    if (pid == -3212) return string("Sigmabar0");
    if (pid == 411) return string("D+");
    if (pid == -411) return string("D-");
    if (pid == 421) return string("D0");
    if (pid == -421) return string("D0bar");
    if (pid == 3322) return string("Xi0");
    if (pid == -3322) return string("Xi0bar");
    return string("NULL");
}
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

void ParticleInf::SetChildren(vector<int> pids) { m_pids = pids; }
bool ParticleInf::Find(int pid) {
    if (find(m_pids.begin(), m_pids.end(), pid) != m_pids.end()) {
        return true;
    } else {
        return false;
    }
}
bool ParticleInf::NeedPion() {
    return Find(211) || Find(-211) || Find(331) || Find(223) || Find(2212211) ||
           Find(3212) || Find(-3212) || Find(3122) || Find(-3122) ||
           Find(3322) || Find(-3322);
}
bool ParticleInf::NeedKaon() { return Find(321) || Find(-321) || Find(333); }
bool ParticleInf::NeedPi0() {
    return Find(2212211) || Find(111) || Find(223) || Find(3322) || Find(-3322);
}
bool ParticleInf::NeedProton() {
    return Find(2212) || Find(-2212) || Find(3212) || Find(-3212) ||
           Find(3122) || Find(-3122) || Find(3322) || Find(-3322);
}
bool ParticleInf::NeedEta() { return Find(221) || Find(331); }
bool ParticleInf::NeedKs() { return Find(310); }
bool ParticleInf::NeedElectron() { return Find(11) || Find(-11); }
bool ParticleInf::NeedMuon() { return Find(13) || Find(-13); }
bool ParticleInf::NeedPhoton() {
    return Find(22) || Find(331222) || Find(3212) || Find(-3212);
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
