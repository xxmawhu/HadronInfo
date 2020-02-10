// complete the class GGInfo
template <int pid>
GGInfo<pid>::GGInfo() {
    m_PID = pid;
    m_massPDG = PDG::mass(m_PID);
}
template <int pid>
GGInfo<pid>::GGInfo(const CDCandidate& sig)
    : AvailableInfo() {
    m_PID = pid;
    m_massPDG = PDG::mass(m_PID);
    m_calculate = false;
    this->SetChild(0, sig.finalChildren().second[0]);
    this->SetChild(1, sig.finalChildren().second[1]);
}

template <int pid>
GGInfo<pid>::GGInfo(const EvtRecTrack* trk1, const EvtRecTrack* trk2)
    : AvailableInfo() {
    m_PID = pid;
    m_massPDG = PDG::mass(m_PID);
    m_calculate = false;
    this->SetChild(0, trk1);
    this->SetChild(1, trk2);
}
template <int pid>
GGInfo<pid>::GGInfo(vector<const EvtRecTrack*> trks)
    : AvailableInfo() {
    m_PID = pid;
    m_massPDG = PDG::mass(m_PID);
    m_calculate = false;
    this->SetChild(0, trks[0]);
    this->SetChild(1, trks[1]);
}

template <int pid>
void GGInfo<pid>::SetChild(const int& i, const EvtRecTrack* shower) {
    m_calculate = false;
    m_shower[i] = const_cast<EvtRecTrack*>(shower);
}

template <int pid>
void GGInfo<pid>::Feed(vector<const EvtRecTrack*> shower) {
    m_calculate = false;
    this->SetChild(0, shower[0]);
    this->SetChild(1, shower[1]);
}

template <int pid>
void GGInfo<pid>::Feed(const EvtRecTrack* shower0, const EvtRecTrack* shower1) {
    m_calculate = false;
    this->SetChild(0, shower0);
    this->SetChild(1, shower1);
}

template <int pid>
void GGInfo<pid>::Feed(const CDCandidate& aPi0) {
    m_calculate = false;
    this->SetChild(0, aPi0.finalChildren().second[0]);
    this->SetChild(1, aPi0.finalChildren().second[1]);
}
template <int pid>
int GGInfo<pid>::Charge() {
    return 0;
}

template <int pid>
bool GGInfo<pid>::Calculate() {
    if (m_calculate) return true;
    // update the raw momentum that before 1C kinemitic fit
    ShowerInfo showerInfo;
    showerInfo.SetChild(m_shower[0]);
    HepLorentzVector p4raw1 = showerInfo.P4();
    showerInfo.SetChild(m_shower[1]);
    HepLorentzVector p4raw2 = showerInfo.P4();
    m_rawP4 = p4raw1 + p4raw2;
    m_rawMass = m_rawP4.m();
    m_rawP4Child[0] = p4raw1;
    m_rawP4Child[1] = p4raw2;

    // start the kinemitic fit
    KalmanKinematicFit* m_kmfit;
    m_kmfit = KalmanKinematicFit::instance();
    m_kmfit->init();

    RecEmcShower* photon1 = m_shower[0]->emcShower();
    RecEmcShower* photon2 = m_shower[1]->emcShower();

    m_kmfit->AddTrack(0, 0.0, photon1);
    m_kmfit->AddTrack(1, 0.0, photon2);
    m_kmfit->AddResonance(0, m_massPDG, 0, 1);

    m_kmfit->Fit(0);

    m_chisq = (m_kmfit->chisq(0));

    m_kmfit->BuildVirtualParticle(0);
    m_wtrk = m_kmfit->wVirtualTrack(0);

    HepLorentzVector pfit1 = m_kmfit->pfit(0);
    HepLorentzVector pfit2 = m_kmfit->pfit(1);

    HepLorentzVector ppi0 = pfit1 + pfit2;
    m_P41C = pfit1 + pfit2;
    m_openAngle = cos(pfit1.vect().angle(pfit2.vect()));
    m_helicity = (pfit1.e() - pfit2.e()) / m_P41C.rho();

    const Hep3Vector bvpi0 = -ppi0.boostVector();
    HepLorentzVector pfit1Bv = pfit1;
    pfit1Bv.boost(bvpi0);
    m_helicityAngle = pfit1Bv.vect().angle(-ppi0.vect());
    m_calculate = true;
    return true;
}

