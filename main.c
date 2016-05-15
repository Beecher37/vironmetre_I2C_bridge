#include "mcc_generated_files/mcc.h"
#include "i2c/i2c_helpers.h"

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
            EUSART_Write(I2C_FirstDevice());
        
        __delay_ms(1);
    }
}
