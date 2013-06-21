#include <htc.h>            /* HiTech General Includes */
#include <stdint.h>         /* For uint8_t definition */
#include <stdbool.h>        /* For true/false definition */
#include <plib.h>           /* Peripheral Library Functions */


#include "user.h"           /* User funct/params, such as InitApp */
#include "NRF24L01P.h"

void RF_ConfigTransmitter(void){

    CE = 0;

    CSN = 0;
    // PTX, CRC enabled, mask a couple of ints
    SPI_Transceive(WRITE_REG + CONFIG);     // Write Command + CONFIG Register
    SPI_Transceive(0x38);     // Reflect RX_DR, Enable CRC, PTX
    CSN = 1;

    CSN = 0;
    //auto retransmit off
    SPI_Transceive(WRITE_REG + SETUP_RETR);     // Write Command + SETUP_RETR Register
    SPI_Transceive(0x00);     // Retransmit off
    CSN = 1;

    CSN = 0;
    //address width = 5
    SPI_Transceive(WRITE_REG + SETUP_AW);     // Write Command + SETUP_AW Register
    SPI_Transceive(NRF24L01_ADDR_WIDTH);     // 5 bytes address width
    CSN = 1;

    CSN = 0;
    //data rate = 2Mbps
    SPI_Transceive(WRITE_REG + RF_SETUP);     // Write Command + RF_SETUP
    SPI_Transceive(0x07);     // 2Mbps @ 0 dBm
    CSN = 1;

    CSN = 0;
    //set channel 2, this is default but we did it anyway...
    SPI_Transceive(WRITE_REG + RF_CH);     // Write Command + RF_CH
    SPI_Transceive(0x02);     // Channel 2
    CSN = 1;

    CSN = 0;
    //set address E7E7E7E7E7, also default...
    SPI_Transceive(WRITE_REG + TX_ADDR);     // Write Command + TX_ADDR
    for (int i = 0; i < (NRF24L01_ADDR_WIDTH + 0x02); i++){
        SPI_Transceive(NRF24L01_TX_ADDR_BUFFER[i]); // E7 = default
    }
    CSN = 1;

    CSN = 0;
    //disable auto-ack, RX mode
    //shouldn't have to do this, but it won't TX if you don't
    SPI_Transceive(WRITE_REG + EN_AA);     // Write Command + EN_AA
    SPI_Transceive(0x00);     // Disable Auto ACK for all Pipes
    CSN = 1;
}

void RF_TransmitData(void){

    CSN = 0;
    //clear previous ints
    SPI_Transceive(WRITE_REG + STATUS);     // Write Command + STATUS Register
    SPI_Transceive(0x7E);     // Clear TX_DS, MAX_RT
    CSN = 1;

    CSN = 0;
    //PWR_UP = 1
    SPI_Transceive(WRITE_REG + CONFIG);     // Write Command + CONFIG Register
    SPI_Transceive(0x3A);     // Reflect RX_DR, Enable CRC, POWER UP, PTX
    CSN = 1;

    CSN = 0;
    //clear TX FIFO
    //the data sheet says that this is supposed to come up 0 after POR, but that doesn't seem to be the case
    SPI_Transceive(FLUSH_TX);     // FLUSH_TX
    CSN = 1;

    CSN = 0;
    //4 byte payload
    SPI_Transceive(W_TX_PAYLOAD);     // W_TX_PAYLOAD
    for (int i = 0; i < NRF24L01_PAYLOAD_WIDTH; i++){
    SPI_Transceive(RF_TransmitBuffer[i]);
    }
    CSN = 1;

    //Pulse CE to start transmission
    CE = 1;
    Delay10KTCYx(36);            // 72 mSec
    CE = 0;
}

