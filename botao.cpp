#include "botao.h"
#include "lpc21xx.h"
#include "global.h"

Button::Button(){}

enum STATE_BUTTON_FSM
{
	CHECK_TURN_ON = 0,
	PRESSED_BUTTON,
	TURN_OFF,
	NURSE_CALL_ON,
	NURSE_CALL_OFF,
};
	
bool Button::get_nurse_calling(void)
{
	return nurse_calling;
}

void Button::FSM_button()
{
time_to_turn_off = 20000; //resetar contador no final
time_nurse_push_button_in = 4000;
time_nurse_push_button_out = 10000;

	switch(state_botao)
	{
		case CHECK_TURN_ON:
			if(IOPIN0 & BOTAO_ON_OFF)
			{
				IO0SET |= ON_OFF; 
				state_botao = PRESSED_BUTTON;
			}
		break;
		
		case PRESSED_BUTTON:
			if(!(IOPIN0 & BOTAO_ON_OFF))
			{ 
				time_push_button = 0;
			}
		
			//VERIFICA TEMPO PARA CHAMADA DE ENFERMEIRA
			if (time_push_button >= time_nurse_push_button_in)
			{
				nurse_calling = true;
				if (time_push_button >= time_to_turn_off) state_botao = TURN_OFF;
			}
			
			if (time_push_button >= time_nurse_push_button_out)
			{
				nurse_calling = false;
				if (time_push_button >= time_to_turn_off) state_botao = TURN_OFF;
			}
			
			if (time_push_button >= time_to_turn_off) state_botao = TURN_OFF;
			
			else 
			{ 	
				time_push_button++;
			}
		break;	
		
		case TURN_OFF:
			IO0CLR |= ON_OFF;
			IO0SET |= LED_ECG;
			IO0SET |= LED_SPO2;
			IO0SET |= LED_ENF;
			state_botao = CHECK_TURN_ON;
			while(1)
			{
			//Só fica preso para o software não rodar quando quiser desligar o aparelho.
			}
		break;
	}
}