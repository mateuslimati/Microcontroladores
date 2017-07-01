/*
 * File:   TOCTOC.c
 * Author: mateus
 *
 * Created on 30 de Junho de 2017, 23:42
 */

#define _XTAL_FREQ 16000000
#include <xc.h>
#include <pic18f4550.h>
#include "LCD.h"
#include "ReadSignal.h"
#include "Buzzer.h"
#include <time.h>

#define high 1
#define low  0

void cadastrarSenha(char* pass){
    
    int i = 0;
    
    pass[0] = 0x00;
    pass[1] = 0x00;
    
    clearLCD();
    set_line(0,1);
    write_LCD("Cadastre sua");
    set_line(1,5);
    write_LCD("senha");
    
    while(i < 4){
        set_line(1,15);
        send_msg('1'+ i);
        if(i == 0)
            readSignal(&pass[0], low);
        else if(i == 1)
            readSignal(&pass[0], high);
        else if(i == 2)
            readSignal(&pass[1], low);            
        else
            readSignal(&pass[1], high);
        i++;
    }
    
    clearLCD();
    set_line(0,5);
    write_LCD("Leitura");
    set_line(1,3);
    write_LCD("Finalizada");
    __delay_ms(3000);

}

void lerToque(char* toque){
        
    int i = 0;
 
    toque[0] = 0x00;
    toque[1] = 0x00;
    
    clearLCD();
    set_line(0,0);
    write_LCD("Bata na porta");
    
    while(i < 4){
        set_line(1,0); 
        send_msg('1'+ i);
        if(i == 0)
            readSignal(&toque[0], low);
        else if(i == 1)
            readSignal(&toque[0], high);
        else if(i == 2)
            readSignal(&toque[1], low);            
        else
            readSignal(&toque[1], high);
        i++;
    }    
}

void cmpPass(char* pass, char* toque){

    int i = cmpSignal(pass, toque);

    if(i == 1){
        clearLCD();
        set_line(0,3);
        write_LCD("As senhas");
        set_line(1,3);
        write_LCD("coincidem");
        bip(2, 1000);  
    }
    else{
        clearLCD();
        set_line(0,3);
        write_LCD("As senhas");
        set_line(1,1);
        write_LCD("nao coincidem");
        bip(4, 500);
    } 

}
