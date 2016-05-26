/**
  @Generated Pin Manager Header File

  @Company:
    Microchip Technology Inc.

  @File Name:
    pin_manager.h

  @Summary:
    This is the Pin Manager file generated using MPLAB(c) Code Configurator

  @Description:
    This header file provides implementations for pin APIs for all pins selected in the GUI.
    Generation Information :
        Product Revision  :  MPLAB(c) Code Configurator - 3.15.0
        Device            :  PIC18F25K20
        Version           :  1.01
    The generated drivers are tested against the following:
        Compiler          :  XC8 1.35
        MPLAB             :  MPLAB X 3.20

    Copyright (c) 2013 - 2015 released Microchip Technology Inc.  All rights reserved.

    Microchip licenses to you the right to use, modify, copy and distribute
    Software only when embedded on a Microchip microcontroller or digital signal
    controller that is integrated into your product or third party product
    (pursuant to the sublicense terms in the accompanying license agreement).

    You should refer to the license agreement accompanying this Software for
    additional information regarding your rights and obligations.

    SOFTWARE AND DOCUMENTATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND,
    EITHER EXPRESS OR IMPLIED, INCLUDING WITHOUT LIMITATION, ANY WARRANTY OF
    MERCHANTABILITY, TITLE, NON-INFRINGEMENT AND FITNESS FOR A PARTICULAR PURPOSE.
    IN NO EVENT SHALL MICROCHIP OR ITS LICENSORS BE LIABLE OR OBLIGATED UNDER
    CONTRACT, NEGLIGENCE, STRICT LIABILITY, CONTRIBUTION, BREACH OF WARRANTY, OR
    OTHER LEGAL EQUITABLE THEORY ANY DIRECT OR INDIRECT DAMAGES OR EXPENSES
    INCLUDING BUT NOT LIMITED TO ANY INCIDENTAL, SPECIAL, INDIRECT, PUNITIVE OR
    CONSEQUENTIAL DAMAGES, LOST PROFITS OR LOST DATA, COST OF PROCUREMENT OF
    SUBSTITUTE GOODS, TECHNOLOGY, SERVICES, OR ANY CLAIMS BY THIRD PARTIES
    (INCLUDING BUT NOT LIMITED TO ANY DEFENSE THEREOF), OR OTHER SIMILAR COSTS.

*/


#ifndef PIN_MANAGER_H
#define PIN_MANAGER_H

#define INPUT   1
#define OUTPUT  0

#define HIGH    1
#define LOW     0

#define ANALOG      1
#define DIGITAL     0

#define PULL_UP_ENABLED      1
#define PULL_UP_DISABLED     0

// get/set CONN_TEST_0 aliases
#define CONN_TEST_0_TRIS               TRISA0
#define CONN_TEST_0_LAT                LATA0
#define CONN_TEST_0_PORT               RA0
#define CONN_TEST_0_ANS                ANS0
#define CONN_TEST_0_SetHigh()    do { LATA0 = 1; } while(0)
#define CONN_TEST_0_SetLow()   do { LATA0 = 0; } while(0)
#define CONN_TEST_0_Toggle()   do { LATA0 = ~LATA0; } while(0)
#define CONN_TEST_0_GetValue()         PORTAbits.RA0
#define CONN_TEST_0_SetDigitalInput()    do { TRISA0 = 1; } while(0)
#define CONN_TEST_0_SetDigitalOutput()   do { TRISA0 = 0; } while(0)

#define CONN_TEST_0_SetAnalogMode()   do { ANS0 = 1; } while(0)
#define CONN_TEST_0_SetDigitalMode()   do { ANS0 = 0; } while(0)


// get/set CONN_TEST_1 aliases
#define CONN_TEST_1_TRIS               TRISA1
#define CONN_TEST_1_LAT                LATA1
#define CONN_TEST_1_PORT               RA1
#define CONN_TEST_1_ANS                ANS1
#define CONN_TEST_1_SetHigh()    do { LATA1 = 1; } while(0)
#define CONN_TEST_1_SetLow()   do { LATA1 = 0; } while(0)
#define CONN_TEST_1_Toggle()   do { LATA1 = ~LATA1; } while(0)
#define CONN_TEST_1_GetValue()         PORTAbits.RA1
#define CONN_TEST_1_SetDigitalInput()    do { TRISA1 = 1; } while(0)
#define CONN_TEST_1_SetDigitalOutput()   do { TRISA1 = 0; } while(0)

