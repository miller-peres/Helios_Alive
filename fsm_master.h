#include "led.h"
//#include "zigbee.h"

class Master_FSM
{
	public:
		Master_FSM(void);
		Led Leds; // obj led
		Button Button_Push;
		Alarm General_Alarm;
		//Zigbee Init_zigbee;
		//Spo2 Init_spo2;
		void FSM_START();
		int a;
};
