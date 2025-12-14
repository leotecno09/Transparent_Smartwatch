#include "ble_common.h"
#include "device_state.h"

static BLEServer* ble_server = nullptr;

class ServerCallbacks : public BLEServerCallbacks {
    void onConnect(BLEServer* server) {
        if (get_current_state() == BLE_DISCONNECTED) {
            update_state(BLE_CONNECTED);
        }
    }

    void onDisconnect(BLEServer* server) {
        if (get_current_state() == BLE_CONNECTED) {
            update_state(BLE_DISCONNECTED);
        }

        ble_start_advertising();                // tornare advertising, nn so se serve anche ble_init() ma nn penso
    }
};

void ble_init() {
    BLEDevice::init("Leo Transparent Smartwatch");
    ble_server = BLEDevice::createServer();
    ble_server->setCallbacks(new ServerCallbacks());
}

BLEServer* get_ble_server() {
    return ble_server;
}

void ble_start_advertising() {
    BLEAdvertising* advertising = BLEDevice::getAdvertising();
    advertising->start();
}
