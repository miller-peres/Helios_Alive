#include "botao.h"
#include "lpc21xx.h"
#include "global.h"

botao::botao(void){}

void botao::FSM_botao(void)
{
	time_on_push_button = 20000;
		if(!(IOPIN0 & BOTAO_ON_OFF))
		{
			time_push_button = 0;
			IO0CLR |= BUZZER;
			
		}
		else if(time_push_button < time_on_push_button)
		{ time_push_button++;
			IO0SET |= BUZZER;
			
		}
			
		if(time_push_button >= time_on_push_button)
		{
			//if(gLiberaDesliga)
			//{
				IO0CLR |= RESET_ZIGBEE;//reseta o Zigbee
				//Desliga todos GPIOs
				//IO0DIR  = 0;
				IO0CLR |= ON_OFF;
				IO0SET |= LED_ECG;
				IO0SET |= LED_SPO2;
				IO0SET |= LED_ENF;
				IO0CLR |= BUZZER;
				IO0SET |= LED_ON_BAT;
				gIndexVetor = 0;
				while(1)
				{
					//Só fica preso para o software não rodar quando quiser desligar o aparelho.
				}
			//}
			gBotaoDesliga = 1;
		}
		else     
		{
			gBotaoDesliga = 0;
			
			IO0SET |= ON_OFF;
		}
}