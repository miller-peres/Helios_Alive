#include "type.h"
#include "serial.h"
#include "lpc21xx.h"
#include "global.h"
#include "timer.h"
#include "time.h"
#include "fsm_master.h"

Master_FSM::Master_FSM(void){}
	
void Master_FSM::FSM_START(void)
{
	Button_Push.FSM_button(); 
	General_Alarm.Alarm_FSM(Button_Push.get_nurse_calling());
	Leds.FSM_LED(General_Alarm);
}


