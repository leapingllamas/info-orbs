#ifndef BILLBOARD_DATA_MODEL_H
#define BILLBOARD_DATA_MODEL_H

#include <Arduino.h>

#include <iomanip>

class BillboardMusicDataModel {
   public:
    BillboardMusicDataModel();
    BillboardMusicDataModel &setArtist(String artist);
    String getArtist();
    BillboardMusicDataModel &setSong(String song);
    String getSong();
    BillboardMusicDataModel &setPositionThisWeek(int8_t position);
    int8_t getPositionThisWeek();
    BillboardMusicDataModel &setPositionLastWeek(int8_t position);
    int8_t getPositionLastWeek();
    BillboardMusicDataModel &setPeakPosition(int8_t position);
    int8_t getPeakPosition();
    BillboardMusicDataModel &setWeeksInChart(int8_t n_weeks);
    int8_t getWeeksInChart();
    bool isChanged();
    BillboardMusicDataModel &setChangedStatus(bool changed);

   private:
    String m_artist = "";
    String m_song = "";
    int8_t m_positionThisWeek = 0;
    int8_t m_positionLastWeek = 0;
    int8_t m_peakPosition = 0;
    int8_t m_weeksInChart = 0;
    bool m_changed = false;
};

#endif  // BILLBOARD_DATA_MODEL_H
