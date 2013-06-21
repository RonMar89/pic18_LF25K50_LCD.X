/******************************************************************************/
/* Files to Include                                                           */
/******************************************************************************/

#include <htc.h>           /* Global Header File */
#include <stdint.h>        /* For uint8_t definition */
#include <stdbool.h>       /* For true/false definition */
#include <plib.h>

#include "system.h"        /* System funct/params, like osc/peripheral config */
#include "user.h"          /* User funct/params, such as InitApp */
#include "delays.h"        /* Delay Functions from XC8 compiler */
#include "NRF24L01P.h"

/******************************************************************************/
/* User Global Variable Declaration                                           */
/******************************************************************************/

/* i.e. uint8_t <variable_name>; */


/******************************************************************************/
/* Main Program                                                               */
/******************************************************************************/

void main(void)
{
    /* Configure the oscillator for the device */
    ConfigureOscillator();

    /* Initialize I/O and Peripherals for application */
    InitApp();
    InitSPI();
    InitInterrupts();

    LCD_Init();

    RF_ConfigReceiver();
    LCD_WriteFirstLine("NRF Initialized");
//    LCD_Write();

    
    while(1)
    {
        if(RF_ReceiveFlag == 1){
            RF_ResetReceiver();
            if(RF_ReceiveBuffer[0] == 0x01){
                ToggleLED_B7();
                LCD_WriteFirstLine("Receive Action:");
                LCD_WriteSecondLine("L-Button Pressed");
            }

            else if(RF_ReceiveBuffer[0] == 0x02){
                ToggleLED_B7();
                LCD_WriteFirstLine("Receive Action:");
                LCD_WriteSecondLine("R-Button Pressed");
            }
        }
    }
}

