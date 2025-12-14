#ifndef DEVICE_STATE_H
#define DEVICE_STATE_H

enum DeviceState {
  BLE_CONNECTED,
  BLE_DISCONNECTED
};

DeviceState get_current_state();
void update_state(DeviceState newState);

#endif