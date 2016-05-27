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

typedef struct {
    bool    plugged;
    uint8_t addr;
    uint16_t debounceCount;
} sensorStatus_t;

extern sensorStatus_t sensorState;
extern sensorStatus_t oldSensorState;

bool I2C_Operation(uint8_t, uint8_t*, uint8_t,
    void (*)(uint8_t*,uint8_t,uint16_t, I2C_MESSAGE_STATUS*));

#define I2C_ReadBytes(dev_addr, p_buffer, length) I2C_Operation(dev_addr, p_buffer, length, I2C_MasterRead)
#define I2C_WriteBytes(dev_addr, p_buffer, length) I2C_Operation(dev_addr, p_buffer, length, I2C_MasterWrite)

uint8_t I2C_FirstDevice();

#ifdef	__cplusplus
}
#endif 

#endif	// I2C_HELPERS_H

