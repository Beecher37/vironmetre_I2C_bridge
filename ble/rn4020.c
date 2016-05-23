#include "rn4020.h"
#include "../mcc_generated_files/mcc.h"
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

bool RN4020_Init()
{        
    RN4020_ClearInput(); 
    printf("LS\r\n");
    __delay_ms(5);
        
    uint8_t* buffer = EUSART_GetCommand();
    
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
}

void RN4020_ClearInput()
{
    while(commandsCount > 0)
        EUSART_GetCommand();
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