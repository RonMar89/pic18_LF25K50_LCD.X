/*
 * File:   NRF24L01P.h
 * Author: Ron Markink
 *
 * Created on 12 december 2012
 */

/* Define the port where the control lines are connected.
 * These are just samples, change to match your application.
 */
#define CSN         PORTBbits.RB4
#define TRIS_CSN    TRISBbits.TRISB4

#define CE          PORTBbits.RB5
#define TRIS_CE     TRISBbits.TRISB5

#define IRQ         PORTBbits.RB2
#define TRIS_IRQ    TRISBbits.TRISB2


// SPI commands ( NRF24L01P ) See Datasheet NRF24L01P
#define READ_REG        0x00  // Define read command to register
#define WRITE_REG       0x20  // Define write command to register
#define R_RX_PAYLOAD    0x61  // Define RX payload register address
#define W_TX_PAYLOAD    0xA0  // Define TX payload register address
#define FLUSH_TX        0xE1  // Define flush TX register command
#define FLUSH_RX        0xE2  // Define flush RX register command
#define REUSE_TX_PL     0xE3  // Define reuse TX payload register command


// SPI register addresses ( NRF24L01P ) See Datasheet NRF24L01P
#define CONFIG          0x00  // 'Config' register address
#define EN_AA           0x01  // 'Enable Auto Acknowledgment' register address
#define EN_RXADDR       0x02  // 'Enabled RX addresses' register address
#define SETUP_AW        0x03  // 'Setup address width' register address
#define SETUP_RETR      0x04  // 'Setup Auto. Retrans' register address
#define RF_CH           0x05  // 'RF channel' register address
#define RF_SETUP        0x06  // 'RF setup' register address
#define STATUS          0x07  // 'Status' register address
#define OBSERVE_TX      0x08  // 'Observe TX' register address
#define RPD             0x09  // 'Carrier Detect' register address
#define RX_ADDR_P0      0x0A  // 'RX address pipe0' register address
#define RX_ADDR_P1      0x0B  // 'RX address pipe1' register address
#define RX_ADDR_P2      0x0C  // 'RX address pipe2' register address
#define RX_ADDR_P3      0x0D  // 'RX address pipe3' register address
#define RX_ADDR_P4      0x0E  // 'RX address pipe4' register address
#define RX_ADDR_P5      0x0F  // 'RX address pipe5' register address
#define TX_ADDR         0x10  // 'TX address' register address
#define RX_PW_P0        0x11  // 'RX payload width, pipe0' register address
#define RX_PW_P1        0x12  // 'RX payload width, pipe1' register address
#define RX_PW_P2        0x13  // 'RX payload width, pipe2' register address
#define RX_PW_P3        0x14  // 'RX payload width, pipe3' register address
#define RX_PW_P4        0x15  // 'RX payload width, pipe4' register address
#define RX_PW_P5        0x16  // 'RX payload width, pipe5' register address
#define FIFO_STATUS     0x17  // 'FIFO Status Register' register address


#define NRF24L01_TX_PAYLOAD_WIDTH 8    // TX payload Width
#define NRF24L01_PAYLOAD_WIDTH  8      // RX Payload Width
#define NRF24L01_ADDR_WIDTH     0x03    // 5 bytes width


/******************************************************************************/
/* NRF24L01P Global Variable Declaration                                      */
/******************************************************************************/
unsigned char NRF24L01_TX_ADDR_BUFFER[5] = {0xE7,0xE7,0xE7,0xE7,0xE7};
unsigned char NRF24L01_RX_ADDR_BUFFER[5] = {0xA2,0xB2,0xC2,0xD2,0xE2};
unsigned char RF_TransmitBuffer[NRF24L01_TX_PAYLOAD_WIDTH]
= {  0x01,0x35,0x36,0x37,0x38,0x39,0x3A,0x3B };
//                                                        0x3C,0x3D,0x3E,0x3F,0x40,0x41,0x42,0x43,
//                                                        0x44,0x45,0x46,0x47,0x48,0x49,0x4A,0x4B,
//                                                        0x4C,0x4D,0x4E,0x4F,0x50,0x51,0x52,0x53 };
unsigned char RF_ReceiveBuffer[NRF24L01_PAYLOAD_WIDTH];
unsigned char STATUS_Data;
unsigned char FIFO_STATUS_Data;

/******************************************************************************/
/* NRF24L01P Function Prototypes                                              */
/******************************************************************************/
void RF_ConfigTransmitter(void);
void RF_ConfigReceiver(void);
void RF_TransmitData(void);
void RF_ResetReceiver(void);
unsigned char SPI_Transceive(unsigned char byte);