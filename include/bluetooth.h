#pragma once

#include <ArduinoBLE.h>

#define BLE_DEVICE_NAME "RP2040Connect"
#define BLE_SERVICE_UUID "19B10000-E8F2-537E-4F6C-D104768A1214"
#define BLE_CHARACTERISTIC_DETECTED "19B10001-E8F2-537E-4F6C-D104768A1214"
#define BLE_CHARACTERISTIC_LAST_DETECTED "19B10002-E8F2-537E-4F6C-D104768A1214"


namespace ble {
    extern bool initialized;
    extern BLEService service;
    extern BLEBooleanCharacteristic detected;
    extern BLEUnsignedLongCharacteristic last_detected;

    bool setup();
    void advertise();
    void update(bool detected, unsigned long last_detected);
}