#include "botao.h"

class Alarm
{
	public:
		Alarm(void);
	
		void Alarm_FSM(bool);
	
		bool get_flag_tec_alarm_ECG(void);
		bool get_flag_tec_alarm_SPO2(void);
		bool get_flag_tec_alarm_ENF(void);
		bool get_flag_tec_alarm_BAT(void);
		bool get_flag_phy_alarm_ECG(void);
		bool get_flag_phy_alarm_SPO2(void);
		bool get_flag_tec_alarm(void);
		bool get_flag_phy_alarm(void);
		bool get_status_nurse(void);
	
	private:
		bool flag_tec_alarm_ECG;
		bool flag_tec_alarm_SPO2;
		bool flag_tec_alarm_ENF;
		bool flag_tec_alarm_BAT;
		bool flag_phy_alarm_ECG;
		bool flag_phy_alarm_SPO2;
		bool flag_tec_alarm;
		bool flag_phy_alarm;
		bool update_enf;
		bool flag_status_nurse;
		unsigned short int state_alarm;
	
};
