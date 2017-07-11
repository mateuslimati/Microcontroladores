/*
 * File:   USART.c
 * Author: mateus
 *
 * Created on 23 de Maio de 2017, 11:26
 */

#include <xc.h>

extern int buttonCancel_Lock;
extern int buttonConfirm_Cad; 

void init_UART(){

    SPBRG = 25;                                   //Writing SPBRG Register
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

int cmp_MSG1(char msg){
    if(msg == 0x40)
        return 1;
    return 0;
}

int cmp_MSG2(char msg){
    if((msg & 0x1C) == 0x04){
        if((msg & 0x03) == 0x00)
            return 0;           //Botão 0
        if((msg & 0x03) == 0x01)
            return 1;           //Botão 1
    }
    return -1;                   //Botão não conhecido
        
}

void checkUSART(){
    
    if(UART_Data_Ready()){
        char msg = UART_Read();
        if(cmp_MSG1(msg)){
            if(UART_Data_Ready()){
                msg = UART_Read();
                int op = cmp_MSG2(msg);
                if(op == 0)
                    buttonCancel_Lock = 1;
                else if(op == 1)
                    buttonConfirm_Cad = 1;
            }
        }
    }
}