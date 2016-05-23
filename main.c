#include "mcc_generated_files/mcc.h"
#include "i2c/i2c_helpers.h"
#include "ble/rn4020.h"

void main(void) {
    uint8_t i = 0;
   // uint8_t* buffer = NULL;
    
    SYSTEM_Initialize();
    INTERRUPT_GlobalInterruptEnable();
    INTERRUPT_PeripheralInterruptEnable();

    IO_RA1_SetLow();
    IO_RA0_SetHigh();
    IO_RC5_SetLow();
    
    // CMD mode
    IO_RB4_SetHigh();
    for (i = 0; i < 40; i++)
        __delay_ms(50);
    IO_RA0_SetLow();
    
    IO_RA0_LAT = RN4020_Init();
    
    for (;;) {
        //for(i=0;i<100;i++)
        //    __delay_ms(10);      
        
        //if (commandsCount > 0) {
        //    buffer = EUSART_GetCommand();
        //    printf("%s", buffer);
        //}

        /*
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
        */
    }
}

