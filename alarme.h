
class Alarme
{
	public:
		Alarme(void);
		unsigned short int get_flag_timer_50ms(void);
		unsigned short int get_flag_timer_400ms(void);
		unsigned short int get_flag_timer_3000ms(void);
		unsigned short int get_flag_timer_125ms(void);
		unsigned short int get_flag_timer_1000ms(void);
		unsigned short int get_flag_timer_5000ms(void);
	
		//contadores alarme alta prioridade
		unsigned int timer_alarme_media_50;
		unsigned int timer_alarme_media_400;
		unsigned int timer_alarme_media_3000;
		//contadores alarme media prioridade
		unsigned int timer_alarme_media_125;
		unsigned int timer_alarme_media_1000;
		unsigned int timer_alarme_media_5000;	
		
		void timer_alarme(void);
		void conta_timer_alarme(void);
	private:
		//contadores alarme alta prioridade
		unsigned short int flag_timer_50ms;
		unsigned short int flag_timer_400ms;
		unsigned short int flag_timer_3000ms;
		//contadores alarme media prioridade
		unsigned short int flag_timer_125ms;
		unsigned short int flag_timer_1000ms;
		unsigned short int flag_timer_5000ms;	
};