#define CONN_TEST_1_SetAnalogMode()   do { ANS1 = 1; } while(0)
#define CONN_TEST_1_SetDigitalMode()   do { ANS1 = 0; } while(0)


// get/set CONN_TEST_2 aliases
#define CONN_TEST_2_TRIS               TRISA2
#define CONN_TEST_2_LAT                LATA2
#define CONN_TEST_2_PORT               RA2
#define CONN_TEST_2_ANS                ANS2
#define CONN_TEST_2_SetHigh()    do { LATA2 = 1; } while(0)
#define CONN_TEST_2_SetLow()   do { LATA2 = 0; } while(0)
#define CONN_TEST_2_Toggle()   do { LATA2 = ~LATA2; } while(0)
#define CONN_TEST_2_GetValue()         PORTAbits.RA2
#define CONN_TEST_2_SetDigitalInput()    do { TRISA2 = 1; } while(0)
#define CONN_TEST_2_SetDigitalOutput()   do { TRISA2 = 0; } while(0)

#define CONN_TEST_2_SetAnalogMode()   do { ANS2 = 1; } while(0)
#define CONN_TEST_2_SetDigitalMode()   do { ANS2 = 0; } while(0)


// get/set CONN_TEST_3 aliases
#define CONN_TEST_3_TRIS               TRISA3
#define CONN_TEST_3_LAT                LATA3
#define CONN_TEST_3_PORT               RA3
#define CONN_TEST_3_ANS                ANS3
#define CONN_TEST_3_SetHigh()    do { LATA3 = 1; } while(0)
#define CONN_TEST_3_SetLow()   do { LATA3 = 0; } while(0)
#define CONN_TEST_3_Toggle()   do { LATA3 = ~LATA3; } while(0)
#define CONN_TEST_3_GetValue()         PORTAbits.RA3
#define CONN_TEST_3_SetDigitalInput()    do { TRISA3 = 1; } while(0)
#define CONN_TEST_3_SetDigitalOutput()   do { TRISA3 = 0; } while(0)

#define CONN_TEST_3_SetAnalogMode()   do { ANS3 = 1; } while(0)
#define CONN_TEST_3_SetDigitalMode()   do { ANS3 = 0; } while(0)


// get/set CONN_TEST_4 aliases
#define CONN_TEST_4_TRIS               TRISA4
#define CONN_TEST_4_LAT                LATA4
#define CONN_TEST_4_PORT               RA4
#define CONN_TEST_4_SetHigh()    do { LATA4 = 1; } while(0)
#define CONN_TEST_4_SetLow()   do { LATA4 = 0; } while(0)
#define CONN_TEST_4_Toggle()   do { LATA4 = ~LATA4; } while(0)
#define CONN_TEST_4_GetValue()         PORTAbits.RA4
#define CONN_TEST_4_SetDigitalInput()    do { TRISA4 = 1; } while(0)
#define CONN_TEST_4_SetDigitalOutput()   do { TRISA4 = 0; } while(0)



// get/set CONN_TEST_5 aliases
#define CONN_TEST_5_TRIS               TRISA5
#define CONN_TEST_5_LAT                LATA5
#define CONN_TEST_5_PORT               RA5
#define CONN_TEST_5_ANS                ANS4
#define CONN_TEST_5_SetHigh()    do { LATA5 = 1; } while(0)
#define CONN_TEST_5_SetLow()   do { LATA5 = 0; } while(0)
#define CONN_TEST_5_Toggle()   do { LATA5 = ~LATA5; } while(0)
#define CONN_TEST_5_GetValue()         PORTAbits.RA5
#define CONN_TEST_5_SetDigitalInput()    do { TRISA5 = 1; } while(0)
#define CONN_TEST_5_SetDigitalOutput()   do { TRISA5 = 0; } while(0)

#define CONN_TEST_5_SetAnalogMode()   do { ANS4 = 1; } while(0)
#define CONN_TEST_5_SetDigitalMode()   do { ANS4 = 0; } while(0)


