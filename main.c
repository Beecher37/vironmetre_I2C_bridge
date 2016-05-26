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
    CONN_TEST_1_SetLow();
    CONN_TEST_0_SetHigh();
    EN_ALIM_SetLow();
    BT_WAKE_SetHigh();

    for (i = 0; i < 60; i++) {
        __delay_ms(50);
    }

    if (RN4020_Init()) {
        CONN_TEST_0_SetLow();
        BT_WAKE_SetLow();

        for (;;) {
            if (BT_CONN_GetValue()) {
                if (!BT_WAKE_GetValue()) {
                    BT_WAKE_SetHigh();
                    __delay_ms(50);
                }

                // Read I/O, read serialport     
                Debounce(!SENS_DETECT_GetValue(), &sensorState.plugged, &sensorState.debounceCount);
                
                // Plug/deplug event
                if (sensorState.plugged != oldSensorState.plugged) {
                    //opLength = 0;
                    // opBuffer[opLength++] = sensorState.plugged;
                    CONN_TEST_0_SetHigh();
                    __delay_ms(50);
                    __delay_ms(50);
                    __delay_ms(50);
                    __delay_ms(50);
                    CONN_TEST_0_SetLow();

                    // On plug, reset I2C and send address
                    if (sensorState.plugged) {
                        I2C_Initialize();
                        __delay_ms(5);
                        sensorState.addr = I2C_FirstDevice();
                    }

                    RN4020_NotifyPlug();
                    request.doWork = false;
                }

                // Do requests
                if (request.doWork) {
                    if (request.data[0] == 0x01) {
                        if (I2C_ReadBytes(sensorState.addr, request.data + 2, request.data[1])) {
                            RN4020_AnswerRequest();
                        }
                    }
                    else {
                        if (I2C_WriteBytes(sensorState.addr, request.data + 2, request.data[1])) {
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
                            
                            do {
                                request.data[request.length++] = ASCIIToHex8(command);
                                command = command + 2;
                            }
                            while (*command != '.');

                            // Process command bytes
                            request.doWork = true;

                        }
                    }
                }
                
                oldSensorState = sensorState;
            }
            else
                BT_WAKE_SetLow();
        }
    }
    else {
        CONN_TEST_0_SetHigh();
        for (;;) {
        }
    }
}

