/*
 * File:   Buzzer.c
 * Author: mateus
 *
 * Created on 30 de Junho de 2017, 23:33
 */


#include <xc.h>
#include <time.h>
#include <pic18f4550.h>
#define _XTAL_FREQ 16000000

void bip(int rounds, int time){
        
    TRISCbits.RC1 = 0;
    PORTCbits.RC1 = 0;
    
    int j = 0;
    if(time == 500){
        while(j < rounds){
                PORTCbits.RC1 = !PORTCbits.RC1;
                __delay_ms(500);
                j++;
        }
    }
    else if(time == 1000){
        while(j < rounds){
                PORTCbits.RC1 = !PORTCbits.RC1;
                __delay_ms(1000);
                j++;
        }
    }
}
