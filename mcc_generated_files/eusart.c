/**
  EUSART Generated Driver File

  @Company
    Microchip Technology Inc.

  @File Name
    eusart.c

  @Summary
    This is the generated driver implementation file for the EUSART driver using MPLAB(c) Code Configurator

  @Description
    This header file provides implementations for driver APIs for EUSART.
    Generation Information :
        Product Revision  :  MPLAB(c) Code Configurator - v3.00
        Device            :  PIC18F25K20
        Driver Version    :  2.00
    The generated drivers are tested against the following:
        Compiler          :  XC8 1.35
        MPLAB             :  MPLAB X 3.20
*/

/*
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

/**
  Section: Included Files
*/
#include "eusart.h"
#include "pin_manager.h"

/**
  Section: Macro Declarations
*/
#define EUSART_TX_BUFFER_SIZE 32
//#define EUSART_RX_BUFFER_SIZE 32

/**
  Section: Global Variables
*/

static uint8_t eusartTxHead = 0;
static uint8_t eusartTxTail = 0;
static uint8_t eusartTxBuffer[EUSART_TX_BUFFER_SIZE];
volatile uint8_t eusartTxBufferRemaining;

//static uint8_t eusartRxHead = 0;
//static uint8_t eusartRxTail = 0;
//static uint8_t eusartRxBuffer[EUSART_RX_BUFFER_SIZE];
//volatile uint8_t eusartRxCount;

#define NB_COMMANDS             8
#define COMMAND_MAX_SIZE        32

static uint8_t commandsBufferHead = 0;
static uint8_t commandsBufferTail = 0;
static uint8_t commandsReceived[NB_COMMANDS][COMMAND_MAX_SIZE];
static uint8_t commandPointer;
volatile uint8_t commandsCount;

/**
  Section: EUSART APIs
*/

void EUSART_Initialize(void)
{
    // disable interrupts before changing states
    PIE1bits.RCIE = 0;
    PIE1bits.TXIE = 0;

    // Set the EUSART module to the options selected in the user interface.

    // ABDOVF no_overflow; CKTXP async_noninverted_sync_fallingedge; BRG16 16bit_generator; WUE disabled; ABDEN disabled; DTRXP not_inverted; 
    BAUDCON = 0x08;

    // SPEN enabled; RX9 8-bit; CREN enabled; ADDEN disabled; SREN disabled; 
    RCSTA = 0x90;

    // TX9 8-bit; TX9D 0; SENDB sync_break_complete; TXEN enabled; SYNC asynchronous; BRGH hi_speed; CSRC slave_mode; 
    TXSTA = 0x24;

    // Baud Rate = 115200; 
    SPBRG = 0x0F;

    // Baud Rate = 115200; 
    SPBRGH = 0x00;


    // initializing the driver state
    eusartTxHead = 0;
    eusartTxTail = 0;
    eusartTxBufferRemaining = sizeof(eusartTxBuffer);

    //eusartRxHead = 0;
    //eusartRxTail = 0;
    //eusartRxCount = 0;
    commandsBufferHead = 0;
    commandsBufferTail = 0;
    commandsCount = 0;
    commandPointer = 0;

    // enable receive interrupt
    PIE1bits.RCIE = 1;
}

/*
uint8_t EUSART_Read(void)
{
    uint8_t readValue  = 0;

    while(0 == eusartRxCount)
    {
    }

    PIE1bits.RCIE = 0;

    readValue = eusartRxBuffer[eusartRxTail++];
    if(sizeof(eusartRxBuffer) <= eusartRxTail)
    {
        eusartRxTail = 0;
    }
    eusartRxCount--;
    PIE1bits.RCIE = 1;

    return readValue;
}
*/

void EUSART_Write(uint8_t txData)
{
    while(0 == eusartTxBufferRemaining)
    {
    }

    if(0 == PIE1bits.TXIE)
    {
        TXREG = txData;
    }
    else
    {
        PIE1bits.TXIE = 0;
        eusartTxBuffer[eusartTxHead++] = txData;
        if(sizeof(eusartTxBuffer) <= eusartTxHead)
        {
            eusartTxHead = 0;
        }
        eusartTxBufferRemaining--;
    }
    PIE1bits.TXIE = 1;
}

char getch(void)
{
    return 0;
//    return EUSART_Read();
}

void putch(char txData)
{
    EUSART_Write(txData);
}

void EUSART_Transmit_ISR(void)
{
    // add your EUSART interrupt custom code
    if(sizeof(eusartTxBuffer) > eusartTxBufferRemaining)
    {
        TXREG = eusartTxBuffer[eusartTxTail++];
        if(sizeof(eusartTxBuffer) <= eusartTxTail)
        {
            eusartTxTail = 0;
        }
        eusartTxBufferRemaining++;
    }
    else
    {
        PIE1bits.TXIE = 0;
    }
}

void EUSART_Receive_ISR(void)
{    
    if(1 == RCSTAbits.OERR)
    {
        // EUSART error - restart
        RCSTAbits.CREN = 0;
        RCSTAbits.CREN = 1;
    }
    
    // buffer overruns are ignored
        
    // ignore '\r' character
    if(RCREG == '\r')
        return;
    
    // on newline, move buffer pointer
    if (RCREG == '\n')
    {     
        if(++commandsBufferHead >= NB_COMMANDS)
            commandsBufferHead = 0;
        
        commandsReceived[commandsBufferHead][commandPointer] = '\0';
        
        commandsCount++;
        commandPointer = 0;
    }
    else
    {
        // If pointer OOB, move it back to 0 and change command slot
        if(commandPointer >= COMMAND_MAX_SIZE)
        {
            commandsReceived[commandsBufferHead][commandPointer] = '\0';
            if(++commandsBufferHead >= NB_COMMANDS)
                commandsBufferHead = 0;
            
            commandsCount++;
            commandPointer = 0;
        }  
        
        // Copy char to buffer 
        commandsReceived[commandsBufferHead][commandPointer++] = RCREG;
    }
}

uint8_t* EUSART_GetCommand()
{
   // uint8_t* buffer = commandsReceived[commandsBufferTail++];
    uint8_t* buf = commandsReceived[commandsBufferTail];
    
    if(++commandsBufferTail >= NB_COMMANDS)
        commandsBufferTail = 0;
    PIE1bits.RCIE = 0;
    commandsCount--;
    PIE1bits.RCIE = 1;
    return buf;
}
/**
  End of File
*/
