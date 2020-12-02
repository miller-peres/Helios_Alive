/******************************************************************************/
/* delay.c: */
/******************************************************************************/
/******************************************************************************/
#include "lpc21xx.h"                     /* LPC21xx definitions               */
/*============================================================================
= FREE RUNNER                                                                =
============================================================================*/

#define MSEC (100)

#define FREE_RUNNER_MATCH_0(param) {PWMMR0 = (param);}
#define FREE_RUNNER_MATCH_1(param) {PWMMR1 = (param);}
#define FREE_RUNNER_MATCH_2(param) {PWMMR2 = (param);}
#define FREE_RUNNER_MATCH_3(param) {PWMMR3 = (param);}
#define FREE_RUNNER_MATCH_4(param) {PWMMR4 = (param);}
#define FREE_RUNNER_MATCH_5(param) {PWMMR5 = (param);}
#define FREE_RUNNER_MATCH_6(param) {PWMMR6 = (param);}

#define FR_0             (0x0001)
#define FR_1             (0x0002)
#define FR_2             (0x0004)
#define FR_3             (0x0008)
#define FR_4             (0x0100)
#define FR_5             (0x0200)
#define FR_6             (0x0400)

#define ATIVA_FREE_RUNNER() {PWMTCR = 0x01;}
#define DESATIVA_FREE_RUNNER() {PWMTCR = 0x00;}
#define TEMPO_PARA_ESTOURO_FR(param) (PWMMR##param - PWMTC) 

#define ZERA_FREE_RUNNER()                                                   \
{                                                                            \
  PWMTCR = 0x02;                                                             \
  while(PWMTC);                                                              \
  PWMIR =  0x070F;                                                           \
  while(PWMIR);                                                              \
}

#define REINICIA_FREE_RUNNER()                                               \
{                                                                            \
  ZERA_FREE_RUNNER();                                                        \
  ATIVA_FREE_RUNNER();                                                       \
}

#define ESTOUROU_FR_0() (PWMIR & FR_0)
#define ESTOUROU_FR_1() (PWMIR & FR_1)
#define ESTOUROU_FR_2() (PWMIR & FR_2)
#define ESTOUROU_FR_3() (PWMIR & FR_3)
#define ESTOUROU_FR_4() (PWMIR & FR_4)
#define ESTOUROU_FR_5() (PWMIR & FR_5)
#define ESTOUROU_FR_6() (PWMIR & FR_6)


#define LIMPA_FREE_RUNNER(param) {PWMIR = (param);}

#if VPBDIV4
#define CONFIGURA_FREE_RUNNER_PRESCALER() {PWMPR = 188;}
#else
//#define CONFIGURA_FREE_RUNNER_PRESCALER() {PWMPR = 750;}
#define CONFIGURA_FREE_RUNNER_PRESCALER() {PWMPR = 900;}
#endif
#define CONFIGURA_FREE_RUNNER_TCR() {PWMTCR = 0x03;}
#define CONFIGURA_FREE_RUNNER_MCR() {PWMMCR = 0x03; }


void  configuraFreeRunner(void)
{
  /***************************************************************************
  * FREE RUNNER                                                              *
  *                                                                          *
  * Na verdade, esse free runner nao e' bem um free runner, pois ele e' acio-*
  * nado somente quando necessario.                                          *
  *                                                                          *
  * O free runner sera' configurado no timer do PWM. Para usar o PWM como ti-*
  * mer generico, basta setar o bit PWMTCR[3] para zero.                     *
  *                                                                          *
  * A configuracao do timer sera' a seguinte: o MR0 do PWM reseta a contagem *
  * do timer. Todos os outros MRs serao usados como contagens intermediarias.*
  ***************************************************************************/
  CONFIGURA_FREE_RUNNER_TCR();
  CONFIGURA_FREE_RUNNER_PRESCALER(); // 0,01ms
  CONFIGURA_FREE_RUNNER_MCR(); // reseta no MR0
}



void controlaFreeRunner(long tempoFreeRunner)
/****************************************************************************/
{
  short ContadorFreeRunner = 0;

  FREE_RUNNER_MATCH_0((unsigned)tempoFreeRunner);
  REINICIA_FREE_RUNNER();

  while(!ESTOUROU_FR_0())
  {
    ATIVA_FREE_RUNNER(); //garante que o free runner esta' rodando
    ContadorFreeRunner++;
  }

//  ZERA_FREE_RUNNER();
}

void delay (short time) {
     configuraFreeRunner();
     controlaFreeRunner(time);
}