// get/set BT_CONN aliases
#define BT_CONN_TRIS               TRISB0
#define BT_CONN_LAT                LATB0
#define BT_CONN_PORT               RB0
#define BT_CONN_WPU                WPUB0
#define BT_CONN_ANS                ANS12
#define BT_CONN_SetHigh()    do { LATB0 = 1; } while(0)
#define BT_CONN_SetLow()   do { LATB0 = 0; } while(0)
#define BT_CONN_Toggle()   do { LATB0 = ~LATB0; } while(0)
#define BT_CONN_GetValue()         PORTBbits.RB0
#define BT_CONN_SetDigitalInput()    do { TRISB0 = 1; } while(0)
#define BT_CONN_SetDigitalOutput()   do { TRISB0 = 0; } while(0)

#define BT_CONN_SetPullup()    do { WPUB0 = 1; } while(0)
#define BT_CONN_ResetPullup()   do { WPUB0 = 0; } while(0)
#define BT_CONN_SetAnalogMode()   do { ANS12 = 1; } while(0)
#define BT_CONN_SetDigitalMode()   do { ANS12 = 0; } while(0)


// get/set SENS_DETECT aliases
#define SENS_DETECT_TRIS               TRISB1
#define SENS_DETECT_LAT                LATB1
#define SENS_DETECT_PORT               RB1
#define SENS_DETECT_WPU                WPUB1
#define SENS_DETECT_ANS                ANS10
#define SENS_DETECT_SetHigh()    do { LATB1 = 1; } while(0)
#define SENS_DETECT_SetLow()   do { LATB1 = 0; } while(0)
#define SENS_DETECT_Toggle()   do { LATB1 = ~LATB1; } while(0)
#define SENS_DETECT_GetValue()         PORTBbits.RB1
#define SENS_DETECT_SetDigitalInput()    do { TRISB1 = 1; } while(0)
#define SENS_DETECT_SetDigitalOutput()   do { TRISB1 = 0; } while(0)

#define SENS_DETECT_SetPullup()    do { WPUB1 = 1; } while(0)
#define SENS_DETECT_ResetPullup()   do { WPUB1 = 0; } while(0)
#define SENS_DETECT_SetAnalogMode()   do { ANS10 = 1; } while(0)
#define SENS_DETECT_SetDigitalMode()   do { ANS10 = 0; } while(0)


// get/set EN_BT aliases
#define EN_BT_TRIS               TRISB2
#define EN_BT_LAT                LATB2
#define EN_BT_PORT               RB2
#define EN_BT_WPU                WPUB2
#define EN_BT_ANS                ANS8
#define EN_BT_SetHigh()    do { LATB2 = 1; } while(0)
#define EN_BT_SetLow()   do { LATB2 = 0; } while(0)
#define EN_BT_Toggle()   do { LATB2 = ~LATB2; } while(0)
#define EN_BT_GetValue()         PORTBbits.RB2
#define EN_BT_SetDigitalInput()    do { TRISB2 = 1; } while(0)
#define EN_BT_SetDigitalOutput()   do { TRISB2 = 0; } while(0)

#define EN_BT_SetPullup()    do { WPUB2 = 1; } while(0)
#define EN_BT_ResetPullup()   do { WPUB2 = 0; } while(0)
#define EN_BT_SetAnalogMode()   do { ANS8 = 1; } while(0)
#define EN_BT_SetDigitalMode()   do { ANS8 = 0; } while(0)


// get/set BT_CMD aliases
#define BT_CMD_TRIS               TRISB3
#define BT_CMD_LAT                LATB3
#define BT_CMD_PORT               RB3
#define BT_CMD_WPU                WPUB3
#define BT_CMD_ANS                ANS9
#define BT_CMD_SetHigh()    do { LATB3 = 1; } while(0)
#define BT_CMD_SetLow()   do { LATB3 = 0; } while(0)
#define BT_CMD_Toggle()   do { LATB3 = ~LATB3; } while(0)
#define BT_CMD_GetValue()         PORTBbits.RB3
#define BT_CMD_SetDigitalInput()    do { TRISB3 = 1; } while(0)
#define BT_CMD_SetDigitalOutput()   do { TRISB3 = 0; } while(0)

#define BT_CMD_SetPullup()    do { WPUB3 = 1; } while(0)
#define BT_CMD_ResetPullup()   do { WPUB3 = 0; } while(0)
#define BT_CMD_SetAnalogMode()   do { ANS9 = 1; } while(0)
#define BT_CMD_SetDigitalMode()   do { ANS9 = 0; } while(0)


