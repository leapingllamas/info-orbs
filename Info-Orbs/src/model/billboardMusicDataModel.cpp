#include "model/billboardMusicDataModel.h"
#include "utils.h"
#include <config.h>

BillboardMusicDataModel::BillboardMusicDataModel() {
}

BillboardMusicDataModel &BillboardMusicDataModel::setArtist(String artist) {
    if (m_artist != artist) {
        m_artist = String(artist);
        // this is not a regular data field so do not mark changed when set
    }
    return *this;
}
String BillboardMusicDataModel::getArtist() {
    return m_artist;
}

BillboardMusicDataModel &BillboardMusicDataModel::setSong(String song) {
    if (m_song != song) {
        m_song = String(song);
        // this is not a regular data field so do not mark changed when set
    }
    return *this;
}
String BillboardMusicDataModel::getSong() {
    return m_song;
}

BillboardMusicDataModel &BillboardMusicDataModel::setPositionThisWeek(int8_t position) {
    if (m_positionThisWeek != position) {
        m_positionThisWeek = position;
        m_changed = true;
    }
    return *this;
}
int8_t BillboardMusicDataModel::getPositionThisWeek() {
    return m_positionThisWeek;
}

BillboardMusicDataModel &BillboardMusicDataModel::setPositionLastWeek(int8_t position) {
    if (m_positionLastWeek != position) {
        m_positionLastWeek = position;
        m_changed = true;
    }
    return *this;
}
int8_t BillboardMusicDataModel::getPositionLastWeek() {
    return m_positionLastWeek;
}

BillboardMusicDataModel &BillboardMusicDataModel::setPeakPosition(int8_t position) {
    if (m_peakPosition != position) {
        m_peakPosition = position;
        m_changed = true;
    }
    return *this;
}
int8_t BillboardMusicDataModel::getPeakPosition() {
    return m_peakPosition;
}

BillboardMusicDataModel &BillboardMusicDataModel::setWeeksInChart(int8_t position) {
    if (m_weeksInChart != position) {
        m_weeksInChart = position;
        m_changed = true;
    }
    return *this;
}
int8_t BillboardMusicDataModel::getWeeksInChart() {
    return m_weeksInChart;
}

bool BillboardMusicDataModel::isChanged() {
    return m_changed;
}
BillboardMusicDataModel &BillboardMusicDataModel::setChangedStatus(bool changed) {
    m_changed = changed;
    return *this;
}
