/*
 * File:   main.c
 * Author: mateus
 *
 * Created on 25 de Abril de 2017, 11:03
 */

// PIC18F4550 Configuration Bit Settings

// 'C' source line config statements

// CONFIG1L
#pragma config PLLDIV = 1        // PLL Prescaler Selection bits (No prescale (4 MHz oscillator input drives PLL directly))
#pragma config CPUDIV = OSC1_PLL2// System Clock Postscaler Selection bits ([Primary Oscillator Src: /1][96 MHz PLL Src: /2])
#pragma config USBDIV = 1        // USB Clock Selection bit (used in Full-Speed USB mode only; UCFG:FSEN = 1) (USB clock source comes directly from the primary oscillator block with no postscale)

// CONFIG1H
#pragma config FOSC = HS        // Oscillator Selection bits (HS oscillator (HS))
#pragma config FCMEN = OFF      // Fail-Safe Clock Monitor Enable bit (Fail-Safe Clock Monitor disabled)
#pragma config IESO = OFF       // Internal/External Oscillator Switchover bit (Oscillator Switchover mode disabled)

// CONFIG2L
#pragma config PWRT = OFF       // Power-up Timer Enable bit (PWRT disabled)
#pragma config BOR = ON         // Brown-out Reset Enable bits (Brown-out Reset enabled in hardware only (SBOREN is disabled))
#pragma config BORV = 3         // Brown-out Reset Voltage bits (Minimum setting 2.05V)
#pragma config VREGEN = OFF     // USB Voltage Regulator Enable bit (USB voltage regulator disabled)

// CONFIG2H
#pragma config WDT = OFF        // Watchdog Timer Enable bit (WDT disabled (control is placed on the SWDTEN bit))
#pragma config WDTPS = 32768    // Watchdog Timer Postscale Select bits (1:32768)

// CONFIG3H
#pragma config CCP2MX = ON      // CCP2 MUX bit (CCP2 input/output is multiplexed with RC1)
#pragma config PBADEN = OFF      // PORTB A/D Enable bit (PORTB<4:0> pins are configured as analog input channels on Reset)
#pragma config LPT1OSC = OFF    // Low-Power Timer 1 Oscillator Enable bit (Timer1 configured for higher power operation)
#pragma config MCLRE = ON       // MCLR Pin Enable bit (MCLR pin enabled; RE3 input pin disabled)

// CONFIG4L
#pragma config STVREN = ON      // Stack Full/Underflow Reset Enable bit (Stack full/underflow will cause Reset)
#pragma config LVP = OFF         // Single-Supply ICSP Enable bit (Single-Supply ICSP enabled)
#pragma config ICPRT = OFF      // Dedicated In-Circuit Debug/Programming Port (ICPORT) Enable bit (ICPORT disabled)
#pragma config XINST = OFF      // Extended Instruction Set Enable bit (Instruction set extension and Indexed Addressing mode disabled (Legacy mode))

// CONFIG5L
#pragma config CP0 = OFF        // Code Protection bit (Block 0 (000800-001FFFh) is not code-protected)
#pragma config CP1 = OFF        // Code Protection bit (Block 1 (002000-003FFFh) is not code-protected)
#pragma config CP2 = OFF        // Code Protection bit (Block 2 (004000-005FFFh) is not code-protected)
#pragma config CP3 = OFF        // Code Protection bit (Block 3 (006000-007FFFh) is not code-protected)

// CONFIG5H
#pragma config CPB = OFF        // Boot Block Code Protection bit (Boot block (000000-0007FFh) is not code-protected)
#pragma config CPD = OFF        // Data EEPROM Code Protection bit (Data EEPROM is not code-protected)

// CONFIG6L
#pragma config WRT0 = OFF       // Write Protection bit (Block 0 (000800-001FFFh) is not write-protected)
#pragma config WRT1 = OFF       // Write Protection bit (Block 1 (002000-003FFFh) is not write-protected)
#pragma config WRT2 = OFF       // Write Protection bit (Block 2 (004000-005FFFh) is not write-protected)
#pragma config WRT3 = OFF       // Write Protection bit (Block 3 (006000-007FFFh) is not write-protected)