template <int pid>
void GGInfo<pid>::AddAvialInfo() {
    AvailableInfo::Add("mass", "double");
    // AvailableInfo::Add("mass1C", "double");
    // AvailableInfo::Add("angle", "double");
    AvailableInfo::Add("openAngle", "double");
    AvailableInfo::Add("helicity", "double");
    AvailableInfo::Add("p4", "HepLorentzVector");
    AvailableInfo::Add("p41C", "HepLorentzVector");
    AvailableInfo::Add("p4GammaHigh", "HepLorentzVector");
    AvailableInfo::Add("p4GammaLow", "HepLorentzVector");
}
template <int pid>
void GGInfo<pid>::GetInfoD(const std::string& info_name, double& targe) {
    if (info_name == "mass") {
        targe = this->Mass();
    } else if (info_name == "openAngle") {
        targe = this->OpenAngle();
    } else if (info_name == "helicity") {
        targe = this->Helicity();
    }
}
template <int pid>
void GGInfo<pid>::GetInfoH(const std::string& info_name,
                           HepLorentzVector& targe) {
    if (info_name == "p4") {
        targe = this->P4();
    } else if (info_name == "p41C") {
        targe = this->p41C();
    } else if (info_name == "p4GammaLow") {
        targe = this->P4GammaLow();
    } else if (info_name == "p4GammaHigh") {
        targe = this->P4GammaHigh();
    }
}

template <int pid>
const double& GGInfo<pid>::Mass() {
    // turn the invarin mass of two gamma before 1C fit
    if (!m_calculate) Calculate();
    return m_mpi0;
}

template <int pid>
const double& GGInfo<pid>::Angle() {
    if (!m_calculate) Calculate();
    return m_angle;
}

template <int pid>
const double& GGInfo<pid>::OpenAngle() {
    if (!m_calculate) Calculate();
    return m_openAngle;
}

template <int pid>
const double& GGInfo<pid>::Helicity() {
    if (!m_calculate) Calculate();
    return m_helicity;
}
template <int pid>
const HepLorentzVector& GGInfo<pid>::P4() {
    if (!m_calculate) Calculate();
    return m_rawP4;
}
template <int pid>
const HepLorentzVector& GGInfo<pid>::p41C() {
    if (!m_calculate) Calculate();
    return m_P41C;
}
template <int pid>
const HepLorentzVector& GGInfo<pid>::P4Child(const int& i) {
    if (!m_calculate) Calculate();
    return m_rawP4Child[i];
}
template <int pid>
const HepLorentzVector& GGInfo<pid>::P4GammaHigh() {
    if (!m_calculate) Calculate();
    if (m_rawP4Child[0].e() > m_rawP4Child[1].e()) {
        return m_rawP4Child[0];
    } else {
        return m_rawP4Child[1];
    }
}

template <int pid>
const HepLorentzVector& GGInfo<pid>::P4GammaLow() {
    if (!m_calculate) Calculate();
    if (m_rawP4Child[0].e() < m_rawP4Child[1].e()) {
        return m_rawP4Child[0];
    } else {
        return m_rawP4Child[1];
    }
}
template <int pid>
const double& GGInfo<pid>::Chisq() {
    if (!m_calculate) Calculate();
    return m_chisq;
}

template <int pid>
const WTrackParameter& GGInfo<pid>::WTrk() {
    if (!m_calculate) Calculate();
    return m_wtrk;
}

template <int pid>
void GGInfo<pid>::UpdateWTrk(const WTrackParameter& newWtrk) {
    m_wtrk = newWtrk;
    m_P41C = newWtrk.p();
    m_mpi0 = newWtrk.mass();
    m_updateWTrk = true;
    m_calculate = false;
}
