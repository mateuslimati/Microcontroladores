/*
 * File:   LED.c
 * Author: mateus
 *
 * Created on 30 de Junho de 2017, 20:18
 */

#include <xc.h>
#include <pic18f4550.h>
#include <time.h>

#define _XTAL_FREQ 16000000

void blink(int rounds, int time){
            
    int i = 0;
    while(i < rounds){
        PORTCbits.RC2 = !PORTCbits.RC2;
        __delay_ms(time);    
    }
    
}
