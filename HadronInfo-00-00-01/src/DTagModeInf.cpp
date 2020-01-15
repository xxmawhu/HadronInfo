#include "HadronInfo/DTagModeInf.h"
#include <stdio.h>
#include <stdlib.h>

int DTagModeInf::Charm(const int &mode) {
    if (mode >= 100 && mode <= 125) {
        return 0;
    } else {
        return 1;
    }
}
vector<int> DTagModeInf::ChargedPid(const int &mode) {
    vector<int> m_pid;
    vector<int> kaons = KaonId(mode);
    vector<int> pions = PionId(mode);
    vector<int> protons = ProtonId(mode);
    for (int i = 0; i < kaons.size(); i++) {
        m_pid.push_back(321);
    }
    for (int i = 0; i < pions.size(); i++) {
        m_pid.push_back(321);
    }
    for (int i = 0; i < pions.size(); i++) {
        int indx = pions[i];
        m_pid[indx] = 211;
    }
    for (int i = 0; i < protons.size(); i++) {
        m_pid.push_back(321);
    }
    for (int i = 0; i < protons.size(); i++) {
        int indx = protons[i];
        m_pid[indx] = 2212;
    }
    return m_pid;
}

vector<int> DTagModeInf::ProtonId(const int &mode) {
    vector<int> m_pid;
    return m_pid;
}

vector<int> DTagModeInf::KsId(const int &mode) {
    vector<int> m_pid;
    if (mode == 0 || mode == 2 || mode == 3) {
        m_pid.push_back(1);
        m_pid.push_back(2);
        return m_pid;
    }
    if (mode == 202 || mode == 203 || mode == 204 || mode == 208 ||
        mode == 212 || mode == 216 || mode == 217 || mode == 222 ||
        mode == 400 || mode == 402 || mode == 405 || mode == 406) {
        m_pid.push_back(0);
        m_pid.push_back(1);
        return m_pid;
    }
    if (mode == 108 || mode == 119 || mode == 211 || mode == 213 ||
        mode == 403) {
        m_pid.push_back(0);
        m_pid.push_back(1);
        m_pid.push_back(2);
        m_pid.push_back(3);
        return m_pid;
    }
    if (mode == 114) {
        m_pid.push_back(0);
        m_pid.push_back(1);
        m_pid.push_back(2);
        m_pid.push_back(3);
        m_pid.push_back(4);
        m_pid.push_back(5);
        return m_pid;
    }
    if (mode == 400 || mode == 402 || mode == 405 || mode == 406) {
        m_pid.push_back(0);
        m_pid.push_back(1);
        return m_pid;
    }
    if (mode == 403) {
        m_pid.push_back(0);
        m_pid.push_back(1);
        m_pid.push_back(2);
        m_pid.push_back(3);
        return m_pid;
    }
    return m_pid;
}
vector<int> DTagModeInf::Pi0Id(const int &mode) {
    vector<int> m_pid;
    int index = 0;
    vector<int> finid = FinalID(mode);
    for (vector<int>::iterator itr = finid.begin(); itr != finid.end(); ++itr) {
        if ((*itr) == 111) {
            m_pid.push_back(index++);
            m_pid.push_back(index++);
        } else {
            for (int i = 0; i < NShowers(*itr); ++i) index++;
        }
    }
    return m_pid;
    if (mode == 122 || mode == 218 || mode == 206) {
        m_pid.push_back(0);
        m_pid.push_back(1);
        return m_pid;
    }
    if (mode == 402 || mode == 404 || mode == 420 || mode == 422 ||
        mode == 424 || mode == 450) {
        m_pid.push_back(0);
        m_pid.push_back(1);
        return m_pid;
    }
    return m_pid;
}
vector<int> DTagModeInf::EtaId(const int &mode) {
    vector<int> m_pid;
    int index = 0;
    vector<int> finid = FinalID(mode);
    for (vector<int>::iterator itr = finid.begin(); itr != finid.end(); ++itr) {
        if ((*itr) == 221) {
            m_pid.push_back(index++);
            m_pid.push_back(index++);
        } else {
            for (int i = 0; i < NShowers(*itr); ++i) index++;
        }
    }
    return m_pid;
}

