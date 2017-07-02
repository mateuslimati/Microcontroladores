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
#include "TOCTOC.h"
#include <time.h>

#define high 1
#define low  0

extern int button;

void lerToque(char* toque){
        
    int i = 0;
 
    toque[0] = 0x00;
    toque[1] = 0x00;
    
    clearLCD();
    set_line(0,0);
    write_LCD("Bata na porta");
    while((int)read_ADC() < 15);
    
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

void destravarPorta(char* pass, char* toque){
        
    int i = 0;
 
    toque[0] = 0x00;
    toque[1] = 0x00;
    
    clearLCD();
    set_line(0,0);
    write_LCD("Bata na porta");

    while((int)read_ADC() < 15){
        if(button == 1)
            return;
    }
        
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
    if(cmpPass(pass, toque)){
        clearLCD();
        set_line(0,1);
        write_LCD("Porta");
        set_line(1,2);
        write_LCD("Destravada!");
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

int cmpPass(char* pass, char* toque){

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
    return i;

}

int confirmarSenha(){
        clearLCD();
        set_line(0,1);
        write_LCD("Confirme sua");
        set_line(1,5);
        write_LCD("senha");
        while(1){
            if(button == 1){
                button = 0;
                return 0;
            }
            else if(PORTBbits.RB4)
                return 1;
        }
}

void cadastrarSenha(char* pass){
    
    TRISBbits.RB4 = 1;
    
    int i = 0;
    int j = 0;
    
    char temp1[2];
    temp1[0] = 0x00;
    temp1[1] = 0x00;

    char temp2[2];
    temp2[0] = 0x00;
    temp2[1] = 0x00;
    
    pass[0] = 0x00;
    pass[1] = 0x00;
    
    while(1){
        clearLCD();
        set_line(0,1);
        write_LCD("Cadastre sua");
        set_line(1,5);
        write_LCD("senha");
        __delay_ms(2000);

        lerToque(&temp1);
        clearLCD();
        set_line(0,2);
        write_LCD("Repita sua");
        set_line(1,5);
        write_LCD("senha");
        __delay_ms(2000);

        lerToque(&temp2);
        if(cmpPass(temp1, temp2))
            if(confirmarSenha())
                break;
  
    }
    
    pass[0] = temp1[0];
    pass[1] = temp1[1];
    
    clearLCD();
    set_line(0,6);
    write_LCD("Senha");
    set_line(1,3);
    write_LCD("Cadastrada");
    __delay_ms(3000);
    
}
