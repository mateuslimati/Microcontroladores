/*
 * File:   PWM.c
 * Author: mateus
 *
 * Created on 3 de Julho de 2017, 13:27
 */

#include <pic18f4550.h>

#include <xc.h>
// -----------------------------------------------------
// Rotina de inicializa��o do m�dulo PWM
// -----------------------------------------------------
void init_PWM(void){
   TRISCbits.TRISC2 = 0;    // Usando o m�dulo CCP1 (pino C2)
   T2CON = 0x04;            // Timer2 desligado, Prescaler = 1 (p. 137 do datasheet)
   PR2 = 0xFF;              // Registrador que cont�m o per�odo do Timer2 (p. 137 do datasheet)
   CCP1CON = 0x3F;          // PWM com uma sa�da (P1A - Pino C2) (p. 151 do datasheet)
   CCPR1L = 0x00;           // Duty Cycle (junto com os bits 4 e 5 de CCP1CON para formar 10 bits)
}
// -----------------------------------------------------


// -----------------------------------------------------
// Rotina de configura��o do Periodo do PWM
// -----------------------------------------------------
// Para c�lculo do per�odo do PWM (p. 153 do datasheet):
// Periodo = [(PR2) + 1] * 4 * Tosc * (Timer2 Prescaler)
// -----------------------------------------------------
void Periodo_PWM(unsigned char Valor){
   T2CON = 0x04;         // Timer2 desligado, Prescaler = 1 (p. 137 do datasheet)
   PR2 = Valor;          // Registrador que cont�m o per�odo do Timer2 (p. 137 do datasheet)
}
// -----------------------------------------------------


// -----------------------------------------------------
// Rotina de configura��o de Duty Cycle do PWM
// -----------------------------------------------------
// Para c�lculo do Duty Cycle do PWM (p.154 do datasheet):
// DutyCycle = (CCPR1L:CCP1CON) * TOSC * (TMR2 Prescaler)
// -----------------------------------------------------
void DutyCycle_PWM(unsigned int Valor){
   CCP1CONbits.DC1B0 = Valor;
   CCP1CONbits.DC1B1 = Valor >> 1;
   CCPR1L = Valor >> 2;
}
// -----------------------------------------------------

