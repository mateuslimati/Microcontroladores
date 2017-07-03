// ================================================ //
// BIBLIOTECA PARA USO DE PWM NO PIC 18F4550        //
//                                                  //
// ESCOLA SENAI "A. JACOB LAFER                     //
// CURSO TÉCNICO DE ELETROELETRÔNICA                //
// DISCIPLINA: DESET                                //
// DATA: 21/09/2016                                 //
// REVISÃO: A                                       //
// ================================================ //

#ifndef PWM
#define	PWM

#include <xc.h> // include processor files - each processor file is guarded.  

#ifndef PWM_H_
#define PWM_H_

void init_PWM(void);
void Periodo_PWM(unsigned char Valor);
void DutyCycle_PWM(unsigned int Valor);

#endif
#endif	/* XC_HEADER_TEMPLATE_H */

