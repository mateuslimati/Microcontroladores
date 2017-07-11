/*
 * File:   ADC.c
 * Author: mateus
 *
 * Created on 29 de Junho de 2017, 16:19
 */


#include <xc.h>

void init_ADC(){
    TRISAbits.TRISA0 = 1;
    ADCON0 = 0;
    ADCON1 = 0x0e;
    ADCON2 = 0xd9;
    ADCON0bits.ADON = 1;
    
}

unsigned int read_ADC(){
    unsigned int value;
    ADCON0bits.GO = 1;
    
    while(ADCON0bits.DONE);
    value = ADRES;
    
    return value;
}