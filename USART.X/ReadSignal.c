/*
 * File:   ReadSignal.c
 * Author: mateus
 *
 * Created on 29 de Junho de 2017, 21:07
 */


#include <xc.h>

#define _XTAL_FREQ 16000000

void readSignal(char *signal, int pos){
    
    int j = 0;
    if(pos == 1)
        j = 4;
    int limite;
    limite = j + 4;
    int i;
    
    while(j < limite){
        
        i = 0;
        while(i < 500){
            if(ADCRead() > 9){
                *signal |= (0x03<<j);
            }
            __delay_ms(1);    
            i++;
        }
        j+=2;
    }
}

int cmpSignal(char *pass, char *toc){
    
    if(pass[0] == toc[0] && pass[1] == toc[1])
        return 1;
    return 0;
}
