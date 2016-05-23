#include "mcc_generated_files/mcc.h"
#include "i2c/i2c_helpers.h"
#include "ble/rn4020.h"

void main(void) {
    uint8_t i = 0;
    SensorStatus_t oldSensorState = DEFAULT_SENSORSTATUS;
    uint8_t opBuffer[20] = {0};
    uint8_t opLength = 0;
    uint8_t* command = NULL;
    uint16_t receivedHandle = 0;

    SYSTEM_Initialize();
    INTERRUPT_GlobalInterruptEnable();
    INTERRUPT_PeripheralInterruptEnable();

    IO_RA1_SetLow();
    IO_RA0_SetHigh();
    IO_RC5_SetLow();

    // CMD mode
    //IO_RB4_SetHigh();
    for (i = 0; i < 40; i++)
        __delay_ms(50);
    IO_RA0_SetLow();

    if (RN4020_Init()) {
        for (;;) {
            
            IO_RB4_LAT = IO_RB0_GetValue();
            
            // Read I/O, read serialport     
            Debounce(!IO_RB1_GetValue(), &sensorState.plugged, &sensorState.debounceCount);

            // Plug/deplug event
            if (sensorState.plugged != oldSensorState.plugged) {
                opLength = 1;

                // On plug, reset I2C and send address
                if (sensorState.plugged) {
                    I2C_Initialize();
                    __delay_ms(5);
                    opBuffer[opLength++] = I2C_FirstDevice();
                }

                RN4020_WriteCharacteristicBuffer(CONNECTION_ID, opBuffer, opLength);
            }


            if (commandsCount > 0) {
                command = EUSART_GetCommand();

                // Handle request
                if (startsWith(command, RN4020_REMOTE_WR_VAL)) {
                    command = command + 3;
                    receivedHandle = ASCIIToHex16(command);

                    if (receivedHandle == REQUEST_HANDLE) {
                        command = command + 5;
                        opLength = 0;
                        do {
                            opBuffer[opLength++] = ASCIIToHex8(command);
                            command = command + 2;
                        } while (*command != '.');

                        // Process command bytes
                    }
                }
            }

            oldSensorState = sensorState;
        }
    }
    else {
        IO_RA0_SetHigh();
        for (;;) {
        }
    }
}

