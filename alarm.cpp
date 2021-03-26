#include "alarm.h"

enum STATE_ALARM
{
	IDLE = 0,
	NURSE_ALARM,
	ECG_ALARM,
	SPO2_ALARM,
};

Alarm::Alarm(void){}

void Alarm::Alarm_FSM(bool nurse_calling) 
{
	switch (state_alarm)
	{
		case IDLE: 
			//FLAGS DE TESTE MOMENTANEO
			//flag_tec_alarm 		= 1;
			flag_phy_alarm	    = 0;
			flag_tec_alarm_ECG  = 0;
			flag_tec_alarm_SPO2 = 0;
			flag_tec_alarm_BAT  = 0;
			flag_phy_alarm_SPO2 = 0;
			flag_phy_alarm_ECG  = 0;
			state_alarm = NURSE_ALARM;
		break;
		
		case NURSE_ALARM:		
		if (nurse_calling)
		{
			flag_status_nurse = true;
			flag_tec_alarm 		= 1;	
		}
		else 
		{
			flag_status_nurse = false;
			flag_tec_alarm 		= 0;
		}
		state_alarm = IDLE;
		break;
		
		case ECG_ALARM:
			//INSERIR ROTINA DE ALARMES DE ECG
			break;
		
		case SPO2_ALARM:
			//INSERIR ROTINA DE ALARMES DE SPO2
			break;
		
		default:
			break;
}
}

//*************************** GETS **************************************

bool Alarm::get_flag_tec_alarm_ECG(void)
{
	return flag_tec_alarm_ECG;
}

bool Alarm::get_flag_tec_alarm_SPO2(void)
{
	return flag_tec_alarm_SPO2;
}

bool Alarm::get_flag_tec_alarm_ENF(void)
{
	return flag_tec_alarm_ENF;
}

bool Alarm::get_flag_tec_alarm_BAT(void)
{
	return flag_tec_alarm_BAT;
}

bool Alarm::get_flag_phy_alarm_ECG(void)
{
	return flag_phy_alarm_ECG;
}

bool Alarm::get_flag_phy_alarm_SPO2(void)
{
	return flag_phy_alarm_SPO2;
}

bool Alarm::get_flag_tec_alarm(void)
{
	return flag_tec_alarm;
}

bool Alarm::get_flag_phy_alarm(void)
{
	return flag_phy_alarm;
}

bool Alarm::get_status_nurse(void)
{
	return flag_status_nurse;
}
