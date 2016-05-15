#include "mcc_generated_files/mcc.h"

void main(void)
{
    uint8_t i = 0;
 
    SYSTEM_Initialize();
    INTERRUPT_GlobalInterruptEnable();
    INTERRUPT_PeripheralInterruptEnable();

    while (1)
    {
        // Add your application code
        if(i++ == 0)
            IO_RA0_Toggle();
        
        __delay_ms(1);
    }
}
