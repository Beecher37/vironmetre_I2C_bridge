/* 
 * File: rn4020.h
 * Author: Thomas Prioul
 * Comments: constants and helpers functions to interface with RN4020 module
 * Revision history: 
 */

#ifndef RN4020_H
#define	RN4020_H

#include <xc.h>
#include <stdint.h>
#include <stdbool.h>

#ifdef	__cplusplus
extern "C" {
#endif /* __cplusplus */

    ////////////////////////////////////////////////////////////////////////////////
    // Common RN4020 commands and strings  
    ////////////////////////////////////////////////////////////////////////////////
#define RN4020_NEWLINE                  "\r\n"
#define RN4020_CMD                      "CMD"
#define RN4020_END                      "END"
#define RN4020_AOK                      "AOK"
#define RN4020_CONN_START               "Connected"
#define RN4020_CONN_END                 "Connection End"
#define RN4020_CONN_PARAM               "ConnParam:"    

    ////////////////////////////////////////////////////////////////////////////////
    // Services and characteristics
    ////////////////////////////////////////////////////////////////////////////////

#define RN4020_WRITE_CHAR               "SHW,%04X,"
#define RN4020_READ_CHAR                "SHR,%04X"
#define RN4020_REMOTE_SUSCRIBE          "WC"
#define RN4020_REMOTE_VALUE_CHANGE      "WV"     

    // Battery service
#define BATTERY_SERVICE_ID              "180F"
#define BATTERY_VALUE_ID                "2A19"

#define BATTERY_VALUE_STR               "2A19,0017,V"
#define BATTERY_CHAR_STR                "2A19,0018,C"

    // Private service
#define VIRONMETRE_SERVICE_ID_STR       "2000"
#define CONNECTION_ID_STR               "3000"
#define CONNECTION_ID                   0x3000
#define CONNECTION_HANDLE               0x000E
#define CONNECTION_VALUE_STR            "3000,000E,V"    
#define CONNECTION_CHAR_STR             "3000,000F,C" 

#define REQUEST_ID_STR                  "3001"
#define REQUEST_ID                      0x3001
#define REQUEST_VALUE_STR               "3001,0011,V"    
#define REQUEST_HANDLE                  0x0011

#define ANSWER_ID_STR                   "3002"
#define ANSWER_ID                       0x3002    
#define ANSWER_VALUE_STR                "3002,0013,V"    
#define ANSWER_CHAR_STR                 "3002,0014,C" 
#define ANSWER_HANDLE                   0x0013       

typedef struct {
    bool connected;
    uint16_t debounceCount;
} RN4020status_t;

typedef enum {
    NO_REQUEST,
    REQUEST_NOT_PROCESSED,
    REQUEST_WORKING,
    REQUEST_DONE,
    REQUEST_FAIL
} REMOTE_REQUEST_STATUS;

typedef struct {
    REMOTE_REQUEST_STATUS status;
    uint8_t length;
    uint8_t data[20];
} remote_i2c_request_t;

extern RN4020status_t bluetoothState;
extern RN4020status_t oldBluetoothState;
extern remote_i2c_request_t remoteRequest;

#define REQUEST_READ                    0x01
#define REQUEST_WRITE                   0x00

#define RN4020_ListServices()           puts("LS\r\n")
#define RN4020_EXECCMD()                puts(RN4020_NEWLINE)

bool RN4020_WaitFor(const uint8_t* msg);
bool RN4020_WakeModule();
bool RN4020_VerifyServices();
bool RN4020_AdvertisePresence();

void RN4020_ManageRequest();
void RN4020_NotifyPlug();
void RN4020_GetMessage();
void RN4020_ClearInput();

#ifdef	__cplusplus
}
#endif /* __cplusplus */

#endif

