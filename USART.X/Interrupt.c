/*
 * File:   Interrupt.c
 * Author: mateus
 *
 * Created on 2 de Maio de 2017, 16:32
 */
#include <xc.h>
#include "LCD.h"

int i = 0;

void interrupt low_priority INT(){
    
    if(INTCONbits.TMR0IF == 1){
        INTCONbits.TMR0IF = 0;
        
        TMR0H = 0xB;
        TMR0L = 0xDC;
        
        if(i == 0){
            i = 1;
            //write_LCD("sec");
        }
        else{
            i = 0;
            //write_LCD("next");
        }
    }
}

void init_timer(){

    TRISD = 0x00;

    INTCONbits.GIE = 0;             //global interrupt disable
    INTCONbits.PEIE = 1;            //peripheral interrupt enable
    INTCONbits.TMR0IF = 0x00;       //clear timer0 interrupt flag
    INTCONbits.TMR0IE = 1;          //enable timer0 interrupt
        
    // 1 second interrupt; 
    T0CONbits.T08BIT = 0;
    T0CONbits.T0CS = 0;
    T0CONbits.PSA = 0;
    T0CONbits.T0PS2 = 1;
    T0CONbits.T0PS1 = 0;
    T0CONbits.T0PS0 = 0;
    TMR0H = 0xB;
    TMR0L = 0xDC;
    T0CONbits.TMR0ON = 1;
    
    INTCONbits.GIE = 1;             //global interrupt disable
}

