#include "type.h"
#include "irq.h"
#include "serial.h"
#include "lpc21xx.h"
#include "global.h"
#include "timer.h"
#include "analise.h"
#include "ssp.h"
#include "i2c.h"
#include "time.h"
#include "fsm_master.h"


//using namespace std;
Master_FSM::Master_FSM(void)
{		
		//InitTimer(0,250);
		//FSM_START(); // estado 0, certo? Isso, esse � o de iniciliza��o, s� vai passar uma vez, tah
}

void Master_FSM::FSM_START(void)
{
		
			// ai vem pra c� Isso ai Hoje n�s s� temos o estado de leds/alarmes, mas no futuro teremos v�rios estados
	//init_timer_alarm.conta_timer_alarme();
		//init_timer_alarm.timer_alarme();
	//Leds.ECG_Alta();
	//Leds.BAT_OK_Ligado();
	Leds.FSM_LED();
		//Leds.ON_BAT_Media(); //init_timer_alarm
		//Leds.BAT_OK_Ligado();
}


