#include "HadronInfoDev/LambdacModeInf.h"

vector<int> LambdacModeInf::getFinalPid(int mode, int charge) {
    vector<int> m_pid;

    if (mode == 0 || mode == 2) {
        m_pid.push_back(2212);
        m_pid.push_back(211);
        m_pid.push_back(211);
        return m_pid;
    }
    if (mode == 1 || mode == 4) {
        m_pid.push_back(2212);
        m_pid.push_back(321);
        m_pid.push_back(211);
        return m_pid;
    }
    if (mode == 3) {
        m_pid.push_back(2212);
        m_pid.push_back(211);
        m_pid.push_back(211);
        m_pid.push_back(211);
        m_pid.push_back(211);
        return m_pid;
    }
    if (mode == 30 || mode == 31 || mode == 32) {
        if (charge > 0) {
            m_pid.push_back(2212);
            m_pid.push_back(211);
            m_pid.push_back(211);
            return m_pid;
        } else {
            m_pid.push_back(211);
            m_pid.push_back(2212);
            m_pid.push_back(211);
            return m_pid;
        }
    }
    if (mode == 33 || mode == 34) {
        if (charge > 0) {
            m_pid.push_back(2212);
            m_pid.push_back(211);
            m_pid.push_back(211);
            m_pid.push_back(211);
            m_pid.push_back(211);
            return m_pid;
        } else {
            m_pid.push_back(211);
            m_pid.push_back(2212);
            m_pid.push_back(211);
            m_pid.push_back(211);
            m_pid.push_back(211);
            return m_pid;
        }
    }
    if (mode == 60 || mode == 61) {
        if (charge > 0) {
            m_pid.push_back(211);
            m_pid.push_back(2212);
            m_pid.push_back(211);
            return m_pid;
        } else {
            m_pid.push_back(211);
            m_pid.push_back(211);
            m_pid.push_back(2212);
            return m_pid;
        }
    }
    if (mode == 62) {
        m_pid.push_back(2212);
        return m_pid;
    }
    if (mode == 63 || mode == 64) {
        m_pid.push_back(211);
        m_pid.push_back(211);
        m_pid.push_back(2212);
        return m_pid;
    }
}
vector<int> LambdacModeInf::getProtonId(int mode, int charge) {
    vector<int> m_pid;

    if (mode == 0 || mode == 1 || mode == 2 || mode == 3 || mode == 4) {
        m_pid.push_back(0);
        return m_pid;
    }
    if (mode == 30 || mode == 31 || mode == 32 || mode == 33 || mode == 34) {
        if (charge > 0) {
            m_pid.push_back(0);
            return m_pid;
        } else {
            m_pid.push_back(1);
            return m_pid;
        }
    }
    if (mode == 60 || mode == 61) {
        if (charge > 0) {
            m_pid.push_back(1);
            return m_pid;
        } else {
            m_pid.push_back(2);
            return m_pid;
        }
    }
    if (mode == 62) {
        m_pid.push_back(0);
        return m_pid;
    }
    if (mode == 63 || mode == 64) {
        m_pid.push_back(2);
        return m_pid;
    }
    return m_pid;
}
vector<int> LambdacModeInf::getLambdaId(int mode, int charge) {
    vector<int> m_pid;

    if (mode == 30 || mode == 31 || mode == 32 || mode == 33 || mode == 34) {
        if (charge > 0) {
            m_pid.push_back(0);
            m_pid.push_back(1);
            return m_pid;
        } else {
            m_pid.push_back(1);
            m_pid.push_back(0);
            return m_pid;
        }
    }
    if (mode == 60 || mode == 61) {
        if (charge > 0) {
            m_pid.push_back(1);
            m_pid.push_back(2);
            return m_pid;
        } else {
            m_pid.push_back(2);
            m_pid.push_back(1);
            return m_pid;
        }
    }
    return m_pid;
}
vector<int> LambdacModeInf::getKsId(int mode, int charge) {
    vector<int> m_pid;

    if (mode == 0 || mode == 2 || mode == 3) {
        m_pid.push_back(1);
        m_pid.push_back(2);
        return m_pid;
    }
    return m_pid;
}
vector<int> LambdacModeInf::getPionId(int mode, int charge) {
    vector<int> m_pid;

    if (mode == 0 || mode == 2) {
        m_pid.push_back(1);
        m_pid.push_back(2);
        return m_pid;
    }
    if (mode == 1) {
        m_pid.push_back(2);
        return m_pid;
    }
    if (mode == 3) {
        m_pid.push_back(1);
        m_pid.push_back(2);
        m_pid.push_back(3);
        m_pid.push_back(4);
        return m_pid;
    }
    if (mode == 4) {
        m_pid.push_back(2);
        return m_pid;
    }
    if (mode == 30 || mode == 31 || mode == 32) {
        if (charge > 0) {
            m_pid.push_back(1);
            m_pid.push_back(2);
            return m_pid;
        } else {
            m_pid.push_back(0);
            m_pid.push_back(2);
            return m_pid;
        }
    }
    if (mode == 33 || mode == 34) {
        if (charge > 0) {
            m_pid.push_back(1);
            m_pid.push_back(2);
            m_pid.push_back(3);
            m_pid.push_back(4);
            return m_pid;
        } else {
            m_pid.push_back(0);
            m_pid.push_back(2);
            m_pid.push_back(3);
            m_pid.push_back(4);
            return m_pid;
        }
    }
    if (mode == 60 || mode == 61) {
        if (charge > 0) {
            m_pid.push_back(0);
            m_pid.push_back(2);
            return m_pid;
        } else {
            m_pid.push_back(0);
            m_pid.push_back(1);
            return m_pid;
        }
    }
    if (mode == 63 || mode == 64) {
        m_pid.push_back(0);
        m_pid.push_back(1);
        return m_pid;
    }
    return m_pid;
}
LambdacModeInf::LambdacModeInf() {}
LambdacModeInf::~LambdacModeInf() {}
