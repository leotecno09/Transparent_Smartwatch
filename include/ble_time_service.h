#ifndef BLE_TIME_H
#define BLE_TIME_H

#define CLOCK_SERVICE_UUID "41b40c88-1f7a-42dc-8af1-37a51b793cde"                 // rappresenta un servizio (es: ble_time), usato dal client per trovare il servizio corretto
#define TIME_CHAR_UUID "e58fcf7e-f9cb-448c-b31e-ad022c229cc2"          // rappresenta una caratteristica (variabile es: ora) dentro il servizio
#define DATE_CHAR_UUID "f986fb73-bde5-4d75-81e9-7101fa9371d6"

#define BLE_TIME_TIMEOUT 60000

void ble_time_init();
const char* get_received_time();
const char* get_received_date();
bool has_new_time();
bool has_new_date();
//unsigned long get_last_ble_time();
void increment_time();
//void parse_time_str(const std::string&);
void reverse_time_parse();

#endif