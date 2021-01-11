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
		//unsigned short int update_enf;
		bool update_enf;
		bool flag_status_nurse;
	
};


//bloco sets inativos

//	.h
//		void set_flag_tec_alarm_ECG(unsigned short int);
//		void set_flag_tec_alarm_SPO2(unsigned short int);
//		void set_flag_tec_alarm_ENF(unsigned short int);
//		void set_flag_tec_alarm_BAT(unsigned short int);
//		void set_flag_phy_alarm_ECG(unsigned short int);
//		void set_flag_phy_alarm_SPO2(unsigned short int);
//		void set_flag_tec_alarm(unsigned short int);
//		void set_flag_phy_alarm(unsigned short int);
//		void set_update_enf(bool);
//		void set_status_nurse(unsigned char);

//  .cpp

//void Alarm::set_flag_tec_alarm_ECG(unsigned short int flag_tec_alarm_ECG)
//{
//	this->flag_tec_alarm_ECG = flag_tec_alarm_ECG;
//}
//	
//void Alarm::set_flag_tec_alarm_SPO2(unsigned short int flag_tec_alarm_SPO2)
//{
//	this->flag_tec_alarm_SPO2 = flag_tec_alarm_SPO2;
//}

//void Alarm::set_flag_tec_alarm_BAT(unsigned short int flag_tec_alarm_BAT)
//{
//	this->flag_tec_alarm_BAT = flag_tec_alarm_BAT;
//}
//	
//void Alarm::set_flag_phy_alarm_ECG(unsigned short int flag_phy_alarm_ECG)
//{
//	this->flag_phy_alarm_ECG = flag_phy_alarm_ECG;
//}

//void Alarm::set_flag_phy_alarm_SPO2(unsigned short int flag_phy_alarm_SPO2)
//{
//	this->flag_phy_alarm_SPO2 = flag_phy_alarm_SPO2;
//}

//void Alarm::set_flag_tec_alarm(unsigned short int flag_tec_alarm)
//{
//	this->flag_tec_alarm = flag_tec_alarm;
//}

//void Alarm::set_flag_phy_alarm(unsigned short int flag_phy_alarm)
//{
//	this->flag_phy_alarm = flag_phy_alarm;
//}

//void Alarm::set_update_enf(bool update_enf)
//{
//	this->update_enf = &update_enf;
//}

//void Alarm::set_status_nurse(unsigned char flag_status_nurse)
//{
//	this->flag_status_nurse = flag_status_nurse;
//}