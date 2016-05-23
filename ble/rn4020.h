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
#define RN4020_EXECCMD()                puts(RN4020_NEWLINE)
#define RN4020_CMD                      "CMD"
#define RN4020_END                      "END"
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
#define BATTERY_SERVICE_ID              "180F"
#define BATTERY_VALUE_ID                "2A19"

// Private service
#define VIRON_SERVICE_ID                "2000"
#define VIRON_CHAR_CONN_ID              "3000"
#define VIRON_CHAR_READ_ID              "3001"
#define VIRON_CHAR_WRITE_ID             "3002"
    
#define RN4020_REMOTE_WR_CHAR           "WC,"
#define RN4020_REMOTE_WR_VAL            "WV,"    
    
void RN4020_WriteCharacteristicByte(uint16_t UUID, uint8_t v);
void RN4020_WriteCharacteristicWord(uint16_t UUID, uint16_t v);
void RN4020_WriteCharacteristicBuffer(uint16_t UUID, uint8_t* buf, uint8_t len);
/*
void RN4020_ParseCommand();



uint8_t RN4020_ReadLine(uint8_t* buffer, uint8_t maxLength);
*/

bool RN4020_Init();
void RN4020_ClearInput();

#ifdef	__cplusplus
}
#endif /* __cplusplus */

#endif

