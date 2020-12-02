#include "alarme.h"
#include "type.h"
#include "irq.h"
#include "time.h"
#include "serial.h"
#include "lpc21xx.h"
#include "global.h"
#include "timer.h"

Alarme::Alarme(void)
{
		//contadores alarme alta prioridade
		unsigned short int flag_timer_50ms = 0;
		unsigned short int flag_timer_400ms = 0;
		unsigned short int flag_timer_3000ms = 0;
		//contadores alarme media prioridade
		unsigned short int flag_timer_125ms = 0;
		unsigned short int flag_timer_1000ms = 0;
		unsigned short int flag_timer_5000ms = 0;
		//contadores alarme alta prioridade
		unsigned int timer_alarme_media_50 = 0;
		unsigned int timer_alarme_media_400 = 0;
		unsigned int timer_alarme_media_3000 = 0;
		//contadores alarme media prioridade
		unsigned int timer_alarme_media_125 = 0;
		unsigned int timer_alarme_media_1000 = 0;
		unsigned int timer_alarme_media_5000 = 0;
}

unsigned short int Alarme::get_flag_timer_50ms(void)
{
		return flag_timer_50ms;
}

unsigned short int Alarme::get_flag_timer_400ms(void)
{
		return flag_timer_400ms;
}

unsigned short int Alarme::get_flag_timer_3000ms(void)
{
		return flag_timer_3000ms;
}

unsigned short int Alarme::get_flag_timer_125ms(void)
{
		return flag_timer_125ms;
}

unsigned short int Alarme::get_flag_timer_1000ms(void)
{
		return flag_timer_1000ms;
}

unsigned short int Alarme::get_flag_timer_5000ms(void)
{
		return flag_timer_5000ms;
}

void Alarme::timer_alarme(void)
{
	/*ALARMED ALTA PRIORIDADES - TEMPOS CONFORME 60601-1-8*/
	
	/*timer 50ms*/
	if (timer_alarme_media_50 < 501)
		{
			flag_timer_50ms = 1; 
			IO0CLR |= BUZZER;
		}
	if (timer_alarme_media_50 > 500)
		{
			flag_timer_50ms = 2; 
			IO0SET |= BUZZER;
		}
	if (timer_alarme_media_50 > 1000)
		{
			flag_timer_50ms = 0;
			timer_alarme_media_50 = 0;
		}

	/*timer 400ms*/
	if (timer_alarme_media_400 == 3000)flag_timer_400ms = 1, timer_alarme_media_400 = 0;
	else flag_timer_400ms = 0;
	
	/*timer 3000ms*/
	if (timer_alarme_media_3000 == 9000)flag_timer_3000ms = 1, timer_alarme_media_3000 = 0;
	else flag_timer_3000ms = 0;
	
	/*ALARMED MEDIA PRIORIDADES - TEMPOS CONFORME 60601-1-8*/
	
	/*timer 125ms*/
	if (timer_alarme_media_125 == 700)flag_timer_125ms = 1, timer_alarme_media_125 = 0;
	else flag_timer_125ms = 0;
	
	/*timer 400ms*/
	if (timer_alarme_media_1000 == 1200)flag_timer_1000ms = 1, timer_alarme_media_1000 = 0;
	else flag_timer_1000ms = 0;
	
	/*timer 3000ms*/
	if (timer_alarme_media_5000 == 15000)flag_timer_5000ms = 1, timer_alarme_media_5000 = 0;
	else flag_timer_5000ms = 0;
	
}

void Alarme::conta_timer_alarme(void)
{
		timer_alarme_media_50++;
		timer_alarme_media_400++;
		timer_alarme_media_3000++;
		timer_alarme_media_125++;
		timer_alarme_media_1000++;
		timer_alarme_media_5000++;
}