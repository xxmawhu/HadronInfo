#include "HadronInfo/TrackInfo.h"

TrackInfo::TrackInfo() : m_track(0), m_parId(0), m_p4(0) {}

TrackInfo::TrackInfo(const int& pid): m_parId(pid){

}

TrackInfo::TrackInfo(const EvtRecTrack *track) {
    m_track = const_cast<EvtRecTrack *>(track);
}
TrackInfo::TrackInfo(const CDCandidate &aTrk) {
    const EvtRecTrack *track = aTrk.finalChildren().first[0];
    m_track = const_cast<EvtRecTrack *>(track);
}

TrackInfo::~TrackInfo() {
    m_track = 0;
    m_parId = 0;
    m_p4 = HepLorentzVector(0, 0, 0, 0);
}

void TrackInfo::SetTrack(const int &parId, const EvtRecTrack *track) {
    m_parId = abs(parId);
    m_track = const_cast<EvtRecTrack *>(track);
}

void TrackInfo::SetTrack(const EvtRecTrack *track) {
    m_track = const_cast<EvtRecTrack *>(track);
}

HepLorentzVector TrackInfo::p4() {
    calculate();
    return m_p4;
}

HepLorentzVector TrackInfo::p4(const int &pid) {
    m_parId = abs(pid);
    calculate();
    return m_p4;
}
HepLorentzVector TrackInfo::p4(EvtRecTrack *atrk, const int &pid) {
    m_parId = abs(pid);
    m_track = atrk;
    calculate();
    return m_p4;
}
HepLorentzVector TrackInfo::p4c(const EvtRecTrack *atrk, const int &pid) {
    m_parId = abs(pid);
    m_track = const_cast<EvtRecTrack *>(atrk);
    calculate();
    return m_p4;
}
WTrackParameter TrackInfo::wtrkc(const EvtRecTrack *atrk, const int &pid) {
    m_parId = abs(pid);
    m_track = const_cast<EvtRecTrack *>(atrk);
    calculate();
    return m_wtrk;
}
WTrackParameter TrackInfo::wtrk(EvtRecTrack *atrk, const int &pid) {
    m_parId = abs(pid);
    m_track = atrk;
    calculate();
    return m_wtrk;
}
WTrackParameter TrackInfo::wtrk(const int &pid) {
    m_parId = abs(pid);
    calculate();
    return m_wtrk;
}
void TrackInfo::calculate() {
    m_p4 = HepLorentzVector(0, 0, 0, 0);
    if (m_parId == 22) {
        RecEmcShower *shower = m_track->emcShower();
        double eraw = shower->energy();
        double phi = shower->phi();
        double the = shower->theta();
        m_p4.setPx(eraw * sin(the) * cos(phi));
        m_p4.setPy(eraw * sin(the) * sin(phi));
        m_p4.setPz(eraw * cos(the));
        m_p4.setE(eraw);

        double dphi = shower->dphi();
        double dtheta = shower->dtheta();
        double dE = shower->dE();
        m_wtrk = WTrackParameter(m_p4, dphi, dtheta, dE);
        return;
    } else {
        RecMdcKalTrack *mdcTrk = m_track->mdcKalTrack();
        if (m_parId == 11) {
            double mass = 0.000511;
            RecMdcKalTrack::setPidType(RecMdcKalTrack::electron);
            m_p4 = mdcTrk->p4(mass);
            m_wtrk = WTrackParameter(mass, mdcTrk->getZHelixE(),
                                     mdcTrk->getZErrorE());

            return;
        }
        if (m_parId == 13) {
            double mass = 0.105658;
            RecMdcKalTrack::setPidType(RecMdcKalTrack::muon);
            m_p4 = mdcTrk->p4(mass);
            m_wtrk = WTrackParameter(mass, mdcTrk->getZHelixMu(),
                                     mdcTrk->getZErrorMu());
            return;
        }
        if (m_parId == 211) {
            double mass = 0.139570;
            RecMdcKalTrack::setPidType(RecMdcKalTrack::pion);
            m_p4 = mdcTrk->p4(mass);
            m_wtrk =
                WTrackParameter(mass, mdcTrk->getZHelix(), mdcTrk->getZError());
            return;
        }
        if (m_parId == 321) {
            double mass = 0.493677;
            RecMdcKalTrack::setPidType(RecMdcKalTrack::kaon);
            m_p4 = mdcTrk->p4(mass);
            m_wtrk = WTrackParameter(mass, mdcTrk->getZHelixK(),
                                     mdcTrk->getZErrorK());
            return;
        }
        if (m_parId == 2212) {
            double mass = 0.938272;
            RecMdcKalTrack::setPidType(RecMdcKalTrack::proton);
            m_p4 = mdcTrk->p4(mass);
            m_wtrk = WTrackParameter(mass, mdcTrk->getZHelixP(),
                                     mdcTrk->getZErrorP());
            return;
        }
    }
}

TrackInfo &TrackInfo::operator=(TrackInfo &aTrackInfo) {
    m_track = aTrackInfo.m_track;
    return *this;
}
double TrackInfo::GetDoubleInfo(const string &info_name) {
    return -110;
}

HepLorentzVector TrackInfo::GetLorentzVector(const string &info_name) {
    if (info_name == "p4") return this->p4();
    return HepLorentzVector(0, 0, 0, -110);
}