// get/set BT_WAKE aliases
#define BT_WAKE_TRIS               TRISB4
#define BT_WAKE_LAT                LATB4
#define BT_WAKE_PORT               RB4
#define BT_WAKE_WPU                WPUB4
#define BT_WAKE_ANS                ANS11
#define BT_WAKE_SetHigh()    do { LATB4 = 1; } while(0)
#define BT_WAKE_SetLow()   do { LATB4 = 0; } while(0)
#define BT_WAKE_Toggle()   do { LATB4 = ~LATB4; } while(0)
#define BT_WAKE_GetValue()         PORTBbits.RB4
#define BT_WAKE_SetDigitalInput()    do { TRISB4 = 1; } while(0)
#define BT_WAKE_SetDigitalOutput()   do { TRISB4 = 0; } while(0)

#define BT_WAKE_SetPullup()    do { WPUB4 = 1; } while(0)
#define BT_WAKE_ResetPullup()   do { WPUB4 = 0; } while(0)
#define BT_WAKE_SetAnalogMode()   do { ANS11 = 1; } while(0)
#define BT_WAKE_SetDigitalMode()   do { ANS11 = 0; } while(0)


// get/set IO_RB5 aliases
#define IO_RB5_TRIS               TRISB5
#define IO_RB5_LAT                LATB5
#define IO_RB5_PORT               RB5
#define IO_RB5_WPU                WPUB5
#define IO_RB5_SetHigh()    do { LATB5 = 1; } while(0)
#define IO_RB5_SetLow()   do { LATB5 = 0; } while(0)
#define IO_RB5_Toggle()   do { LATB5 = ~LATB5; } while(0)
#define IO_RB5_GetValue()         PORTBbits.RB5
#define IO_RB5_SetDigitalInput()    do { TRISB5 = 1; } while(0)
#define IO_RB5_SetDigitalOutput()   do { TRISB5 = 0; } while(0)

#define IO_RB5_SetPullup()    do { WPUB5 = 1; } while(0)
#define IO_RB5_ResetPullup()   do { WPUB5 = 0; } while(0)


// get/set CONN_TEST_6 aliases
#define CONN_TEST_6_TRIS               TRISC0
#define CONN_TEST_6_LAT                LATC0
#define CONN_TEST_6_PORT               RC0
#define CONN_TEST_6_SetHigh()    do { LATC0 = 1; } while(0)
#define CONN_TEST_6_SetLow()   do { LATC0 = 0; } while(0)
#define CONN_TEST_6_Toggle()   do { LATC0 = ~LATC0; } while(0)
#define CONN_TEST_6_GetValue()         PORTCbits.RC0
#define CONN_TEST_6_SetDigitalInput()    do { TRISC0 = 1; } while(0)
#define CONN_TEST_6_SetDigitalOutput()   do { TRISC0 = 0; } while(0)



// get/set CONN_TEST_7 aliases
#define CONN_TEST_7_TRIS               TRISC1
#define CONN_TEST_7_LAT                LATC1
#define CONN_TEST_7_PORT               RC1
#define CONN_TEST_7_SetHigh()    do { LATC1 = 1; } while(0)
#define CONN_TEST_7_SetLow()   do { LATC1 = 0; } while(0)
#define CONN_TEST_7_Toggle()   do { LATC1 = ~LATC1; } while(0)
#define CONN_TEST_7_GetValue()         PORTCbits.RC1
#define CONN_TEST_7_SetDigitalInput()    do { TRISC1 = 1; } while(0)
#define CONN_TEST_7_SetDigitalOutput()   do { TRISC1 = 0; } while(0)



// get/set CONN_TEST_8 aliases
#define CONN_TEST_8_TRIS               TRISC2
#define CONN_TEST_8_LAT                LATC2
#define CONN_TEST_8_PORT               RC2
#define CONN_TEST_8_SetHigh()    do { LATC2 = 1; } while(0)
#define CONN_TEST_8_SetLow()   do { LATC2 = 0; } while(0)
#define CONN_TEST_8_Toggle()   do { LATC2 = ~LATC2; } while(0)
#define CONN_TEST_8_GetValue()         PORTCbits.RC2
#define CONN_TEST_8_SetDigitalInput()    do { TRISC2 = 1; } while(0)
#define CONN_TEST_8_SetDigitalOutput()   do { TRISC2 = 0; } while(0)



