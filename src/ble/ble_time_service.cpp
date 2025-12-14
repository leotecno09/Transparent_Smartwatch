#include "ble_time_service.h"
#include "display.h"
#include "ble_common.h"
#include "device_state.h"

static std::string received_time = "";
static std::string received_date = "";

int hour = 0;
int minute = 0;

unsigned long last_ble_time = 0;

void parse_time_str(const std::string& time_str) {
    hour = std::stoi(time_str.substr(0, 2));
    minute = std::stoi(time_str.substr(3, 2));
}

class TimeCallback : public BLECharacteristicCallbacks {
    void onWrite(BLECharacteristic* characteristic) {
        //last_ble_time = millis();
        received_time = characteristic->getValue();
        parse_time_str(received_time);

        Serial.println("[BLE TimeCallback] Received new time");
    }
};

class DateCallback : public BLECharacteristicCallbacks {
    void onWrite(BLECharacteristic* characteristic) {
        //last_ble_time = millis();

        received_date = characteristic->getValue();

        /*if (get_current_state() == BLE_DISCONNECTED) {
            update_state(BLE_CONNECTED);
        }*/

        Serial.println("[BLE DateCallback] Received new date");
    }
};

void ble_time_init() {
    BLEServer* server = get_ble_server();
    BLEService* service = server->createService(CLOCK_SERVICE_UUID);          // crea il servizio (ble_time) con UUID, da rifare in altri servizi .cpp

    BLECharacteristic* timeChar = service->createCharacteristic(
        TIME_CHAR_UUID,
        BLECharacteristic::PROPERTY_WRITE
    );

    BLECharacteristic* dateChar = service->createCharacteristic(
        DATE_CHAR_UUID,
        BLECharacteristic::PROPERTY_WRITE
    );

    timeChar->setCallbacks(new TimeCallback());
    dateChar->setCallbacks(new DateCallback());

    service->start();
}

void reverse_time_parse() {
    char temp_time_buf[6];

    std::snprintf(temp_time_buf, sizeof(temp_time_buf), "%02d:%02d", hour, minute);

    received_time = temp_time_buf;
}

void increment_time() {
    minute++;

    if (minute >= 60) {
        hour++;
        minute = 0;

        if (hour >= 24) hour = 0;
    }
}

const char* get_received_time() {
    return received_time.c_str();
}

const char* get_received_date() {
    return received_date.c_str();
}

/*unsigned long get_last_ble_time() {
    return last_ble_time;
}*/

/*bool has_new_time() {
    return new_time;
}

bool has_new_date() {
    return new_date;
}*/