void RF_ConfigReceiver(void){

    CE = 0;

    CSN = 0;
    //PRX, CRC enabled
    SPI_Transceive(WRITE_REG + CONFIG);     // Write Command + CONFIG Register
    SPI_Transceive(0x39);     // Reflect RX_DR, Enable CRC, PRX
    CSN = 1;

    CSN = 0;
    //disable auto-ack for all channels
    SPI_Transceive(WRITE_REG + EN_AA);     // Write Command + EN_AA Register
    SPI_Transceive(0x00);     // Disable Auto Acknowledgment
    CSN = 1;

    CSN = 0;
    //address width = 5 bytes
    SPI_Transceive(WRITE_REG + SETUP_AW);     // Write Command + SETUP_AW Register
    SPI_Transceive(NRF24L01_ADDR_WIDTH);     // 5 bytes address width
    CSN = 1;

    CSN = 0;
    //data rate = 1MB
    SPI_Transceive(WRITE_REG + RF_SETUP);     // Write Command + RF_SETUP Register
    SPI_Transceive(0x07);     // 2 Mbps @ 0 dBm
    CSN = 1;

    CSN = 0;
    //4 byte payload
    SPI_Transceive(WRITE_REG + RX_PW_P0);     // Write Command + RX_PW_P0
    SPI_Transceive(NRF24L01_PAYLOAD_WIDTH);     // 4 bytes payload in pipe 0
    CSN = 1;

    CSN = 0;
    //set channel 2
    SPI_Transceive(WRITE_REG + RF_CH);     // Write Command + RF_CH Register
    SPI_Transceive(0x02);     // Use RF channel 2
    CSN = 1;

    CSN = 0;
    //set addres to receive from
    SPI_Transceive(WRITE_REG + RX_ADDR_P0);
    for (int i = 0; i < (NRF24L01_ADDR_WIDTH + 0x02); i++){
        SPI_Transceive(NRF24L01_RX_ADDR_BUFFER[i]); // E7 = default
    }
    CSN = 1;

    CSN = 0;
    //set address E7E7E7E7E7
    SPI_Transceive(WRITE_REG + TX_ADDR);     // Write Command + TX_ADDR Register
    for (int i = 0; i < (NRF24L01_ADDR_WIDTH + 0x02); i++){
        SPI_Transceive(NRF24L01_RX_ADDR_BUFFER[i]); // E7 = default
    }
    CSN = 1;

    CSN = 0;
    //PWR_UP = 1
    SPI_Transceive(WRITE_REG + CONFIG);     // Write Command + CONFIG Register
    SPI_Transceive(0x3B);     // Reflect RX_DR, Enable CRC, Power UP, PRX
    CSN = 1;

    Delay10KTCYx(1);     // 2 mSec

    CE = 1;             // Turn receiver on
}

void RF_ResetReceiver(void){
    // Shut off receiver before reading STATUS and writing registers
    // Registers can not be written if CE is high
    CE = 0;

    //Read STATUS Register
    CSN = 0;
    SPI_Transceive(READ_REG + STATUS);
    STATUS_Data = SPI_Transceive(0);
    CSN = 1;

    //Read RX payload
    CSN = 0;
    SPI_Transceive(R_RX_PAYLOAD);     // R_RX_PAYLOAD
    for (int i = 0; i < NRF24L01_PAYLOAD_WIDTH; i++){
       	RF_ReceiveBuffer[i] = SPI_Transceive(0);
    }
    CSN = 1;
    
    //Read FIFO STATUS
    CSN = 0;
    SPI_Transceive(READ_REG + FIFO_STATUS);
    FIFO_STATUS_Data = SPI_Transceive(0);
    CSN = 1;
    
    if((FIFO_STATUS_Data & 0x01) == 0){
        while((FIFO_STATUS_Data & 0x01) == 0){
            //Read RX payload
            CSN = 0;
            SPI_Transceive(R_RX_PAYLOAD);     // R_RX_PAYLOAD
            for (int i = 0; i < NRF24L01_PAYLOAD_WIDTH; i++){
                RF_ReceiveBuffer[i] = SPI_Transceive(0);
            }
            CSN = 1;

            //Read FIFO STATUS
            CSN = 0;
            SPI_Transceive(READ_REG + FIFO_STATUS);
            FIFO_STATUS_Data = SPI_Transceive(0);
            CSN = 1;
        }
    }

    //Flush RX FIFO
    CSN = 0;
    SPI_Transceive(FLUSH_RX);
    CSN = 1;

    CSN = 0;
    //Reset Interrupts
    SPI_Transceive(WRITE_REG + STATUS);
    SPI_Transceive(0x70);
    CSN = 1;

}

unsigned char SPI_Transceive(unsigned char byte){

    SSPBUF = byte;
    while(!DataRdySPI());
    return SSPBUF;
}

