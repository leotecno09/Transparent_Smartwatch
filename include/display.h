#ifndef DISPLAY_H
#define DISPLAY_H

#include <U8g2lib.h>

#define TIME_DATE_FONT u8g2_font_littlemissloudonbold_tr
#define INFO_FONT u8g2_font_courB08_tf
#define BL_ICON_FONT u8g2_font_open_iconic_embedded_2x_t
#define BATT_ICON_FONT u8g2_font_battery19_tn

// icons
#define BLUETOOTH_CONNECTED 74
#define FULL_BATT 53

void display_init();
void display_show_time_str(const char*, const char*);
void display_show_centered_str(const char*);
void display_icons(int);
void display_clr_buf();
void display_send_buf();

#endif