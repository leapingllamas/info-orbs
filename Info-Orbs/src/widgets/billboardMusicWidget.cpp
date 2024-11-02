#include "widgets/billboardMusicWidget.h"

#include <ArduinoJson.h>
#include <HTTPClient.h>
#include <config.h>

#include <iomanip>
                
BillboardMusicWidget::BillboardMusicWidget(ScreenManager &manager) : Widget(manager) {
    m_positionCount = 5; //we are always guaranteed 5 slots
    for (int8_t i = 0; i < 5; i++) {
        m_positions[i] = BillboardMusicDataModel();
    }
}

void BillboardMusicWidget::setup() {
    return;
}

void BillboardMusicWidget::draw(bool force) {
    for (int8_t i = 0; i < m_positionCount; i++) {
        if (m_positions[i].isChanged() || force) {
            displayPosition(i, m_positions[i], TFT_WHITE, TFT_BLACK);
            m_positions[i].setChangedStatus(false);
        }
    }
}

void BillboardMusicWidget::update(bool force) {
    if (force || m_positionDelayPrev == 0 || (millis() - m_positionDelayPrev) >= m_positionDelay) {
        setBusy(true);
        String httpRequestAddress = "https://raw.githubusercontent.com/mhollingshead/billboard-hot-100/main/recent.json";

        HTTPClient http;
        http.begin(httpRequestAddress);
        int httpCode = http.GET();

        if (httpCode > 0) {  // Check for the returning code
            String payload = http.getString();
            JsonDocument doc;
            DeserializationError error = deserializeJson(doc, payload);

            if (!error) {

                for (int8_t i = 0; i < m_positionCount; i++) {
                    //TODO get i'th position from the json
                    //d = doc["data"][i];

                    m_positions[i].setArtist(doc["data"][i]["artist"]);
                    m_positions[i].setSong(doc["data"][i]["song"]);
                    m_positions[i].setPositionLastWeek(doc["data"][i]["last_week"].as<float>());//TODO handle last week is NULL
                    m_positions[i].setPositionThisWeek(doc["data"][i]["this_week"].as<float>());
                    m_positions[i].setPeakPosition(doc["data"][i]["peak_position"].as<float>());
                    m_positions[i].setWeeksInChart(doc["data"][i]["weeks_on_chart"].as<float>());
                }
                setBusy(false);
                m_positionDelayPrev = millis();
            } else {
                // Handle JSON deserialization error
                Serial.println("deserializeJson() failed");
            }
        } else {
            // Handle HTTP request error
            Serial.printf("HTTP request failed, error: %s\n", http.errorToString(httpCode).c_str());
        }

        http.end();

    }
}

void BillboardMusicWidget::changeMode() {
    update(true);
}

void BillboardMusicWidget::displayPosition(int8_t displayIndex, BillboardMusicDataModel &position, uint32_t backgroundColor, uint32_t textColor) {
    Serial.println("displayPosition - " + String(position.getPositionThisWeek()) + " ~ " + String(position.getSong()) + " ~ " + String(position.getArtist()));
    m_manager.selectScreen(displayIndex);

    TFT_eSPI &display = m_manager.getDisplay();

    display.fillScreen(TFT_BLACK);
    display.setTextColor(TFT_WHITE);
    display.setTextSize(4);  // Set text size

    // Calculate center positions
    int screenWidth = display.width();
    int centre = 120;

    // Draw position data
    display.fillRect(0, 0, screenWidth, 50, 0x0256);  // rgb565 colors
    
    //display.drawString(position.getArtist(), centre, 27, 1);
    display.drawString(String(position.getPositionThisWeek()), centre, 27, 1);

    display.setTextSize(2);
    display.drawString(position.getArtist(), centre, 100, 1);
    display.setTextSize(4);

    display.setTextSize(2);
    display.setTextColor(TFT_MAGENTA, TFT_BLACK);
    display.drawString(position.getSong(), centre,147, 1 );
    display.setTextSize(4);

    if (position.getPositionThisWeek() == position.getPositionLastWeek()) {
        display.setTextSize(3);
        display.setTextColor(TFT_LIGHTGREY, TFT_BLACK);
        display.drawString("SAME",centre, 200, 1);
        display.setTextSize(4);
    }
    else if (position.getPositionThisWeek() > position.getPositionLastWeek()
        && position.getPositionLastWeek() > 0
    ) {
        display.setTextColor(TFT_RED, TFT_BLACK);
        display.fillTriangle(120, 220, 140, 185, 100, 185, TFT_RED);

        display.setTextSize(2);
        display.setTextColor(TFT_WHITE, TFT_BLACK);
        display.drawString("week",centre - 56, 190, 1);
        display.drawString(String(position.getWeeksInChart()),centre - 45, 210, 1);
        display.drawString("from",centre + 55, 190, 1);
        display.drawString(String(position.getPositionLastWeek()),centre + 41, 210, 1);
        display.setTextSize(4);

    }
    else if (position.getPositionThisWeek() < position.getPositionLastWeek()
        && position.getPositionLastWeek() > 0    
    ) {
        display.setTextColor(TFT_GREEN, TFT_BLACK);
        display.fillTriangle(120, 185, 140, 220, 100, 220, TFT_GREEN);
    }
    else {
        display.setTextSize(3);
        display.setTextColor(TFT_YELLOW, TFT_BLACK);
        display.drawString("NEW!",centre, 200, 1);
        display.setTextSize(4);
    }

    // display.drawString(stock.getPercentChange(2) + "%", centre, 147, 1);
    //display.drawString(String(position.getPositionThisWeek()), centre,147, 1 );

}
