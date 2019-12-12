#include "HadronInfo/DTagModeInf.h"
vector<int> DTagModeInf::FinalID(const int &mode) {
    vector<int> m_pid;
    if (mode == 0) {
        m_pid.push_back(-321);
        m_pid.push_back(211);
        return m_pid;
    }
    if (mode == 1) {
        m_pid.push_back(-321);
        m_pid.push_back(211);
        m_pid.push_back(111);
        return m_pid;
    }
    if (mode == 2) {
        m_pid.push_back(-321);
        m_pid.push_back(211);
        m_pid.push_back(111);
        m_pid.push_back(111);
        return m_pid;
    }
    if (mode == 3) {
        m_pid.push_back(-321);
        m_pid.push_back(211);
        m_pid.push_back(211);
        m_pid.push_back(-211);
        return m_pid;
    }
    if (mode == 4) {
        m_pid.push_back(-321);
        m_pid.push_back(211);
        m_pid.push_back(211);
        m_pid.push_back(-211);
        m_pid.push_back(111);
        return m_pid;
    }
    if (mode == 5) {
        m_pid.push_back(-321);
        m_pid.push_back(211);
        m_pid.push_back(221);
        return m_pid;
    }
    if (mode == 50) {
        m_pid.push_back(310);
        m_pid.push_back(-321);
        m_pid.push_back(211);
        return m_pid;
    }
    if (mode == 51) {
        m_pid.push_back(310);
        m_pid.push_back(-321);
        m_pid.push_back(211);
        m_pid.push_back(111);
        return m_pid;
    }
    if (mode == 100) {
        m_pid.push_back(310);
        m_pid.push_back(211);
        m_pid.push_back(-211);
        return m_pid;
    }
    if (mode == 101) {
        m_pid.push_back(310);
        m_pid.push_back(211);
        m_pid.push_back(-211);
        m_pid.push_back(111);
        return m_pid;
    }
    if (mode == 102) {
        m_pid.push_back(310);
        m_pid.push_back(111);
        return m_pid;
    }
    if (mode == 103) {
        m_pid.push_back(211);
        m_pid.push_back(-211);
        m_pid.push_back(111);
        return m_pid;
    }
    if (mode == 104) {
        m_pid.push_back(211);
        m_pid.push_back(-211);
        return m_pid;
    }
    if (mode == 105) {
        m_pid.push_back(321);
        m_pid.push_back(-321);
        return m_pid;
    }
    if (mode == 106) {
        m_pid.push_back(321);
        m_pid.push_back(-321);
        m_pid.push_back(111);
        return m_pid;
    }
    if (mode == 107) {
        m_pid.push_back(111);
        m_pid.push_back(111);
        return m_pid;
    }
    if (mode == 108) {
        m_pid.push_back(310);
        m_pid.push_back(310);
        return m_pid;
    }
    if (mode == 109) {
        m_pid.push_back(310);
        m_pid.push_back(310);
        m_pid.push_back(111);
        return m_pid;
    }
    if (mode == 110) {
        m_pid.push_back(310);
        m_pid.push_back(111);
        m_pid.push_back(111);
        return m_pid;
    }
    if (mode == 111) {
        m_pid.push_back(310);
        m_pid.push_back(321);
        m_pid.push_back(-321);
        return m_pid;
    }
    if (mode == 112) {
        m_pid.push_back(310);
        m_pid.push_back(221);
        return m_pid;
    }
    if (mode == 113) {
        m_pid.push_back(111);
        m_pid.push_back(111);
        m_pid.push_back(111);
        return m_pid;
    }
    if (mode == 114) {
        m_pid.push_back(310);
        m_pid.push_back(310);
        m_pid.push_back(310);
        return m_pid;
    }
    if (mode == 115) {
        m_pid.push_back(211);
        m_pid.push_back(211);
        m_pid.push_back(211);
        m_pid.push_back(-211);
        return m_pid;
    }
    if (mode == 116) {
        m_pid.push_back(211);
        m_pid.push_back(-211);
        m_pid.push_back(111);
        m_pid.push_back(111);
        return m_pid;
    }
    if (mode == 117) {
        m_pid.push_back(321);
        m_pid.push_back(-321);
        m_pid.push_back(211);
        m_pid.push_back(-211);
        return m_pid;
    }
    if (mode == 118) {
        m_pid.push_back(321);
        m_pid.push_back(-321);
        m_pid.push_back(111);
        m_pid.push_back(111);
        return m_pid;
    }
    if (mode == 119) {
        m_pid.push_back(310);
        m_pid.push_back(310);
        m_pid.push_back(211);
        m_pid.push_back(-211);
        return m_pid;
    }
    if (mode == 120) {
        m_pid.push_back(211);
        m_pid.push_back(211);
        m_pid.push_back(-211);
        m_pid.push_back(-211);
        m_pid.push_back(111);
        return m_pid;
    }
    if (mode == 121) {
        m_pid.push_back(310);
        m_pid.push_back(211);
        m_pid.push_back(211);
        m_pid.push_back(-211);
        m_pid.push_back(-211);
        return m_pid;
    }
    if (mode == 122) {
        m_pid.push_back(321);
        m_pid.push_back(-321);
        m_pid.push_back(211);
        m_pid.push_back(-211);
        m_pid.push_back(111);
        return m_pid;
    }
    if (mode == 123) {
        m_pid.push_back(310);
        m_pid.push_back(111);
        m_pid.push_back(221);
        return m_pid;
    }
    if (mode == 124) {
        m_pid.push_back(310);
        m_pid.push_back(331);
        return m_pid;
    }
    if (mode == 125) {
        return m_pid;
    }
    if (mode == 126) {
        return m_pid;
    }
    if (mode == 200) {
        m_pid.push_back(-321);
        m_pid.push_back(211);
        m_pid.push_back(211);
        return m_pid;
    }
    if (mode == 201) {
        m_pid.push_back(-321);
        m_pid.push_back(211);
        m_pid.push_back(211);
        m_pid.push_back(111);
        return m_pid;
    }
    if (mode == 202) {
        m_pid.push_back(310);
        m_pid.push_back(211);
        return m_pid;
    }
    if (mode == 203) {
        m_pid.push_back(310);
        m_pid.push_back(211);
        m_pid.push_back(111);
        return m_pid;
    }
    if (mode == 204) {
        m_pid.push_back(310);
        m_pid.push_back(211);
        m_pid.push_back(211);
        m_pid.push_back(-211);
        return m_pid;
    }
    if (mode == 205) {
        m_pid.push_back(-321);
        m_pid.push_back(321);
        m_pid.push_back(211);
        return m_pid;
    }
    if (mode == 206) {
        m_pid.push_back(211);
        m_pid.push_back(111);
        return m_pid;
    }
    if (mode == 207) {
        m_pid.push_back(321);
        m_pid.push_back(111);
        return m_pid;
    }
    if (mode == 208) {
        m_pid.push_back(310);
        m_pid.push_back(321);
        return m_pid;
    }
    if (mode == 209) {
        m_pid.push_back(211);
        m_pid.push_back(211);
        m_pid.push_back(-211);
        return m_pid;
    }
    if (mode == 210) {
        m_pid.push_back(211);
        m_pid.push_back(111);
        m_pid.push_back(111);
        return m_pid;
    }
    if (mode == 211) {
        m_pid.push_back(310);
        m_pid.push_back(310);
        m_pid.push_back(211);
        return m_pid;
    }
    if (mode == 212) {
        m_pid.push_back(310);
        m_pid.push_back(321);
        m_pid.push_back(111);
        return m_pid;
    }
    if (mode == 213) {
        m_pid.push_back(310);
        m_pid.push_back(310);
        m_pid.push_back(321);
        return m_pid;
    }
    if (mode == 214) {
        m_pid.push_back(211);
        m_pid.push_back(211);
        m_pid.push_back(-211);
        m_pid.push_back(111);
        return m_pid;
    }
    if (mode == 215) {
        m_pid.push_back(211);
        m_pid.push_back(111);
        m_pid.push_back(111);
        return m_pid;
    }
    if (mode == 216) {
        m_pid.push_back(310);
        m_pid.push_back(321);
        m_pid.push_back(211);
        m_pid.push_back(-211);
        return m_pid;
    }
    if (mode == 217) {
        m_pid.push_back(310);
        m_pid.push_back(-321);
        m_pid.push_back(211);
        m_pid.push_back(211);
        return m_pid;
    }
    if (mode == 218) {
        m_pid.push_back(-321);
        m_pid.push_back(321);
        m_pid.push_back(211);
        m_pid.push_back(111);
        return m_pid;
    }
    if (mode == 219) {
        m_pid.push_back(211);
        m_pid.push_back(211);
        m_pid.push_back(211);
        m_pid.push_back(-211);
        m_pid.push_back(-211);
        return m_pid;
    }
    if (mode == 220) {
        m_pid.push_back(-321);
        m_pid.push_back(211);
        m_pid.push_back(211);
        m_pid.push_back(211);
        m_pid.push_back(-211);
        return m_pid;
    }
    if (mode == 221) {
        m_pid.push_back(211);
        m_pid.push_back(221);
        return m_pid;
    }
    if (mode == 222) {
        return m_pid;
    }
    if (mode == 300) {
        m_pid.push_back(-321);
        m_pid.push_back(321);
        m_pid.push_back(321);
        return m_pid;
    }
    if (mode == 400) {
        m_pid.push_back(310);
        m_pid.push_back(321);
        return m_pid;
    }
    if (mode == 401) {
        m_pid.push_back(321);
        m_pid.push_back(-321);
        m_pid.push_back(211);
        return m_pid;
    }
    if (mode == 402) {
        m_pid.push_back(310);
        m_pid.push_back(321);
        m_pid.push_back(111);
        return m_pid;
    }
    if (mode == 403) {
        m_pid.push_back(310);
        m_pid.push_back(310);
        m_pid.push_back(211);
        return m_pid;
    }
    if (mode == 404) {
        m_pid.push_back(321);
        m_pid.push_back(-321);
        m_pid.push_back(211);
        m_pid.push_back(111);
        return m_pid;
    }
    if (mode == 405) {
        m_pid.push_back(310);
        m_pid.push_back(321);
        m_pid.push_back(211);
        m_pid.push_back(-211);
        return m_pid;
    }
    if (mode == 406) {
        m_pid.push_back(310);
        m_pid.push_back(-321);
        m_pid.push_back(211);
        m_pid.push_back(211);
        return m_pid;
    }
    if (mode == 407) {
        return m_pid;
    }
    if (mode == 420) {
        return m_pid;
    }
    if (mode == 421) {
        return m_pid;
    }
    if (mode == 422) {
        return m_pid;
    }
    if (mode == 423) {
        return m_pid;
    }
    if (mode == 424) {
        return m_pid;
    }
    if (mode == 425) {
        return m_pid;
    }
    if (mode == 440) {
        return m_pid;
    }
    if (mode == 441) {
        return m_pid;
    }
    if (mode == 442) {
        return m_pid;
    }
    if (mode == 450) {
        return m_pid;
    }
    if (mode == 451) {
        return m_pid;
    }
    if (mode == 452) {
        return m_pid;
    }
    if (mode == 460) {
        return m_pid;
    }
    if (mode == 461) {
        return m_pid;
    }
    if (mode == 470) {
        return m_pid;
    }
    if (mode == 471) {
        return m_pid;
    }
    if (mode == 480) {
        m_pid.push_back(211);
        m_pid.push_back(331);
        return m_pid;
    }
    if (mode == 481) {
        return m_pid;
    }
    if (mode == 600) {
        m_pid.push_back(321);
        m_pid.push_back(-321);
        m_pid.push_back(211);
        m_pid.push_back(221);
        return m_pid;
    }
    if (mode == 601) {
        m_pid.push_back(321);
        m_pid.push_back(-321);
        m_pid.push_back(211);
        m_pid.push_back(2212211);
        return m_pid;
    }
}
