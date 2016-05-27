#include "mcc_generated_files/mcc.h"
#include "i2c/i2c_helpers.h"
#include "ble/rn4020.h"
#include "helpers/helpers.h"

//#define __DEBUG
//#define __ECHO

void waitForRN4020Init() {
    uint8_t i = 0;
    for (; i < 200; i++)
        __delay_ms(10);
}

void main(void) {
    uint8_t i = 0;
    SYSTEM_Initialize();
    INTERRUPT_GlobalInterruptEnable();
    INTERRUPT_PeripheralInterruptEnable();
    CONN_TEST_1_SetLow();
    CONN_TEST_0_SetLow();
    EN_ALIM_SetLow();

    waitForRN4020Init();

#ifdef __DEBUG
    CONN_TEST_0_SetHigh();
#endif

    // On init error, put an LED ON and block in this state
    if (!(RN4020_WakeModule() && RN4020_VerifyServices())) {
#ifdef __DEBUG    
        CONN_TEST_0_SetHigh();
#endif
        for (;;) {
        }
    }

    RN4020_AdvertisePresence();
    
    //SLEEP();
    
#ifdef __DEBUG    
    CONN_TEST_0_SetLow();
#endif
    for (;;) {
        // Debounce bluetooth input state
        Debounce(BT_CONN_GetValue(), &bluetoothState.connected, &bluetoothState.debounceCount);

        // Sub-state : connected
        if (bluetoothState.connected) {
            // Connected for the first iteration
            if (bluetoothState.connected != oldBluetoothState.connected) {
                remoteRequest.status = NO_REQUEST;
            }

            CONN_TEST_0_SetLow();

            Debounce(!SENS_DETECT_GetValue(), &sensorState.plugged, &sensorState.debounceCount);

            // <editor-fold defaultstate="collapsed" desc="Plug/deplug event">

            if (sensorState.plugged != oldSensorState.plugged) {
#ifdef __DEBUG
                CONN_TEST_0_SetHigh();
                __delay_ms(50);
                __delay_ms(50);
                __delay_ms(50);
                __delay_ms(50);
                CONN_TEST_0_SetLow();
#endif
                // On plug, reset I2C and send address
                if (sensorState.plugged) {
                    I2C_Initialize();
                    __delay_ms(5);
                    sensorState.addr = I2C_FirstDevice();
                }

                RN4020_NotifyPlug();
                remoteRequest.status = NO_REQUEST;
            }

#ifdef __ECHO

            if (remoteRequest.status == REQUEST_NOT_PROCESSED) {
                if (RN4020_WakeModule()) {
                    printf(RN4020_WRITE_CHAR, ANSWER_HANDLE);
                    
                    for(i=0;i<remoteRequest.length;i++)
                        printf("%02X", remoteRequest.data[i]);
                    
                    RN4020_EXECCMD();
                    if(!RN4020_WaitFor(RN4020_AOK)) {
                        
                    }
                }
    
                RN4020_SleepModule();
                remoteRequest.status = NO_REQUEST;
            }
#else
            RN4020_ManageRequest(); // Process existing requests
#endif
            RN4020_GetMessage(); // Read commands and create request

            oldSensorState = sensorState;
        }
        else {
            // Not connected for the first iteration
            if (bluetoothState.connected != oldBluetoothState.connected) {
                RN4020_AdvertisePresence();
                //SLEEP();
            }
        }

        oldBluetoothState = bluetoothState;
    }
}