// get/set CONN_TEST_8 aliases
#define CONN_TEST_8_TRIS               TRISC2
#define CONN_TEST_8_LAT                LATC2
#define CONN_TEST_8_PORT               RC2
#define CONN_TEST_8_SetHigh()    do { LATC2 = 1; } while(0)
#define CONN_TEST_8_SetLow()   do { LATC2 = 0; } while(0)
#define CONN_TEST_8_Toggle()   do { LATC2 = ~LATC2; } while(0)
#define CONN_TEST_8_GetValue()         PORTCbits.RC2
#define CONN_TEST_8_SetDigitalInput()    do { TRISC2 = 1; } while(0)
#define CONN_TEST_8_SetDigitalOutput()   do { TRISC2 = 0; } while(0)



// get/set CONN_TEST_8 aliases
#define CONN_TEST_8_TRIS               TRISC2
#define CONN_TEST_8_LAT                LATC2
#define CONN_TEST_8_PORT               RC2
#define CONN_TEST_8_SetHigh()    do { LATC2 = 1; } while(0)
#define CONN_TEST_8_SetLow()   do { LATC2 = 0; } while(0)
#define CONN_TEST_8_Toggle()   do { LATC2 = ~LATC2; } while(0)
#define CONN_TEST_8_GetValue()         PORTCbits.RC2
#define CONN_TEST_8_SetDigitalInput()    do { TRISC2 = 1; } while(0)
#define CONN_TEST_8_SetDigitalOutput()   do { TRISC2 = 0; } while(0)



// get/set EN_ALIM aliases
#define EN_ALIM_TRIS               TRISC5
#define EN_ALIM_LAT                LATC5
#define EN_ALIM_PORT               RC5
#define EN_ALIM_SetHigh()    do { LATC5 = 1; } while(0)
#define EN_ALIM_SetLow()   do { LATC5 = 0; } while(0)
#define EN_ALIM_Toggle()   do { LATC5 = ~LATC5; } while(0)
#define EN_ALIM_GetValue()         PORTCbits.RC5
#define EN_ALIM_SetDigitalInput()    do { TRISC5 = 1; } while(0)
#define EN_ALIM_SetDigitalOutput()   do { TRISC5 = 0; } while(0)



// get/set EN_ALIM aliases
#define EN_ALIM_TRIS               TRISC5
#define EN_ALIM_LAT                LATC5
#define EN_ALIM_PORT               RC5
#define EN_ALIM_SetHigh()    do { LATC5 = 1; } while(0)
#define EN_ALIM_SetLow()   do { LATC5 = 0; } while(0)
#define EN_ALIM_Toggle()   do { LATC5 = ~LATC5; } while(0)
#define EN_ALIM_GetValue()         PORTCbits.RC5
#define EN_ALIM_SetDigitalInput()    do { TRISC5 = 1; } while(0)
#define EN_ALIM_SetDigitalOutput()   do { TRISC5 = 0; } while(0)



// get/set EN_ALIM aliases
#define EN_ALIM_TRIS               TRISC5
#define EN_ALIM_LAT                LATC5
#define EN_ALIM_PORT               RC5
#define EN_ALIM_SetHigh()    do { LATC5 = 1; } while(0)
#define EN_ALIM_SetLow()   do { LATC5 = 0; } while(0)
#define EN_ALIM_Toggle()   do { LATC5 = ~LATC5; } while(0)
#define EN_ALIM_GetValue()         PORTCbits.RC5
#define EN_ALIM_SetDigitalInput()    do { TRISC5 = 1; } while(0)
#define EN_ALIM_SetDigitalOutput()   do { TRISC5 = 0; } while(0)




/**
 * @Param
    none
 * @Returns
    none
 * @Description
    GPIO and peripheral I/O initialization
 * @Example
    PIN_MANAGER_Initialize();
 */
void PIN_MANAGER_Initialize (void);

/**
 * @Param
    none
 * @Returns
    none
 * @Description
    Interrupt on Change Handling routine
 * @Example
    PIN_MANAGER_IOC();
 */
void PIN_MANAGER_IOC(void);

#endif // PIN_MANAGER_H
/**
 End of File
*/