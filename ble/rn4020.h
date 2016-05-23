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
    
#define BATTERY_VALUE_STR               "2A19,0017,V"
#define BATTERY_CHAR_STR                "2A19,0018,C"

// Private service
#define VIRONMETRE_SERVICE_ID_STR       "2000"
#define CONNECTION_ID_STR               "3000"
#define REQUEST_ID_STR                  "3001"
#define ANSWER_ID_STR                   "3002"
    
#define CONNECTION_VALUE_STR            "3000,000E,V"    
#define CONNECTION_CHAR_STR             "3000,000F,C" 
 
#define REQUEST_VALUE_STR               "3001,0011,V"    
    
#define ANSWER_VALUE_STR                "3002,0013,V"    
#define ANSWER_CHAR_STR                 "3002,0014,C" 
    
#define CONNECTION_ID                   0x3000
#define REQUEST_ID                      0x3001
#define ANSWER_ID                       0x3002

#define CONNECTION_HANDLE               0x000E
#define REQUEST_HANDLE                  0x0011
#define ANSWER_HANDLE                   0x0013    
    
#define RN4020_REMOTE_WR_CHAR           "WC"
#define RN4020_REMOTE_WR_VAL            "WV"    
    
    
#define RN4020_ListServices()           printf("LS\r\n")
    
void RN4020_WriteCharacteristicByte(uint16_t UUID, uint8_t v);
void RN4020_WriteCharacteristicWord(uint16_t UUID, uint16_t v);
void RN4020_WriteCharacteristicBuffer(uint16_t UUID, uint8_t* buf, uint8_t len);

bool RN4020_Init();
void RN4020_ClearInput();
bool startsWith(const char *str, const char *pre);
uint16_t ASCIIToNibble(uint8_t nib);
uint16_t ASCIIToHex16(uint8_t* hexStr);
uint8_t ASCIIToHex8(uint8_t* hexStr);

#ifdef	__cplusplus
}
#endif /* __cplusplus */

#endif

