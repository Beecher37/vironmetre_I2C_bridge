#include "mcc_generated_files/mcc.h"
#include "i2c/i2c_helpers.h"

#define INFO_I2C_PLUGGED    0x49
#define CMD_READ            0x52 // 'R'
#define CMD_WRITE           0x57 // 'W'


void main(void)
{
    uint8_t addr = 0;
    uint8_t i = 0;
    uint8_t length = 0;
    uint8_t buffer[3];
    SensorStatus_t oldSensorState;
    
    SYSTEM_Initialize();
    INTERRUPT_GlobalInterruptEnable();
    INTERRUPT_PeripheralInterruptEnable();

    sensorState.debounceCount = 0;
    oldSensorState.plugged = false;
    
    IO_RA0_SetLow();
    
    for(i = 0; i < 10; i++)
    {
        IO_RA0_Toggle();
        __delay_ms(50);
    }
    
    while (1)
    {        
        Debounce(!IO_RB1_GetValue(), &sensorState.plugged, &sensorState.debounceCount);
        
        // Plug/deplug event
        if(sensorState.plugged != oldSensorState.plugged)
        {
            EUSART_Write(INFO_I2C_PLUGGED);
            EUSART_Write(sensorState.plugged);
            
            // On plug, reset I2C and send address
            if(sensorState.plugged)
            {
                I2C_Initialize();
                EUSART_Write(I2C_FirstDevice());
            }
        }
        
        // Get messages
        if(sensorState.plugged)
        {
            // Full message received
            if(EUSART_DataReady >= 3)
            {
                IO_RA0_SetHigh();
                switch(EUSART_Read())
                {
                    case CMD_READ:
                        addr = EUSART_Read();
                        length = EUSART_Read();
                        
                        if(length > 0)
                        {
                            if(I2C_ReadBytes(addr, buffer, length))
                            {
                                EUSART_Write(CMD_READ);
                                EUSART_Write(length);

                                for(i = 0; i < length; i++)
                                    EUSART_Write(buffer[i]);
                            }
                        }
                        break;
                        
                    case CMD_WRITE:
                        addr = EUSART_Read();
                        length = EUSART_Read();
                                                
                        if(length > 0)
                        {
                            for(i = 0; i < length; i++)
                                buffer[i] = EUSART_Read();
                            
                            EUSART_Write(CMD_WRITE);
                            if(I2C_WriteBytes(addr, buffer, length))
                            {
                                EUSART_Write(length);
                            }
                            else
                                EUSART_Write(0);
                        }
                        break;
                    
                    default:
                        while(EUSART_DataReady)
                            EUSART_Read();
                        break;
                                
                }
                
                IO_RA0_SetLow();
            }
        }
        
        oldSensorState = sensorState;
    }
}
