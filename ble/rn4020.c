#include "rn4020.h"
#include "../mcc_generated_files/mcc.h"
#include "../i2c/i2c_helpers.h"
#include <string.h>

remote_req_t request;

void RN4020_NotifyPlug()
{
    printf(RN4020_WRITE_CHAR, CONNECTION_HANDLE);
    
    printf("%02X", sensorState.plugged);
    if(sensorState.plugged)
        printf("%02X", sensorState.addr);

    RN4020_EXECCMD();
}

void RN4020_AnswerRequest()
{
    uint8_t i = 0;
 
    request.doWork = false;
    printf(RN4020_WRITE_CHAR, ANSWER_HANDLE);
    
    printf("%02X", request.data[0]);
    printf("%02X", request.data[1]);
    
    if(request.data[0] == 1)
    {
        for(i = 0; i < request.data[1]; i++)
            printf("%02X", request.data[i+2]);
    }
    RN4020_EXECCMD();    
}

void RN4020_WriteCharacteristicByte(uint16_t UUID, uint8_t value) {
    RN4020_WriteCharacteristicBuffer(UUID, &value, 1);
}

void RN4020_WriteCharacteristicWord(uint16_t UUID, uint16_t value) {
    uint8_t buffer[2];
    buffer[0] = LOW_BYTE(value);
    buffer[1] = HIGH_BYTE(value);

    RN4020_WriteCharacteristicBuffer(UUID, buffer, 2);
}

void RN4020_WriteCharacteristicBuffer(uint16_t UUID, uint8_t* buffer, uint8_t length) {
    uint8_t i = 0;
    printf(RN4020_WRITE_CHAR, UUID);
    for (i = 0; i < length; i++)
        printf("%02X", buffer[i]);
    RN4020_EXECCMD();
}

bool RN4020_Init() {
    uint8_t i = 0;

    RN4020_ClearInput();
    RN4020_ListServices();

    i += (strcmp(EUSART_GetCommand(), VIRONMETRE_SERVICE_ID_STR) == 0);
        i += (strcmp(EUSART_GetCommand(), CONNECTION_VALUE_STR) == 0);
        i += (strcmp(EUSART_GetCommand(), CONNECTION_CHAR_STR) == 0);
        i += (strcmp(EUSART_GetCommand(), REQUEST_VALUE_STR) == 0);
        i += (strcmp(EUSART_GetCommand(), ANSWER_VALUE_STR) == 0);
        i += (strcmp(EUSART_GetCommand(), ANSWER_CHAR_STR) == 0);
    
    i += (strcmp(EUSART_GetCommand(), BATTERY_SERVICE_ID) == 0);
        i += (strcmp(EUSART_GetCommand(), BATTERY_VALUE_STR) == 0);
        i += (strcmp(EUSART_GetCommand(), BATTERY_CHAR_STR) == 0);
        
    i += (strcmp(EUSART_GetCommand(), RN4020_END) == 0);
    
    if (i >= 10)
        return true;

    return false;

    /*
    // Check that both services (battery, vironmetre) exist
    if (strcmp(EUSART_GetCommand(), VIRON_SERVICE_ID) == 0 &&
        strcmp(EUSART_GetCommand(), "  3000,000E,V") == 0 &&
        strcmp(EUSART_GetCommand(), "  3000,000F,C") == 0 &&
        strcmp(EUSART_GetCommand(), BATTERY_SERVICE_ID) == 0 &&
        strcmp(EUSART_GetCommand(), "  2A19,0012,V") == 0 &&
        strcmp(EUSART_GetCommand(), "  2A19,0013,C") == 0 &&
        strcmp(EUSART_GetCommand(), RN4020_END) == 0)
        return true; 
    else
    {
        RN4020_ClearInput();        
        return false;
    }
     */
}

void RN4020_ClearInput() {
    while (commandsCount > 0)
        EUSART_GetCommand();
}

bool startsWith(const char *str, const char *pre)
{
    return strncmp(pre, str, strlen(pre)) == 0;
}

uint16_t ASCIIToNibble(uint8_t nib)
{
    uint16_t n;

    n = nib - '0';
    if(n > 48)
        n -= 39;
    else if(n > 9)
        n -= 7;

    return n;
}

uint16_t ASCIIToHex16(uint8_t* hexStr)
{
    return ASCIIToNibble(*hexStr++) << 12 |
           ASCIIToNibble(*hexStr++) << 8 |
           ASCIIToNibble(*hexStr++) << 4 |
           ASCIIToNibble(*hexStr);
}

uint16_t ASCIIToHex8(uint8_t* hexStr)
{
    return (ASCIIToNibble(*hexStr++) << 4) | (ASCIIToNibble(*hexStr));
}

/*
void RN4020_ParseCommand()
{
    
}

uint8_t RN4020_ReadLine(uint8_t* buffer, uint8_t maxLength)
{
    uint8_t i = 0;
    
    // Clear buffer
    for(;i < maxLength; i++)
        buffer[i] = '\0';
    i = 0;
        
    // While EUSART isn't empty and still in max buffer size
    while(EUSART_DataReady > 0 && i < maxLength)
    {
        // Read chars
        buffer[i] = EUSART_Read();
        
        if(buffer[i] == '\n')
        {
            buffer[i] = '\0';
            break;
        }
        i++;
    }
    
    if(i > 1 && buffer[i-1] == '\r')
        buffer[i-1] = '\0';
    
    if(i > 0)
        i++;
    
    return i;
}
 */