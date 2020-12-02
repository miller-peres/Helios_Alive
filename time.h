/******************************************************************************/
/*  Configurando timer 0 e timer 1 para gerar interrupcao a cada timer_tick (us)        */
/******************************************************************************/
/*
** Neste exemplo melhorado, a programacao do timer 0 fica independente da
** programacao do PLL, vc deve apenas informar o valor do cristal utilizado
**
** Parametros de projeto:
** cristal de 10Mhz
** PLL = NAO INTERESSA !!! PODE SER QUALQUER COISA !!!
** VPB clock (clock dos perifericos) = NAO INTERESSA !!! PODE SER QUALQUER COISA !!!
**
** Neste exemplo, suponha que queremos um timer_tick de 250 ms ou 250000 us
**
******************************************************************************/
#include <LPC22XX.H>    // LPC22XX Peripheral Registers
/*******************************************************************
**
** Frequencia do cristal...
** IMPORTANTE - se voce usar cristal com frequencia diferente,
** ajuste este valor, senao o timer nao funcionara adequadamente
**
********************************************************************/
#define XTAL_IN_HZ  10000000  /* 10 milhoes de hz */

//===================================================================================
#define TIMER_TICK_DESEJADO 1000000 /* 1 milhao de us = 1 s */
//#define TIMER_TICK_DESEJADO  500000 /* 500 mil us = 0,500 s */
//#define TIMER_TICK_DESEJADO  250000 /* 250 mil us = 0,250 s */
//#define TIMER_TICK_DESEJADO  125000 /* 125 mil us = 0,125 s */
//#define TIMER_TICK_DESEJADO    5000 /* 5 mil us = 5 ms */
//#define TIMER_TICK_DESEJADO    1000 /* 1 mil us = 1 ms */
//#define TIMER_TICK_DESEJADO        10 /* 10 us */
//===================================================================================
#define APBDIV VPBDIV //so para compatibilizar nomenclatura Keil vs datasheet 
//===================================================================================

#define NUM_TIMERS        1  // Timer 0 e Timer 1

void SetupPLL      (void) ;
void SetupVPBclock (void) ;
int  InitTimer     (char nTimer,unsigned long timer_tick) ;
void Delay         (short nDelay);
void Calculos(void);







