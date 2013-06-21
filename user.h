/******************************************************************************/
/* User Level #define Macros                                                  */
/******************************************************************************/

#define LED_B7  PORTBbits.RB7

#define DELAY_LED   100
#define BAUDRATE    31
#define DATA_1      0x0F // 15 decimaal
#define DATA_2      0xF0 // 240 decimaal

char RF_ReceiveFlag = 0;

char LCDREGEL1[16]  = "Petra is mijn";
char LCDREGEL2[16]  = "lieve schatje";
char LCDREGEL3[16];
char LCDREGEL4[17]  = "XLCD lower nibbl";
char LCDREGEL5[17]  = "PORTA+C P18F2550";

char * test;

/******************************************************************************/
/* User Function Prototypes                                                   */
/******************************************************************************/

void InitApp(void);             /* I/O and Peripheral Initialization */
void InitSPI(void);
void InitInterrupts(void);

void LCD_Init(void);
void LCD_Write(void);
void LCD_WriteFirstLine(char OutFirstString[]);
void LCD_WriteSecondLine(char OutSecondString[]);

void DelayFor18TCY(void);
void DelayPORXLCD(void);
void DelayXLCD(void);

void ToggleLED_B7(void);

void Delay1TCY ( void );                    // Gives a delay of 1/5 us
void Delay10TCYx ( unsigned char unit );    // Gives a delay of 10 * ... * 1/5 = 50 us
void Delay100TCYx ( unsigned char unit );   // Gives a delay of 100 * ... * 1/5 = 1 ms
void Delay1KTCYx ( unsigned char unit );    // Gives a delay of 1000 * ... * 1/5 = 20 ms
void Delay10KTCYx ( unsigned char unit );   // Gives a delay of 10000 * 15 * 1/5 = 30 ms
