/* 
 * File:   
 * Author: 
 * Comments:
 * Revision history: 
 */

#ifndef BLUETOOTH_LE_H
#define	BLUETOOTH_LE_H

#include <xc.h>

#ifdef	__cplusplus
extern "C" {
#endif /* __cplusplus */

// Common RN4020 commands
    
#define LINE            "\r\n"
#define CMD_START       "CMD"
#define CMD_END         "END"
#define AOK             "AOK"
#define CONN_START      "Connected"
#define CONN_END        "Connection End"
#define CONN_PARAM      "ConnParam:"
#define WRITE_CHAR      "SUW,%X4,%X"
#define READ_CHAR       "SUR,%X4"    

#define REM_WR_CHAR     "WC,"
#define REM_WR_VAL      "WV,"
    
// Services and characteristics

// Battery service
#define BATTERY_SERVICE         0x180F
#define BATTERY_VALUE_ID        0x2A19

// Private service
#define VIRON_SERVICE           0x2000
#define VIRON_CHAR_CONN_ID      0x3000
#define VIRON_CHAR_READ_ID      0x3001
#define VIRON_CHAR_WRITE_ID     0x3002
    
#ifdef	__cplusplus
}
#endif /* __cplusplus */

#endif	/* BLUETOOTH_LE_H */

