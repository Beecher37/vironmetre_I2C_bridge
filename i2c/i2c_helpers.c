#include "i2c_helpers.h"
#include "../mcc_generated_files/pin_manager.h"

#define I2C_RETRY_MAX 5

SensorStatus_t sensorState = { false, 0x00, 0x0000 };

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

bool I2C_Operation(uint8_t dev_addr, uint8_t* p_buffer, uint8_t length,
        void (*functionPtr)(uint8_t*,uint8_t,uint16_t, I2C_MESSAGE_STATUS*))
{
    uint8_t timeOut = 0;
    I2C_MESSAGE_STATUS status = I2C_MESSAGE_PENDING;

    while (!I2C_MasterQueueIsEmpty());

    // Write reg pointer
    while (status != I2C_MESSAGE_FAIL) {
        // write bytes to the device
        (*functionPtr)(p_buffer, length, dev_addr, &status);

        // wait for the message to be sent or status has changed.
        while (status == I2C_MESSAGE_PENDING && sensorState.plugged);

        if (!sensorState.plugged)
            return false;

        if (status == I2C_MESSAGE_COMPLETE)
            return true;

        // check for max retry and skip this byte
        if (timeOut++ >= I2C_RETRY_MAX)
            break;
    }

    return false;
}

uint8_t I2C_FirstDevice() {
    uint8_t addr = 0;
    uint8_t buffer = 0;

    for (addr = 1; addr < 128; addr++) {
        if (I2C_ReadBytes(addr, &buffer, 1))
            return addr;

        if (!sensorState.plugged)
            break;
    }

    return 0;
}
