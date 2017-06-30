/*
 * File:   LCD.c
 * Author: mateus
 *
 * Created on 2 de Maio de 2017, 16:22
 */
#include <xc.h>

#define _XTAL_FREQ 16000000

void ena_pulse(){

    PORTEbits.RE1 = 0;
    __delay_ms(1);
    PORTEbits.RE1 = 1;
    __delay_ms(1);
    PORTEbits.RE1 = 0;
    __delay_ms(1);
    
}

void send_cfg(char cmd){

    PORTD = cmd;
    PORTBbits.RB3 = 0;
    ena_pulse();
    __delay_ms(1);
    
}

void clearLCD(){
    send_cfg(0x01); //Clear Display
}

void send_msg(char msg){

    PORTD = msg;
    PORTBbits.RB3 = 1;
    __delay_ms(1);
    ena_pulse();
    __delay_ms(1);
    PORTBbits.RB3 = 0;
}

void init_LCD(){
    
    TRISB = 0x04;
    TRISD = 0x00;
    TRISE = 0x00;
    PORTD = 0x00;
    
    send_cfg(0x01); //Clear Display
    send_cfg(0x38); //Configura para operações com 8 bits e seleciona o display de duas linhas
    send_cfg(0x80); //Seta o display na posição (0,0)
    send_cfg(0x0F);  //Ativa o       
    //send_cfg(0x01);
}

void write_LCD(char *c){
    
    int i = 0;
    for(; c[i] != '\0'; i++)
        send_msg(c[i]);
}

void set_line(int line, int pos){
    
    char cursor;    
    if(line == 0)
        cursor = 0x80 + pos;
    else
        cursor = 0xC0 + pos;
    send_cfg(cursor);

}