 /*
 * File:   Interrupt.c
 * Author: mateus
 *
 * Created on 2 de Maio de 2017, 16:32
 */
#include <xc.h>
#include <pic18f4550.h>
#include "LCD.h"
#include "PWM.h"

#define _XTAL_FREQ 16000000


extern int buttonCancel_Lock;
extern int doorState;

//void interrupt low_priority INT(){ Interrupt for secound
//    
//    if(INTCONbits.TMR0IF == 1){
//        INTCONbits.TMR0IF = 0;
//        
//        TMR0H = 0xB;
//        TMR0L = 0xDC;
//        
//        if(i == 0){
//            i = 1;
//            //write_LCD("sec");
//        }
//        else{
//            i = 0;
//            //write_LCD("next");
//        }
//    }
//}

void interrupt ISR(){
    
    if(INTCON3bits.INT2IF){
        INTCON3bits.INT2IF = 0;
        buttonCancel_Lock = 1;
        if(doorState = 1){
            doorState = 0;
            DutyCycle_PWM(600);
            __delay_ms(400);
            DutyCycle_PWM(0);
        }
    }
}

void init_INTRB2(){
    
    INTCONbits.GIE = 0;
    INTCONbits.PEIE = 0;
    TRISBbits.RB2 = 1;
    INTCON2bits.INTEDG0 = 1;
    INTCON3bits.INT2IF = 0;
    INTCON3bits.INT2IE = 1;
    INTCONbits.GIE = 1;
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

