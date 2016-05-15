/* 
 * File:   
 * Author: 
 * Comments:
 * Revision history: 
 */

#ifndef I2C_HELPERS_H
#define	I2C_HELPERS_H

#include <xc.h> 
#include <stdbool.h>
#include <stdint.h>

#ifdef	__cplusplus
extern "C" {
#endif 

uint8_t I2C_FirstDevice();
bool I2C_ReadBytes(uint8_t dev_addr, uint8_t* p_buffer, uint8_t length);
bool I2C_WriteBytes(uint8_t dev_addr, uint8_t* p_buffer, uint8_t length);

#ifdef	__cplusplus
}
#endif 

#endif	// I2C_HELPERS_H

