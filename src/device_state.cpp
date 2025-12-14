#include <Arduino.h>
#include "device_state.h"

volatile DeviceState currentState = BLE_DISCONNECTED;           // volatile indica che può cambiare in qualsiasi moment

DeviceState get_current_state() {
    return currentState;
}

void update_state(DeviceState newState) {
    currentState = newState;
    Serial.println("[WARN] State changed!");

    if (currentState == BLE_DISCONNECTED)
        Serial.println("Now in BLE_DISCONNECTED");
    else
        Serial.println("Now in BLE_CONNECTED");
}