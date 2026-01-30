#ifndef H_BLUETOOTH
#define H_BLUETOOTH

#include "simplecble/simpleble.h"

#define BLE_SCAN_TIME 5000

int ble_init();
void ble_start_scan();
void ble_stop_scan();

#endif