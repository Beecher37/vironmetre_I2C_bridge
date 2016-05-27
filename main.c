#include "mcc_generated_files/mcc.h"
#include "i2c/i2c_helpers.h"
#include "ble/rn4020.h"
#include "helpers/helpers.h"

//#define __DEBUG

void waitForRN4020Init()
{
    uint8_t i = 0;
    for(;i < 200; i++)
        __delay_ms(10);
}

void main(void) {
    SYSTEM_Initialize();
    INTERRUPT_GlobalInterruptEnable();
    INTERRUPT_PeripheralInterruptEnable();
    CONN_TEST_1_SetLow();
    EN_ALIM_SetLow();
    
    waitForRN4020Init();
    
#ifdef __DEBUG
    CONN_TEST_0_SetHigh();
#endif

    // On error, put an LED ON and block in this state
    if (!(RN4020_WakeModule() && RN4020_VerifyServices())) {
        CONN_TEST_0_SetHigh();
        for (;;) {}
    }
    
    RN4020_AdvertisePresence();
    BT_WAKE_SetLow();    
    CONN_TEST_0_SetLow();
        
    for (;;) {
        // Debounce bluetooth input state
        Debounce(BT_CONN_GetValue(), &bluetoothState.connected, &bluetoothState.debounceCount);
        
        if (bluetoothState.connected) {
            RN4020_WakeModule();
            Debounce(!SENS_DETECT_GetValue(), &sensorState.plugged, &sensorState.debounceCount);
            
            // Plug/deplug event
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
            
            RN4020_ManageRequest(); // Process existing requests
            RN4020_GetMessage(); // Read commands

            oldSensorState = sensorState;
        }
        else
        {
            if(bluetoothState.connected != oldBluetoothState.connected)
                RN4020_AdvertisePresence();
            
            BT_WAKE_SetLow();
        }
        
        oldBluetoothState = bluetoothState;
    }
}

