#include "type.h"
#include "irq.h"
//#include "time.h"
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
Master_FSM::Master_FSM(void){}

void Master_FSM::FSM_timer(void)
{
		init_conta_timer_alarme.conta_timer_alarme();
		init_timer_alarme.timer_alarme();
		//Leds.ON_BAT_Media();
		
}


