template <int pid>
Track<pid>::Track()
    : m_track(0), m_PID(pid), m_p4(0), m_calculate(false), m_updateWTrk(false) {
    this->AddAvialInfo();
    SetName(BOSS::name(m_PID));
}
template <int pid>
Track<pid>::Track(const EvtRecTrack *track)
    : m_calculate(false), m_updateWTrk(false), m_PID(pid) {
    m_track = const_cast<EvtRecTrack *>(track);
    this->AddAvialInfo();
    AvailableInfo::SetName(BOSS::name(m_PID));
}
template <int pid>
Track<pid>::Track(const CDCandidate &aTrk)
    : m_calculate(false), m_updateWTrk(false), m_PID(pid) {
    const EvtRecTrack *track = aTrk.finalChildren().first[0];
    m_track = const_cast<EvtRecTrack *>(track);
    this->AddAvialInfo();
    AvailableInfo::SetName(BOSS::name(m_PID));
}

template <int pid>
void Track<pid>::Calculate() {
    if (m_calculate) {
        return;
    }
    RecMdcKalTrack *mdcTrk = m_track->mdcKalTrack();
    // const HepPoint3D &ip = GetIP();
    double mass = PDG::mass(pid);
    HepVector helix;
    HepSymMatrix helixError;
    switch (m_PID) {
        case 0:
            RecMdcKalTrack::setPidType(RecMdcKalTrack::electron);
            helix = mdcTrk->getZHelixE();
            helixError = mdcTrk->getZErrorE();
            break;
        case 1:
            RecMdcKalTrack::setPidType(RecMdcKalTrack::muon);
            helix = mdcTrk->getZHelixMu();
            helixError = mdcTrk->getZErrorMu();
            break;
        case 2:
            RecMdcKalTrack::setPidType(RecMdcKalTrack::pion);
            helix = mdcTrk->getZHelix();
            helixError = mdcTrk->getZError();
            break;
        case 3:
            RecMdcKalTrack::setPidType(RecMdcKalTrack::kaon);
            helix = mdcTrk->getZHelixK();
            helixError = mdcTrk->getZErrorK();
            break;
        case 4:
            RecMdcKalTrack::setPidType(RecMdcKalTrack::proton);
            helix = mdcTrk->getZHelixP();
            helixError = mdcTrk->getZErrorP();
            break;
        default:
            RecMdcKalTrack::setPidType(RecMdcKalTrack::pion);
            helix = mdcTrk->getZHelix();
            helixError = mdcTrk->getZError();
            break;
    }
    m_wtrk = WTrackParameter(mass, helix, helixError);
    HepPoint3D point0(0., 0., 0.);
    VFHelix helixip3(point0, helix, helixError);
    const HepPoint3D &ip = GetIP();
    helixip3.pivot(ip);
    HepVector vecipa = helixip3.a();
    m_Rxy = fabs(vecipa[0]);
    m_Rz = fabs(vecipa[3]);
    m_costheta = cos(mdcTrk->theta());
    m_calculate = true;
    m_p4 = m_wtrk.p(); 
    return;
}

template <int pid>
HepLorentzVector Track<pid>::P4() {
    if (m_updateWTrk) {
        return m_p4;
    }
    Calculate();
    return m_p4;
}

template <int pid>
WTrackParameter Track<pid>::WTrk() {
    if (m_updateWTrk) return m_wtrk;
    Calculate();
    return m_wtrk;
}
template <int pid>
double Track<pid>::GetRxy() {
    Calculate();
    return m_Rxy;
}

template <int pid>
double Track<pid>::GetRz() {
    Calculate();
    return m_Rz;
}

template <int pid>
double Track<pid>::GetCosTheta() {
    Calculate();
    return m_costheta;
}

template <int pid>
HepPoint3D Track<pid>::GetIP() {
    Hep3Vector xorigin(0, 0, 0);
    IVertexDbSvc *vtxsvc;
    Gaudi::svcLocator()->service("VertexDbSvc", vtxsvc);
    if (vtxsvc->isVertexValid()) {
        double *dbv = vtxsvc->PrimaryVertex();
        xorigin.setX(dbv[0]);
        xorigin.setY(dbv[1]);
        xorigin.setZ(dbv[2]);
    }
    HepPoint3D IP(xorigin[0], xorigin[1], xorigin[2]);
    return IP;
}

template <int pid>
void Track<pid>::UpdateWTrk(const WTrackParameter &newWtrk) {
    m_wtrk = newWtrk;
    m_p4 = newWtrk.p();
    m_mass = newWtrk.mass();
    m_updateWTrk = true;
    m_calculate = false;
}
template <int pid>
void Track<pid>::Feed(const EvtRecTrack *track) {
    m_calculate = false;
    m_updateWTrk = false;
    m_track = const_cast<EvtRecTrack *>(track);
}
template <int pid>
void Track<pid>::Feed(const CDCandidate &aTrk) {
    m_calculate = false;
    m_updateWTrk = false;
    const EvtRecTrack *track = aTrk.finalChildren().first[0];
    m_track = const_cast<EvtRecTrack *>(track);
}
template <int pid>
Track<pid>::~Track() {}
template <int pid>
void Track<pid>::SetTrack(const EvtRecTrack *track) {
    m_track = const_cast<EvtRecTrack *>(track);
}

template <int pid>
void Track<pid>::GetInfoD(const std::string &info_name, double &targe) {
   //cout << "Info in Track::GetInfoD: " 
   //    << "info_name = " << info_name << endl;
    if (info_name == "Rxy") {
        targe = this->GetRxy();
   //    cout << "Info in Track::GetInfoD: " 
   //        << "targe = " << targe << endl;
    } else if (info_name == "Rz") {
        targe = this->GetRz();
   ///    cout << "Info in Track::GetInfoD: " 
   ///        << "targe = " << targe << endl;
    } else if (info_name == "CosTheta") {
        targe = this->GetCosTheta();
    ///   cout << "Info in Track::GetInfoD: " 
    ///       << "targe = " << targe << endl;
    }
}

template <int pid>
void Track<pid>::GetInfoH(const std::string &info_name,
        HepLorentzVector &targe) {
    if (info_name == "p4") {
        targe = this->P4();
        return;
    }
}
template <int pid>
const int Track<pid>::Charge() { 
    if (m_track) {
        return m_track->mdcKalTrack()->charge(); 
    } else {
        return 0;    
    }
}
template <int pid>
void Track<pid>::AddAvialInfo() {
    AvailableInfo::Add("Rxy", "double");
    AvailableInfo::Add("Rz", "double");
    AvailableInfo::Add("CosTheta", "double");
    AvailableInfo::Add("p4", "HepLorentzVector");
}
