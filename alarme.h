
class Alarm
{
	public:
		void set_flag_tec_alarm_ECG(unsigned short int);
		void set_flag_tec_alarm_SPO2(unsigned short int);
		void set_flag_tec_alarm_ENF(unsigned short int);
		void set_flag_tec_alarm_BAT(unsigned short int);
		void set_flag_phy_alarm_ECG(unsigned short int);
		void set_flag_phy_alarm_SPO2(unsigned short int);
		void set_flag_tec_alarm(unsigned short int);
		void set_flag_phy_alarm(unsigned short int);
		void set_update_enf(unsigned short int);
	
		unsigned short int get_flag_tec_alarm_ECG(void);
		unsigned short int get_flag_tec_alarm_SPO2(void);
		unsigned short int get_flag_tec_alarm_ENF(void);
		unsigned short int get_flag_tec_alarm_BAT(void);
		unsigned short int get_flag_phy_alarm_ECG(void);
		unsigned short int get_flag_phy_alarm_SPO2(void);
		unsigned short int get_flag_tec_alarm(void);
		unsigned short int get_flag_phy_alarm(void);
		unsigned short int get_update_enf(void);
	
	private:
		unsigned short int flag_tec_alarm_ECG;
		unsigned short int flag_tec_alarm_SPO2;
		unsigned short int flag_tec_alarm_ENF;
		unsigned short int flag_tec_alarm_BAT;
		unsigned short int flag_phy_alarm_ECG;
		unsigned short int flag_phy_alarm_SPO2;
		unsigned short int flag_tec_alarm;
		unsigned short int flag_phy_alarm;
		unsigned short int update_enf;
	
};