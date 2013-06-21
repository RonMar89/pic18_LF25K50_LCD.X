/******************************************************************************/
/* Files to Include                                                           */
/******************************************************************************/

#include <htc.h>            /* HiTech General Includes */
#include <stdint.h>         /* For uint8_t definition */
#include <stdbool.h>        /* For true/false definition */
#include <string.h>
#include "plib.h"

#include "user.h"
#include "NRF24L01P.h"
#include "system.h"


/******************************************************************************/
/* User Functions                                                             */
/******************************************************************************/

/* <Initialize variables in user.h and insert code for user algorithms.> */

void InitApp(void){

    /* Setup analog functionality and port direction */
//    ANSELA = 0;             // Analog OFF
    ADCON0bits.CHS = 4;     // Analog channel AN4
    ADCON1bits.PCFG = 0xF;  // All Digital IO's
//    ADCON1bits.TRIGSEL 1;   // Special Trigger from CTMU
    
    PORTA = 0;              // Reset PORTA
    TRISA = 0;              // All Outputs

//    ANSELB = 0;             // Analog OFF
    PORTB = 0;              // Reset PORTB
    TRISB = 0;              // All Outputs

//    ANSELC = 0;             // Analog OFF
    PORTC = 0;              // Reset PORTC
    TRISC = 0;              // All Outputs

    TRIS_CSN = 0;
    CSN     = 1;

    TRIS_IRQ = 1;    // IRQ - RF Module PORTB RB2/INT2
    
}

void InitSPI(void){
    OpenSPI(SPI_FOSC_64, MODE_00, SMPMID);
}

void InitInterrupts(void){

    IPEN = 1;       // Interrupt Priority High

    INTEDG2 = 0;    // Falling Edge
    INT2IP  = 0;    // INT2 Priority Low
    INT2IE  = 1;    // INT2 Enabled

    GIE = 1;        // Global Interrupt Enable
}

void LCD_Init(void){    // LCD instellingen
    OpenXLCD(DON);

    OpenXLCD(FOUR_BIT&LINES_5X7); // 8 bits datalijn, meerdere regels

    while (BusyXLCD());
    WriteCmdXLCD(SHIFT_DISP_LEFT); // cursor instelling

    while (BusyXLCD());
    WriteCmdXLCD(CURSOR_ON&BLINK_OFF);	//cursor uit, knipperen uit

}

void LCD_Write(void){
    while (BusyXLCD());
    SetDDRamAddr(0x00);
    while (BusyXLCD());
    putsXLCD(LCDREGEL4);

    Delay10KTCYx(250); // 500 mSec
    Delay10KTCYx(250); // 500 mSec

    while (BusyXLCD());
    SetDDRamAddr(0x40);
    while (BusyXLCD());
    putsXLCD(LCDREGEL5);

    while (BusyXLCD());
    WriteCmdXLCD(CURSOR_OFF&BLINK_OFF);	//cursor uit, knipperen uit
    
}

void LCD_WriteFirstLine(char OutFirstString[]){
    while (BusyXLCD());
    SetDDRamAddr(0x00);
    while (BusyXLCD());
    putsXLCD(OutFirstString);

    while (BusyXLCD());
    WriteCmdXLCD(CURSOR_OFF&BLINK_OFF);	//cursor uit, knipperen uit
}

void LCD_WriteSecondLine(char OutSecondString[]){
    while (BusyXLCD());
    SetDDRamAddr(0x40);
    while (BusyXLCD());
    putsXLCD(OutSecondString);

    while (BusyXLCD());
    WriteCmdXLCD(CURSOR_OFF&BLINK_OFF);	//cursor uit, knipperen uit
}

void DelayFor18TCY(void){
    for(int i = 0; i < 100; i++){
    __delay_us(1);
    }
}
void DelayPORXLCD(void){
	Delay1KTCYx(80);  // 16 mSec
	return;
}
void DelayXLCD(void){
	Delay1KTCYx(25); // 5 mSec
	return;
}

void ToggleLED_B7(void){
    LED_B7 = ~LED_B7;
}