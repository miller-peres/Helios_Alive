#include "led.h"

class Master_FSM
{
	public:
		
		Master_FSM(void);
		Led Leds; // obj led
		Button Button_Push;
		Alarm General_Alarm;
		void FSM_START();
		int controller;
};