/*
 * File:   I²C.c
 * Author: mateus
 *
 * Created on 11 de Julho de 2017, 01:16
 */


#include <xc.h>
#define _XTAL_FREQ 16000000

void init_I2C(const unsigned long clock){
    SSPCON1 = 0b00101000;            //Configura as funções do módulo MSSP e define o modo como Master e o clock
                                     //clock = Fosc/(4*(SSPADD) + 1) => SSPADD + 1 = Fosc/4*clock;
    SSPCON2 = 0;                     //Zera os bits de status de SSPCON2;
    SSPADD = (_XTAL_FREQ/(4*clock))-1;   //Configura a velocidade do clock 
    SSPSTAT = 0;
    TRISBbits.RB1 = 0;               //Setting as input as given in datasheet
    TRISBbits.RB0 = 0;               //Setting as input as given in datasheet
}

void I2C_Master_Wait(){
    while ((SSPSTAT & 0x04) || (SSPCON2 & 0x1F)); //Transmit is in progress
}

void I2C_Master_Start(){
    I2C_Master_Wait();    
    SSPCON2bits.SEN = 1;             //Initiate start condition
}

void I2C_Master_RepeatedStart(){
    I2C_Master_Wait();
    SSPCON2bits.RSEN = 1;           //Initiate repeated start condition
}

void I2C_Master_Stop(){
    I2C_Master_Wait();
    SSPCON2bits.PEN = 1;           //Initiate stop condition
}

void I2C_Master_Write(char data){
    I2C_Master_Wait();
    SSPBUF = data;         //Write data to SSPBUF
}

char I2C_Master_Read(unsigned short a){
    char data;
    I2C_Master_Wait();
    SSPCON2bits.RCEN = 1;
    I2C_Master_Wait();
    data = SSPBUF;      //Read data from SSPBUF
    I2C_Master_Wait();
    if(a == 0)
        ACKDT = 0;
    else
        ACKDT = 1;    //Acknowledge bit
    ACKEN = 1;          //Acknowledge sequence
    return data;
}
    