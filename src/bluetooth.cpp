#include "bluetooth.h"

bool ble::initialized = false;
BLEService ble::service = BLEService(BLE_SERVICE_UUID);
BLEBooleanCharacteristic ble::detected = BLEBooleanCharacteristic(BLE_CHARACTERISTIC_DETECTED, BLERead | BLENotify);
BLEUnsignedLongCharacteristic ble::last_detected = BLEUnsignedLongCharacteristic(BLE_CHARACTERISTIC_LAST_DETECTED, BLERead);

bool ble::setup() {
    if (!BLE.begin()){
        return false;
    }

    BLE.setLocalName(BLE_DEVICE_NAME);
    BLE.setAdvertisedService(ble::service);
    ble::service.addCharacteristic(ble::detected);
    ble::service.addCharacteristic(ble::last_detected);

    BLE.addService(ble::service);
    ble::detected.writeValue(0);
    ble::last_detected.writeValue(0);

    BLE.advertise();
    return true;
}

void ble::advertise() {
    if (BLE.connected() || millis() % 1000 < 975 ) {
        return;
    }
    BLE.advertise();
}

void ble::update(bool detected, unsigned long last_detected) {
    if (!BLE.connected()) {
        ble::initialized = false;
        return;
    } else if (!ble::initialized) {
        ble::initialized = true;
    }
    ble::detected.writeValue(detected);
    ble::last_detected.writeValue(last_detected);

    BLE.poll();
}