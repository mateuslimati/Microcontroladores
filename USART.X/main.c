 /*
 * File:   main.c
 * Author: Mateus Lima
 *
 * Created on 25 de Abril de 2017, 11:03
 */

// PIC18F4550 Configuration Bit Settings

// 'C' source line config statements

#include "main.h"
#include "LCD.h"
#include "Interrupt.h"
#include "ADC.h"
#include "TOCTOC.h"
#include "PWM.h"

int doorState = 0; //0 representa fechada
int buttonConfirm_Cad = 0;
int buttonCancel_Lock = 0;

void main(){
    
    init_PWM();
    init_INTRB2();
    init_LCD();
    init_ADC();
       
    char pass[2];
    pass[0] = 0x00;
    pass[1] = 0x00;
    char toc[2];
    toc[0] = 0x00;
    toc[1] = 0x00;
    
    cadastrarSenha(pass);
 
    do{
        
        destravarPorta(pass, toc);
        if(buttonConfirm_Cad == 1){
            buttonConfirm_Cad = 0;
            cadastrarSenha(pass);
        }
            
    }while(1);
    
}