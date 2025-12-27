#ifndef BLE_BATTERY_SERVICE_H
#define BLE_BATTERY_SERVICE_H

#define BATTERY_SERVICE_UUID "6edd2332-6529-4e3c-83b0-d283bd20d93f"
#define BATTERY_VAL_CHAR "2538b962-e8d8-4f12-954f-d30675b1b6d1"
#define BATTERY_IS_CHARGING_CHAR "975ea9e7-cec0-4060-bad2-853038577f90"

void battery_ble_init();
bool is_battery_charging();
int get_battery_val_int();

#endif