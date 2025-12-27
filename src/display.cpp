#include "display.h"
#include <SPI.h>

U8G2_SSD1309_128X64_NONAME0_F_4W_SW_SPI u8g2(U8G2_R0, 4, 6, 7, 5, 3);

void display_init() {
    u8g2.begin();
}

void display_show_time_str(const char* time_str, const char* date_str) {
    u8g2.setFont(TIME_DATE_FONT);

    int time_str_width = u8g2.getStrWidth(time_str);
    int date_str_width = u8g2.getStrWidth(date_str);

    int centered_x_time = (128 - time_str_width) / 2;
    int centered_x_date = (128 - date_str_width) / 2;

    int centered_y_time = (64 + u8g2.getAscent() - u8g2.getDescent()) / 2;
    int centered_y_date = ((64 + u8g2.getAscent() - u8g2.getDescent()) / 2) - 20;

    u8g2.drawStr(centered_x_time, centered_y_time, time_str);
    u8g2.drawStr(centered_x_date, centered_y_date, date_str);
}

void display_show_centered_str(const char* str) {
    u8g2.setFont(INFO_FONT);

    // calcolo righe necessarie
    int lines = 0;
    char line[64];
    line[0] = '\0';

    const char* ptr = str;

    while (*ptr) {
        char word[32];
        int i = 0;

        while (*ptr && *ptr != ' ') {
            word[i++] = *ptr++;
        }

        word[i] = '\0';

        if (*ptr == ' ') ptr++;

        char testl[64];
        strcpy(testl, line);

        if (strlen(testl) > 0) strcat(testl, " ");
        strcat(testl, word);

        if (u8g2.getStrWidth(testl) <= u8g2.getDisplayWidth()) {
            strcpy(line, testl);
        } else {
            lines++;
            strcpy(line, word);
        }
    }

    if (strlen(line) > 0) lines++;

    // centratura vertical
    int totHeight = lines * u8g2.getMaxCharHeight();
    int y = (u8g2.getDisplayHeight() - totHeight) / 2 + u8g2.getMaxCharHeight();

    // draw
    ptr = str;
    line[0] = '\0';

    while (*ptr) {
        char word[32];
        int i = 0;

        while (*ptr && *ptr != ' ') {
            word[i++] = *ptr++;
        }

        word[i] = '\0';

        if (*ptr == ' ') ptr++;

        char testl[64];
        strcpy(testl, line);

        if (strlen(testl) > 0) strcat(testl, " ");
        strcat(testl, word);

        if (u8g2.getStrWidth(testl) <= u8g2.getDisplayWidth()) {
            strcpy(line, testl);
        } else {
            int x = (u8g2.getDisplayWidth() - u8g2.getStrWidth(line)) / 2;
            u8g2.drawStr(x, y, line);
            y += u8g2.getMaxCharHeight();
            strcpy(line, word);
        }
    }

    if (strlen(line) > 0) {
        int x = (u8g2.getDisplayWidth() - u8g2.getStrWidth(line)) / 2;
        u8g2.drawStr(x, y, line);
    }
}

void display_icons(int icon) {
    switch (icon) {
        case 1:                         // ble connesso
            u8g2.setFont(BL_ICON_FONT);
            u8g2.drawGlyph(3, 20, BLUETOOTH_CONNECTED);
            break;

        case 2:                         // batteria telefono full
            u8g2.setFont(BATT_ICON_FONT);
            u8g2.drawGlyph(115, 25, FULL_BATT);
            break;

        case 3:                        // batteria telefono 4 tacche
            u8g2.setFont(BATT_ICON_FONT);
            u8g2.drawGlyph(115, 25, BATTERY_4);
            break;            
        
        case 4:                        // batteria telefono metà
            u8g2.setFont(BATT_ICON_FONT);
            u8g2.drawGlyph(115, 25, BATTERY_MID);
            break;

        case 5:                        // batteria telefono 2 tacche
            u8g2.setFont(BATT_ICON_FONT);
            u8g2.drawGlyph(115, 25, BATTERY_2);
            break;

        case 6:                       // batteria telefono 1 tacca
            u8g2.setFont(BATT_ICON_FONT);
            u8g2.drawGlyph(115, 25, BATTERY_1);
            break;

        case 7:                       // batteria telefono charging
            u8g2.setFont(BATT_ICON_FONT);
            u8g2.drawGlyph(115, 25, BATTERY_CHARGING);
            break;
    }
}

void display_clr_buf() {
    u8g2.clearBuffer();
}

void display_send_buf() {
    u8g2.sendBuffer();
}