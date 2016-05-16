#include "mcc_generated_files/mcc.h"
#include "i2c/i2c_helpers.h"

#define INFO_I2C_PLUGGED 0x49

void main(void)
{
    SensorStatus_t oldSensorState;
    
    SYSTEM_Initialize();
    INTERRUPT_GlobalInterruptEnable();
    INTERRUPT_PeripheralInterruptEnable();

    SensorState.debounceCount = 0;
    oldSensorState.plugged = false;
    
    while (1)
    {        
        Debounce(!IO_RB1_GetValue(), &SensorState.plugged, &SensorState.debounceCount);
        
        if(SensorState.plugged != oldSensorState.plugged)
        {
            EUSART_Write(INFO_I2C_PLUGGED);
            EUSART_Write(SensorState.plugged);
            
            if(SensorState.plugged)
            {
                I2C_Initialize();
                EUSART_Write(I2C_FirstDevice());
            }
        }
        
        oldSensorState = SensorState;
    }
}
