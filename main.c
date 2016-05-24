#include "mcc_generated_files/mcc.h"
#include "i2c/i2c_helpers.h"
#include "ble/rn4020.h"

void main(void) {
    uint8_t i = 0;
    SensorStatus_t oldSensorState = DEFAULT_SENSORSTATUS;
//    uint8_t opBuffer[20] = {0};
//    uint8_t opLength = 0;
    uint8_t* command = NULL;
    uint16_t receivedHandle = 0;

    SYSTEM_Initialize();
    INTERRUPT_GlobalInterruptEnable();
    INTERRUPT_PeripheralInterruptEnable();
    IO_RA1_SetLow(); IO_RA0_SetHigh(); IO_RC5_SetLow(); IO_RB4_SetHigh();
    
    for (i = 0; i < 40; i++) { __delay_ms(50); }
    IO_RA0_SetLow();
    
    if (RN4020_Init()) {
        for (;;) {
            // Read I/O, read serialport     
            Debounce(!IO_RB1_GetValue(), &sensorState.plugged, &sensorState.debounceCount);
                        
            // Plug/deplug event
            if (sensorState.plugged != oldSensorState.plugged) {
                //opLength = 0;
               // opBuffer[opLength++] = sensorState.plugged;
               IO_RA0_SetHigh();__delay_ms(50);__delay_ms(50);__delay_ms(50);__delay_ms(50);IO_RA0_SetLow();
                
                // On plug, reset I2C and send address
                if (sensorState.plugged) {
                    I2C_Initialize(); __delay_ms(5);
                    sensorState.addr = I2C_FirstDevice();
                   // opBuffer[opLength++] = sensorState.addr;
                }
                
                RN4020_NotifyPlug();
                request.doWork = false;
                //RN4020_WriteCharacteristicBuffer(CONNECTION_HANDLE, opBuffer, opLength);
            }
            
            // Do requests
            if(request.doWork)
            {                
                if(request.data[0] == 0x01)
                {
                    if(I2C_ReadBytes(sensorState.addr, request.data + 2, request.data[1]))
                    {
                        RN4020_AnswerRequest();
                    }
                }
                else
                {
                    if(I2C_WriteBytes(sensorState.addr, request.data + 2, request.data[1]))
                    {
                        RN4020_AnswerRequest();
                    }
                }
            }

            // Read commands
            if (commandsCount > 0) {
                command = EUSART_GetCommand();

                // Handle request
                if (startsWith(command, RN4020_REMOTE_WR_VAL)) {
                    command = command + 3;
                    receivedHandle = ASCIIToHex16(command);

                    if (receivedHandle == REQUEST_HANDLE) {
                        command = command + 5;
                        request.length = 0;
                        //request.data[0] = ASCIIToHex8(command);
                        //receivedHandle = ASCIIToHex8(command);
                        
                        do {
                            request.data[request.length++] = ASCIIToHex8(command);
                            command = command + 2;
                        } while (*command != '.');

                        // Process command bytes
                        request.doWork = true;
                        
                    }
                }
            }

            oldSensorState = sensorState;
        }
    }
    else {
        IO_RA0_SetHigh();
        for (;;) {}
    }
}

