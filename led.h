#include "alarm.h"

class Led
{
	
	public:
		Led(void);
		unsigned short int led_on_off;
		unsigned short int Cycle_2;
		unsigned short int Cycle;
		//unsigned short int state_led;
		unsigned short int Reset_cycle;
		unsigned short int TIME_INT;
		unsigned  int tick;
		unsigned  int time_green_led;
		unsigned char state_led;
		bool timer_zero;
		void FSM_LED(Alarm);

};