// CONFIG6H
#pragma config WRTC = OFF       // Configuration Register Write Protection bit (Configuration registers (300000-3000FFh) are not write-protected)
#pragma config WRTB = OFF       // Boot Block Write Protection bit (Boot block (000000-0007FFh) is not write-protected)
#pragma config WRTD = OFF       // Data EEPROM Write Protection bit (Data EEPROM is not write-protected)

// CONFIG7L
#pragma config EBTR0 = OFF      // Table Read Protection bit (Block 0 (000800-001FFFh) is not protected from table reads executed in other blocks)
#pragma config EBTR1 = OFF      // Table Read Protection bit (Block 1 (002000-003FFFh) is not protected from table reads executed in other blocks)
#pragma config EBTR2 = OFF      // Table Read Protection bit (Block 2 (004000-005FFFh) is not protected from table reads executed in other blocks)
#pragma config EBTR3 = OFF      // Table Read Protection bit (Block 3 (006000-007FFFh) is not protected from table reads executed in other blocks)

// CONFIG7H
#pragma config EBTRB = OFF      // Boot Block Table Read Protection bit (Boot block (000000-0007FFh) is not protected from table reads executed in other blocks)

// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.
#define _XTAL_FREQ 16000000
#include <xc.h>
#include <pic18f4550.h>
#include "LCD.h"
#include "Interrupt.h"
#include "USART.h"
#include "ADC.h"
#include "Itoa.h"
#include "ReadSignal.h"

#define high 1
#define low 0

void main(){
    
    init_timer();
    init_LCD();
    init_UART();
    
    TRISCbits.RC2 = 0;
    TRISBbits.RB5 = 0;
    
    set_line(0, 0);   
    write_LCD("Microcontroladores");
    
    ADCInit();
    int i = 0;
    clearLCD();
    
    char pass[2];
    pass[0] = 0x00;
    pass[1] = 0x00;
    char toc[2];
    toc[0] = 0x00;
    toc[1] = 0x00;
    
    //do{
    write_LCD("Voce tem 5 seg-");
    set_line(1,0);
    write_LCD("undos para bater");
    __delay_ms(3000);
    
    while(i < 4){
        clearLCD(); 
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
    i = 0;
    
    clearLCD();
    set_line(0,5);
    write_LCD("Leitura");
    set_line(1,3);
    write_LCD("Finalizada");
    __delay_ms(3000);

    do{
        clearLCD();
        set_line(0,0);
        write_LCD("Bata na porta");
        __delay_ms(3000);
        toc[0] = 0x00;
        toc[1] = 0x00;

        while(i < 4){
            clearLCD(); 
            send_msg('1'+ i);
            if(i == 0)
                readSignal(&toc[0], low);
            else if(i == 1)
                readSignal(&toc[0], high);
            else if(i == 2)
                readSignal(&toc[1], low);            
            else
                readSignal(&toc[1], high);
            i++;
        }
        i = 0;

        i = cmpSignal(pass, toc);

        if(i == 1){
            clearLCD();
            set_line(0,3);
            write_LCD("As senhas");
            set_line(1,3);
            write_LCD("coincidem");
            PORTCbits.RC2 = 1;
            PORTBbits.RB5 = 0;
            __delay_ms(1000);    
            PORTCbits.RC2 = 0;
            PORTBbits.RB5 = 1;
            __delay_ms(1000);
        }
        else{
            clearLCD();
            set_line(0,3);
            write_LCD("As senhas");
            set_line(1,2);
            write_LCD("n�o coincidem");
            __delay_ms(2000);
        } 
        
            //__delay_ms(2000);
        PORTCbits.RC2 = 0;
        PORTBbits.RB5 = 0;
       
        i = 0;       
    }while(1);
    
}