#include "i2c_helpers.h"
#include "../mcc_generated_files/i2c.h"
#include "../mcc_generated_files/pin_manager.h"

#define I2C_RETRY_MAX 5

SensorStatus_t SensorState;

void Debounce(bool rawPinValue, bool* oldStableValue, uint16_t* debounceCount) {
    if (rawPinValue == *oldStableValue && *debounceCount > 0)
        (*debounceCount)--;
    else if (rawPinValue != *oldStableValue)
        (*debounceCount)++;

    // If the Input has shown the same value for long enough let's switch it
    if (*debounceCount >= SENSOR_DEBOUNCE_COUNT) {
        *debounceCount = 0;
        *oldStableValue = rawPinValue;
    }
}

uint8_t I2C_FirstDevice() {
    uint8_t addr = 0;
    uint8_t buffer = 0;

    for (addr = 1; addr < 128; addr++) {
        if (I2C_ReadBytes(addr, &buffer, 1))
            return addr;

        if (!SensorState.plugged)
            break;
    }

    return 0;
}

bool I2C_ReadBytes(uint8_t dev_addr, uint8_t* p_buffer, uint8_t length) {
    uint8_t timeOut = 0;
    I2C_MESSAGE_STATUS status = I2C_MESSAGE_PENDING;

    while (!I2C_MasterQueueIsEmpty());

    while (status != I2C_MESSAGE_FAIL) {
        // read buffer from device
        I2C_MasterRead(p_buffer, length, dev_addr, &status);

        // wait for the message to be sent or status has changed.
        while (status == I2C_MESSAGE_PENDING && SensorState.plugged);

        if (!SensorState.plugged)
            return false;

        if (status == I2C_MESSAGE_COMPLETE)
            return true;

        // check for max retry and skip this byte
        if (timeOut >= I2C_RETRY_MAX)
            break;
        else
            timeOut++;
    }

    return false;
}

bool I2C_WriteBytes(uint8_t dev_addr, uint8_t* p_buffer, uint8_t length) {
    uint8_t timeOut = 0;
    I2C_MESSAGE_STATUS status = I2C_MESSAGE_PENDING;

    while (!I2C_MasterQueueIsEmpty());

    // Write reg pointer
    while (status != I2C_MESSAGE_FAIL) {
        // write bytes to the device
        I2C_MasterWrite(p_buffer, length, dev_addr, &status);

        // wait for the message to be sent or status has changed.
        while (status == I2C_MESSAGE_PENDING && SensorState.plugged);

        if (!SensorState.plugged)
            return false;

        if (status == I2C_MESSAGE_COMPLETE)
            return true;

        // check for max retry and skip this byte
        if (timeOut >= I2C_RETRY_MAX)
            break;
        else
            timeOut++;
    }

    return false;
}


