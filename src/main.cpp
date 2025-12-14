#include <Arduino.h>
#include "display.h"
#include "ble_common.h"
#include "device_state.h"

#define DISPLAY_UPDATE_TIMEOUT 1000

unsigned long last_display_update = 0;
unsigned long last_time_update = 0;

void setup() {
  Serial.begin(9600);

  display_init();

  ble_init();
  Serial.println("[BLE] BLE initialized.");

  ble_time_init();
  Serial.println("[BLE] BLE Time Service initialized.");

  ble_start_advertising();

  Serial.println("[BLE] Now advertising");

  display_clr_buf();
  display_show_centered_str("Boot OK");
  display_send_buf();
}

void loop() {
  unsigned long now = millis();

  /*if (get_current_state() == BLE_CONNECTED) {
    if (now - get_last_ble_time() > BLE_TIME_TIMEOUT) {
      // siamo disconessi porcodd
      update_state(BLE_DISCONNECTED);
      Serial.println("BLE_TIME_TIMEOUT exceeded. Entering BLE_DISCONNECTED status.");

      display_clr_buf();
      display_show_centered_str("Bluetooth disconnected.");

      display_to_update = true;
    }
  }*/

  /*if (get_received_date() == "NODATA" || get_received_time() == "NODATA") {
    display_clr_buf();
    display_show_centered_str("Waiting for connection...");

    Serial.println("Waiting for bluetooth data...");
  } else {*/

  /*if (get_current_state() == BLE_DISCONNECTED) {
      // contiamo da soli uau
      Serial.println("conto da solooaoa");

  } else {

  }*/

  if (get_current_state() == BLE_DISCONNECTED) {
    if (now - last_time_update >= 60000) {
      last_time_update += 60000;
      increment_time();
    }
  } else {
    last_time_update = now;
  }

  if (now - last_display_update >= DISPLAY_UPDATE_TIMEOUT) {
    display_clr_buf();

    if (get_current_state() == BLE_CONNECTED) {
      display_icons(1);
      display_icons(2);
      display_show_time_str(get_received_time(), get_received_date());
    } else {
      reverse_time_parse();
      display_show_time_str(get_received_time(), "");
    }


    display_send_buf();

    last_display_update = now;
    Serial.println("Data updated.");
  }

  //delay(1000);
}