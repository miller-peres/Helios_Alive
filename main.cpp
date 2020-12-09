#include <string.h>
#include <stdio.h>
#include <math.h>
#include "type.h"
#include "irq.h"
#include "time.h"
#include "serial.h"
#include "lpc21xx.h"
#include "global.h"
#include "timer.h"
#include "analise.h"
#include "ssp.h"
#include "i2c.h"
#include "fsm_master.h"


unsigned char derivacao = 0;
unsigned char i = 0;


int main(int argc, char** argv)
{
	init_VIC();
	
	InitTimer(0,250);
	//InitTimer(1,10000);									//quanto maior, menor a frequencia do clock
	//Master_FSM FSM_state; 
	//InitTimer(0,250); 									//aqui, quanto maior, menor a frequencia do clock, setado para 250us
	IO0DIR |= ( LED_ENF + LED_SPO2 + LED_ECG + LED_ON_BAT );												
	IO0DIR |= ( TX0 + SCK0 + MOSI0 + BUZZER + TX1 + ON_OFF  + CS_AD  + DER_1 + DER_2 + RESET_ZIGBEE); 
	PINSEL1 &= ~0xC000000 ;								//Configura o pino P0_29 como GPIO
	//I2CInit(I2CMASTER);										// inicializa i2c
	//Alarme init_timer_alarm;
	
	
}
