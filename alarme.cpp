#include "alarme.h"

Alarm::Alarm(void){}
	
void Alarm::set_flag_tec_alarm_ECG(unsigned short int flag_tec_alarm_ECG)
	{
		this->flag_tec_alarm_ECG = flag_tec_alarm_ECG;
	}
	
	
void set_flag_tec_alarm_SPO2(unsigned short int);
void set_flag_tec_alarm_ENF(unsigned short int);
void set_flag_tec_alarm_BAT(unsigned short int);
void set_flag_phy_alarm_ECG(unsigned short int);
void set_flag_phy_alarm_SPO2(unsigned short int);
void set_flag_tec_alarm(unsigned short int);
void set_flag_phy_alarm(unsigned short int);
void set_update_enf(unsigned short int);