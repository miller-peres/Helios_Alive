#include <string.h>
#include <stdio.h>
#include <math.h>
#include "type.h"
//#include "irq.h"
#include "time.h"
#include "serial.h"
#include "lpc21xx.h"
#include "global.h"
#include "timer.h"
#include "fsm_master.h"
#include "zigbee.h"
//#include "vic.h"
//#include "spo2.h"
#define BUZZER    				P0_7

unsigned char derivacao = 0;
unsigned char i 		= 0;

int main(int argc, char** argv)
{
	static Vic start_vic;						  // OBJETO VIC
	start_vic.init_VIC();
	InitTimer(0,250); 							  // FSM_Master, FSM_LED, FSM_Button, FSM_Alarm estão aqui dentro
	int a;	
	// DEFINE PINOS DE SAÍDA
	IO0DIR |= ( LED_ENF + LED_SPO2 + LED_ECG + LED_ON_BAT  + LED_VM_AM );												
	IO0DIR |= ( TX0 + SCK0 + MOSI0 + BUZZER + TX1 + ON_OFF  + CS_AD  + DER_1 + DER_2 + RESET_ZIGBEE ); 
	PINSEL1 &= ~0xE000000 ;						  //Configura o pino P0_28 como GPIO - LÊ PINI RSSI
	PINSEL1 &= ~0xC000000 ;						  //Configura o pino P0_29 como GPIO - BOTÃO LIG/DESL
	PINSEL1 &= ~0x1C000000 ;					  //Configura o pino P0_30 como GPIO - PINO LED AM/VM
	
	static Zigbee Init_zigbee;					  // OBJETO ZIGBEE
	//static Vic init_VIC_cpy;					 
	Init_zigbee.config_COM_zigbee(start_vic);     // INICIALIZA COM0 - ZIGBEE
	//IO0SET |= RESET_ZIGBEE; 					  // SETA PINO DE RESET PARA 1 (RESETA EM 0)
	
	while(1) 							
	{
		a++;
		if (a<20) Init_zigbee.send_package(false);          // HABILITA ENVIO DE DADOS PELA SERIAL (COM0 - ZIGBEE)
		else if (a>19)Init_zigbee.send_package(true);
		if (a>40) a=0;
	}
}
