#include "led.h"

class Master_FSM
{
	
	public:
		Master_FSM(void);
		Alarme init_timer_alarme; // Obj alarme
		Alarme init_conta_timer_alarme; // Obj alarme
		Led Leds; // obj led
		Alarme alarme_led;

	void FSM_timer(void);
	
};