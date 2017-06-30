/*
 * File:   USART.c
 * Author: mateus
 *
 * Created on 23 de Maio de 2017, 11:26
 */

#include <xc.h>

void init_UART(){

    SPBRG = 12;                                    //Writing SPBRG Register
    BRGH = 0;
    SYNC = 0;                                     //Setting Asynchronous Mode, ie UART
    SPEN = 1;                                     //Enables Serial Port
    TRISC7 = 1;                                   //As Prescribed in Datasheet
    TRISC6 = 1;                                   //As Prescribed in Datasheet
    CREN = 1;                                     //Enables Continuous Reception
    TXEN = 1;                                     //Enables Transmission
}

void UART_Write(char data){
  while(!TRMT);
  TXREG = data;
}

char UART_TX_Empty(){
  return TRMT;
}

void UART_Write_Text(char *text){
  int i;
  for(i=0;text[i]!='\0';i++)
    UART_Write(text[i]);
}

char UART_Data_Ready(){
  return RCIF;
}

char UART_Read(){
  while(!RCIF);
  return RCREG;
}

void UART_Read_Text(char *Output, unsigned int length){
  unsigned int i;
  for(int i=0;i<length;i++)
  Output[i] = UART_Read();
}