vector<int> DTagModeInf::PionId(const int &mode) {
    vector<int> m_pid;
    if (mode == 0 || mode == 1 || mode == 2) {
        m_pid.push_back(1);
        return m_pid;
    }
    if (mode == 122) {
        m_pid.push_back(2);
        m_pid.push_back(3);
        return m_pid;
    }
    if (mode == 200 || mode == 201) {
        m_pid.push_back(1);
        m_pid.push_back(2);
        return m_pid;
    }
    if (mode == 202 || mode == 203) {
        m_pid.push_back(0);
        m_pid.push_back(1);
        m_pid.push_back(2);
        return m_pid;
    }
    if (mode == 204 || mode == 211) {
        m_pid.push_back(0);
        m_pid.push_back(1);
        m_pid.push_back(2);
        m_pid.push_back(3);
        m_pid.push_back(4);
        return m_pid;
    }
    if (mode == 205) {
        m_pid.push_back(2);
        return m_pid;
    }
    if (mode == 206 || mode == 210 || mode == 215) {
        m_pid.push_back(0);
        return m_pid;
    }
    if (mode == 208 || mode == 212) {
        m_pid.push_back(0);
        m_pid.push_back(1);
        return m_pid;
    }
    if (mode == 209 || mode == 214) {
        m_pid.push_back(0);
        m_pid.push_back(1);
        m_pid.push_back(2);
        return m_pid;
    }
    if (mode == 213) {
        m_pid.push_back(0);
        m_pid.push_back(1);
        m_pid.push_back(2);
        m_pid.push_back(3);
        return m_pid;
    }
    if (mode == 218) {
        m_pid.push_back(2);
        return m_pid;
    }
    if (mode == 400 || mode == 402) {
        m_pid.push_back(0);
        m_pid.push_back(1);
        return m_pid;
    }
    if (mode == 401 || mode == 404) {
        m_pid.push_back(2);
        return m_pid;
    }
    if (mode == 403) {
        m_pid.push_back(0);
        m_pid.push_back(1);
        m_pid.push_back(2);
        m_pid.push_back(3);
        m_pid.push_back(4);
        return m_pid;
    }
    if (mode == 405 || mode == 406) {
        m_pid.push_back(0);
        m_pid.push_back(1);
        m_pid.push_back(3);
        m_pid.push_back(4);
        return m_pid;
    }
    if (mode == 480) {
        m_pid.push_back(0);
        m_pid.push_back(1);
        m_pid.push_back(2);
        return m_pid;
    } else {
        int index = 0;
        vector<int> finid = FinalID(mode);
        for (vector<int>::iterator itr = finid.begin(); itr != finid.end();
             ++itr) {
            if (abs(*itr) == 211) {
                m_pid.push_back(index++);
            } else if (abs(*itr) == 321) {
                index++;
            }
        }
        return m_pid;
    }
    return m_pid;
}

vector<int> DTagModeInf::KaonId(const int &mode) {
    vector<int> m_pid;
    if (mode == 0 || mode == 1 || mode == 2 || mode == 3 || mode == 5) {
        m_pid.push_back(0);
        return m_pid;
    }
    if (mode == 122) {
        m_pid.push_back(0);
        m_pid.push_back(1);
        return m_pid;
    }
    if (mode == 122) {
        m_pid.push_back(0);
        m_pid.push_back(1);
        return m_pid;
    }

    if (mode == 122) {
        m_pid.push_back(0);
        m_pid.push_back(1);
        return m_pid;
    }
    if (mode == 200 || mode == 201 || mode == 207 || mode == 220) {
        m_pid.push_back(0);
        return m_pid;
    }
    if (mode == 205 || mode == 218) {
        m_pid.push_back(0);
        m_pid.push_back(1);
        return m_pid;
    }
    if (mode == 208 || mode == 212 || mode == 216 || mode == 217) {
        m_pid.push_back(2);
        return m_pid;
    }
    if (mode == 213) {
        m_pid.push_back(4);
        return m_pid;
    }
    if (mode == 218) {
        m_pid.push_back(0);
        m_pid.push_back(1);
        return m_pid;
    }
    if (mode == 300) {
        m_pid.push_back(0);
        m_pid.push_back(1);
        m_pid.push_back(2);
        return m_pid;
    }
    if (mode == 400 || mode == 402 || mode == 405 || mode == 406) {
        m_pid.push_back(2);
        return m_pid;
    }
    if (mode == 401 || mode == 404) {
        m_pid.push_back(0);
        m_pid.push_back(1);
        return m_pid;
    }

    return m_pid;
}
DTagModeInf::DTagModeInf() {}
DTagModeInf::~DTagModeInf() {}
// 2018 May 29 9:40
int DTagModeInf::NShowers(const int &pid) {
    if (pid == 111 || pid == 2212211 || pid == 221 || pid == 3312211) {
        return 2;
    } else if (pid == 22 || pid == 331222) {
        return 1;
    }
    return 0;
}
