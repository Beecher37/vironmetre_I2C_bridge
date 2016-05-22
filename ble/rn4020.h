/* 
 * File:   
 * Author: 
 * Comments:
 * Revision history: 
 */

#ifndef RN4020_H
#define	RN4020_H

#include <xc.h>
#include "../mcc_generated_files/eusart.h"

#ifdef	__cplusplus
extern "C" {
#endif /* __cplusplus */

////////////////////////////////////////////////////////////////////////////////
// Common RN4020 commands and strings  
////////////////////////////////////////////////////////////////////////////////
#define RN4020_NEWLINE                  "\r\n"
#define RN4020_EXECCMD()                EUSART_Write('\r'); EUSART_Write('\n')
#define RN4020_CMD_START                "CMD"
#define RN4020_CMD_END                  "END"
#define RN4020_AOK                      "AOK"
#define RN4020_CONN_START               "Connected"
#define RN4020_CONN_END                 "Connection End"
#define RN4020_CONN_PARAM               "ConnParam:"    

////////////////////////////////////////////////////////////////////////////////
// Services and characteristics
////////////////////////////////////////////////////////////////////////////////

#define RN4020_WRITE_CHAR               "SUW,%X4,"
#define RN4020_READ_CHAR                "SUR,%X4"
    
// Battery service
#define BATTERY_SERVICE_ID              0x180F
#define BATTERY_VALUE_ID                0x2A19

// Private service
#define VIRON_SERVICE_ID                0x2000
#define VIRON_CHAR_CONN_ID              0x3000
#define VIRON_CHAR_READ_ID              0x3001
#define VIRON_CHAR_WRITE_ID             0x3002
    
#define RN4020_REMOTE_WR_CHAR           "WC,"
#define RN4020_REMOTE_WR_VAL            "WV,"    
    
void RN4020_WriteCharacteristicByte(uint16_t UUID, uint8_t value);
void RN4020_WriteCharacteristicWord(uint16_t UUID, uint16_t value);
void RN4020_WriteCharacteristicBuffer(uint16_t UUID, uint8_t* buffer,
        uint8_t length);

void RN4020_ParseCommand();

#ifdef	__cplusplus
}
#endif /* __cplusplus */

#endif

