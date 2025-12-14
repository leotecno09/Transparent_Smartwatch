#ifndef BLE_COMMON_H
#define BLE_COMMON_H

#include <BLEDevice.h>
#include <BLEServer.h>
#include <BLEUtils.h>
#include "ble_time_service.h"

void ble_init();
BLEServer* get_ble_server();
void ble_start_advertising();

#endif