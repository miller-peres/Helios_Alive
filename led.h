
		
	  enum LEDstate
	{
			CONFIG,
			LIGA_LED,
			DESL_LED,
	};

class Led
{
	
	public:
		Led(void);
		unsigned short int led_on_off;
		unsigned short int Cycle_2;
		unsigned short int Cycle;
		unsigned short int state_led;
		unsigned short int Reset_cycle;
		unsigned short int TIME_INT;
		unsigned  int tick;
		unsigned short int flag_tec_alarm_ECG;
		unsigned short int flag_tec_alarm_SPO2;
		unsigned short int flag_tec_alarm_ENF;
		unsigned short int flag_tec_alarm_BAT;
		unsigned short int flag_phy_alarm_ECG;
		unsigned short int flag_phy_alarm_SPO2;
		unsigned short int flag_tec_alarm;
		unsigned short int flag_phy_alarm;
		
		void FSM_LED(void);
		
	
};

