#ifndef BILLBOARD_MUSIC_WIDGET_H
#define BILLBOARD_MUSIC_WIDGET_H

#include <ArduinoJson.h>
#include <HTTPClient.h>
#include <TFT_eSPI.h>

#include "model/billboardMusicDataModel.h"
#include "widget.h"

#define MAX_POSITIONS 5

class BillboardMusicWidget : public Widget {
   public:
    BillboardMusicWidget(ScreenManager &manager);
    void setup() override;
    void update(bool force = false) override;
    void draw(bool force = false) override;
    void changeMode() override;

   private:
    void getChartData(BillboardMusicDataModel &position);
    void displayPosition(int8_t displayIndex, BillboardMusicDataModel &position, uint32_t backgroundColor, uint32_t textColor);


    unsigned long m_positionDelay = 86400000;  //default to 24hr in ms between updates
    unsigned long m_positionDelayPrev = 0;

    BillboardMusicDataModel m_positions[MAX_POSITIONS];
    int8_t m_positionCount;
};
#endif  // BILLBOARD_MUSIC_WIDGET_H
