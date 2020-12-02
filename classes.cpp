#include <string.h>
#include <stdio.h>
#include <math.h>
#include <string>
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
#include "Led.h"
#include "Master_FSM.h"

using namespace std;

 Led::Led(void){}
 
// PARA ECG
void Led::ECG_Alta(void) 
{
	
	IO0CLR |= DER_1;
	IO0SET |= LED_ECG;
	
	IO0CLR |= LED_SPO2;
	IO0CLR |= LED_ENF;
	IO0CLR |= LED_ON_BAT;
			
}

void Led::ECG_Media(void) 
{
	IO0SET |= DER_1;
	IO0CLR |= LED_ECG;
	
	IO0SET |= LED_SPO2;
	IO0SET |= LED_ENF;
	IO0SET |= LED_ON_BAT;
		
}

// PARA SPO2
void Led::SPO2_Alta(void) 
{
	IO0CLR |= DER_1;
	IO0SET |= LED_SPO2;
	
	IO0CLR |= LED_ECG;
	IO0CLR |= LED_ENF;
	IO0CLR |= LED_ON_BAT;
}

void Led::SPO2_Media(void) 
{
	IO0SET |= DER_1;
	IO0CLR |= LED_SPO2;
	
	IO0SET |= LED_ECG;
	IO0SET |= LED_ENF;
	IO0SET |= LED_ON_BAT;
		
}

//PARA BATERIA
void Led::BAT_OK(void) 
{
	IO0CLR |= DER_1;
	IO0SET |= LED_ON_BAT;
	
	IO0CLR |= LED_ECG;
	IO0CLR |= LED_ENF;
	IO0CLR |= LED_SPO2;
}

void Led::BAT_Media(void) 
{
	IO0SET |= DER_1;
	IO0CLR |= LED_ON_BAT;
	
	IO0SET |= LED_SPO2;
	IO0SET |= LED_ENF;
	IO0SET |= LED_ON_BAT;
		
}

//PARA ENF
void Led::ENF_Alta(void) 
{
	IO0CLR |= DER_1;
	IO0SET |= LED_ENF;
	
	IO0CLR |= LED_SPO2;
	IO0CLR |= LED_ENF;
	IO0CLR |= LED_ON_BAT;
}

void Led::ENF_Media(void) 
{
	IO0SET |= DER_1;
	IO0CLR |= LED_ENF;
	
	IO0SET |= LED_SPO2;
	IO0SET |= LED_ENF;
	IO0SET |= LED_ON_BAT;
		
}


Master_FSM::Master_FSM(void){contador_timer = 0;}
		
void Master_FSM::FSM_LED(void)
{
	contador_timer ++;
	if (contador_timer == 10)contador_timer = 0;
	
	if (contador_timer == 2)
	{
		Leds.ECG_Alta();
	}
	
}




