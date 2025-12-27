#include "ble_common.h"
#include "display.h"
#include "ble_battery_service.h"

static int battery_val;
static std::string isCharging;

class BatteryValCallback : public BLECharacteristicCallbacks {
    void onWrite(BLECharacteristic* characteristic) {
        battery_val = stoi(characteristic->getValue());
        Serial.println("[BLE BatteryValCallback] Received battery");
    }
};

class IsChargingCallback : public BLECharacteristicCallbacks {
    void onWrite(BLECharacteristic* characteristic) {
        isCharging = characteristic->getValue();

        Serial.println("[BLE IsChargingCallback] Received isCharging");
    }
};

void battery_ble_init() {
    BLEServer* server = get_ble_server();
    BLEService* service = server->createService(BATTERY_SERVICE_UUID);

    BLECharacteristic* batteryValChar = service->createCharacteristic(BATTERY_VAL_CHAR, BLECharacteristic::PROPERTY_WRITE);
    BLECharacteristic* isCharging = service->createCharacteristic(BATTERY_IS_CHARGING_CHAR, BLECharacteristic::PROPERTY_WRITE);

    batteryValChar->setCallbacks(new BatteryValCallback());
    isCharging->setCallbacks(new IsChargingCallback());

    service->start();
}

bool is_battery_charging() {
    return isCharging == "true";
}

int get_battery_val_int() {
    return battery_val;
}