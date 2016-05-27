/* 
 * File:   
 * Author: 
 * Comments:
 * Revision history: 
 */

#ifndef STRING_HELPERS_H
#define	STRING_HELPERS_H

#include <xc.h>
#include <stdint.h>
#include <stdbool.h>

#ifdef	__cplusplus
extern "C" {
#endif /* __cplusplus */

bool startsWith(const char *str, const char *pre);
uint16_t ASCIIToNibble(uint8_t nib);
uint16_t ASCIIToHex16(uint8_t* hexStr);
uint16_t ASCIIToHex8(uint8_t* hexStr);

#ifdef	__cplusplus
}
#endif /* __cplusplus */

#endif	/* STRING_HELPERS_H */

