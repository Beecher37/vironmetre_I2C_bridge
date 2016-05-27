/* 
 * File:   
 * Author: Thomas Prioul
 * Comments: Helper functions
 * Revision history: 
 */

#ifndef I2C_HELPERS_H
#define	I2C_HELPERS_H

#include <xc.h> 
#include <stdbool.h>
#include <stdint.h>
#include "../mcc_generated_files/i2c.h"

#ifdef	__cplusplus
extern "C" {
#endif 

#define SENSOR_DEBOUNCE_COUNT   1000
typedef struct
{
    bool    plugged;
    uint8_t addr;
    uint16_t debounceCount;
} sensorStatus_t;

//const SensorStatus_t DEFAULT_SENSORSTATUS = { false, 0x00, 0x0000 };

extern sensorStatus_t sensorState;
extern sensorStatus_t oldSensorState;

void Debounce(bool rawPinValue, bool* oldStableValue, uint16_t* debounceCount);

bool I2C_Operation(uint8_t, uint8_t*, uint8_t,
    void (*)(uint8_t*,uint8_t,uint16_t, I2C_MESSAGE_STATUS*));

#define I2C_ReadBytes(dev_addr, p_buffer, length) I2C_Operation(dev_addr, p_buffer, length, I2C_MasterRead)
#define I2C_WriteBytes(dev_addr, p_buffer, length) I2C_Operation(dev_addr, p_buffer, length, I2C_MasterWrite)

uint8_t I2C_FirstDevice();

#ifdef	__cplusplus
}
#endif 

#endif	// I2C_HELPERS_H

