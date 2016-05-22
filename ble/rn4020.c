#include "rn4020.h"
#include <string.h>

void RN4020_WriteCharacteristicByte(uint16_t UUID, uint8_t value)
{
    RN4020_WriteCharacteristicBuffer(UUID, &value, 1);
}

void RN4020_WriteCharacteristicWord(uint16_t UUID, uint16_t value)
{
    uint8_t buffer[2];
    buffer[0] = LOW_BYTE(value);
    buffer[1] = HIGH_BYTE(value);
    
    RN4020_WriteCharacteristicBuffer(UUID, buffer, 2);
}

void RN4020_WriteCharacteristicBuffer(uint16_t UUID, uint8_t* buffer, uint8_t length)
{
    uint8_t i = 0;
    
    printf(RN4020_WRITE_CHAR, UUID);
    
    for(i = 0; i < length; i++)
        printf("%X2", buffer[i]);
    
    RN4020_EXECCMD();
}

void RN4020_ParseCommand()
{
    
}

bool RN4020_Init()
{
    uint8_t buffer[32];    
    printf("LS\r\n");
    
    // Check that both services (battery, vironmetre) exist
    if(!RN4020_ReadLine(buffer, 32) || strcmp(buffer, VIRON_SERVICE_ID))
        return false; 
    if(!RN4020_ReadLine(buffer, 32) || strcmp(buffer, "  3000,000E,V"))
        return false;
    if(!RN4020_ReadLine(buffer, 32) || strcmp(buffer, "  3000,000F,C"))
        return false;
    
    if(!RN4020_ReadLine(buffer, 32) || strcmp(buffer, BATTERY_SERVICE_ID))
        return false; 
    if(!RN4020_ReadLine(buffer, 32) || strcmp(buffer, "  2A19,0012,V"))
        return false;
    if(!RN4020_ReadLine(buffer, 32) || strcmp(buffer, "  2A19,0013,C"))
        return false;
    if(!RN4020_ReadLine(buffer, 32) || strcmp(buffer, RN4020_END))
        return false;
    
    return true;
}

void RN4020_ClearInput()
{
    while(EUSART_DataReady > 0)
        EUSART_Read();
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
