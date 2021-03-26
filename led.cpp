#include "type.h"
#include "irq.h"
#include "time.h"
#include "serial.h"
#include "lpc21xx.h"
#include "global.h"
#include "timer.h"
#include "analise.h"
#include "ssp.h"
#include "i2c.h"
#include "led.h"

#define BUZZER    				P0_7

enum STATE_LED_FSM
{
	IDLE = 0,
	DEFINE_ALARMS_PRIORITY,
	TECHNICAL_ALARM,
	TEC_WAIT_FAST_CYCLE,
	TEC_WAIT_SLOW_CYCLE,
	PHYSIOLOGICAL_ALARM,
	PHY_WAIT_FAST_CYCLE,
	PHY_WAIT_MID_CYCLE,
	PHY_WAIT_SLOW_CYCLE,
	TIMER_ZERO,
};

Led::Led(void){}

void Led::FSM_LED(Alarm General_Alarm) 
{
	timerseg++;
	switch (state_led)
	{
		case IDLE:
			timerseg = 0;	
			tick = timerseg;
			Cycle = 3;
			tick = 0;
			led_on_off = 0;
			timer_zero = 0;
			TIME_INT = 1800;
			state_led = DEFINE_ALARMS_PRIORITY;
		break;
			
		case DEFINE_ALARMS_PRIORITY:	
			timerseg++;
				
			if((timerseg % 2 == 0)  && (General_Alarm.get_flag_tec_alarm_BAT() == 0))
			{				
				IO0SET |= LED_VM_AM;
				IO0SET |= LED_ON_BAT;
			}	
			
			else 
			{
				IO0CLR |= LED_ON_BAT;
			}

				
			if ((General_Alarm.get_flag_tec_alarm() == 1) && (General_Alarm.get_flag_phy_alarm() == 1))
			{
				state_led = PHYSIOLOGICAL_ALARM;
			}
			
			if (General_Alarm.get_flag_phy_alarm() == 1)
			{
				state_led = PHYSIOLOGICAL_ALARM;
			}	
			
			if (General_Alarm.get_flag_tec_alarm() == 1)
			{
				state_led = TECHNICAL_ALARM;
			}
			
			if ((General_Alarm.get_flag_tec_alarm() == 0) && (General_Alarm.get_flag_phy_alarm() == 0))
			{
				state_led = TIMER_ZERO;
			}
		break;
			
		// ALARMES TECNICOS
		case TECHNICAL_ALARM:	
		if 	(timer_zero == 0)
		{
			timerseg = 0;
			timer_zero = 1;
		}
		
		if (timer_zero == 1)
		{
			IO0CLR |= LED_VM_AM;
//			IO0SET |= LED_SPO2;
//			IO0SET |= LED_ENF;
//			IO0SET |= LED_ECG;
//			IO0SET |= LED_ON_BAT;
			
			if ((timerseg % 2 != 0)  && (General_Alarm.get_flag_tec_alarm_BAT() == 0))
			{
				// LIGA O LED ESPECIFICO DO ALARME TECNICO
				if (General_Alarm.get_status_nurse() == true) 
				{					
					IO0SET |= LED_ECG;
					IO0SET |= LED_SPO2;
					IO0SET |= LED_ON_BAT;
					IO0CLR |= LED_ENF;
					IO0SET |= BUZZER;
				}
				if (General_Alarm.get_flag_tec_alarm_BAT() == 1) 
				{					
					IO0CLR |= LED_ON_BAT;
				}
				if (General_Alarm.get_flag_tec_alarm_ECG() == 1) 
				{
					IO0CLR |= LED_ECG;
				}
				if (General_Alarm.get_flag_tec_alarm_SPO2() == 1)
				{					
					IO0CLR |= LED_SPO2;
				}
			}
			// LIGA LED EQUIPAMENTO LIGADO SE BATERIA ESTIVER ACIMA DE 6%
			else if ((timerseg % 2 == 0)  && (General_Alarm.get_flag_tec_alarm_BAT() == 0))
			{		
				IO0SET |= LED_ON_BAT;
				IO0CLR |= LED_SPO2;
				IO0CLR |= LED_ECG;
				IO0CLR |= LED_ENF;
				IO0SET |= LED_VM_AM;
			}
			
			if (timerseg >= (tick + 1000))
			{
				state_led = TEC_WAIT_FAST_CYCLE;
				tick = timerseg;
			}
		}
		break;
			
			case TEC_WAIT_FAST_CYCLE:
				IO0SET |= LED_VM_AM;	
				IO0CLR |= LED_SPO2;
				IO0CLR |= LED_ECG;
				IO0CLR|= LED_ENF;
				IO0CLR |= BUZZER;
				
				if((timerseg % 2 == 0)  && (General_Alarm.get_flag_tec_alarm_BAT() == 0)) IO0SET |= LED_ON_BAT;
				else IO0CLR |= LED_ON_BAT;
			
				if (timerseg >= (tick + 1000))
					{
						state_led = DEFINE_ALARMS_PRIORITY;
						tick = timerseg;
						led_on_off++;
				if (led_on_off >= 3)
					{
						state_led = TEC_WAIT_SLOW_CYCLE;
					}
					}
		
			break;
			
			case TEC_WAIT_SLOW_CYCLE:
				if((timerseg % 2 == 0)  && (General_Alarm.get_flag_tec_alarm_BAT() == 0)) IO0SET |= LED_ON_BAT; // COORIGE BUG DE LUMINOSIDADE LED VERDE
				else IO0CLR |= LED_ON_BAT;
				
				if (timerseg >= (tick + 20000))
					{
						led_on_off = 0;
						timerseg = 0;
						tick = timerseg;
						state_led = DEFINE_ALARMS_PRIORITY;
					}
							
			break;
			
			// ALARMES FISIOLOGICOS
			case PHYSIOLOGICAL_ALARM:
			// LIGA LED EQUIPAMENTO LIGADO SE BATERIA ESTIVER ACIMA DE 6%
			if((timerseg % 2 != 0)  && (General_Alarm.get_flag_tec_alarm_BAT() == 0))
				{	
					IO0SET |= LED_ON_BAT;
					IO0SET |= LED_VM_AM;
				}

			
			// LIGA O LED ESPECIFICO DO ALARME FISIOL�GICO
			if (General_Alarm.get_flag_phy_alarm_ECG() == 1) 
			{
				IO0SET|= LED_ECG;
				IO0SET |= BUZZER;
			}
			if (General_Alarm.get_flag_phy_alarm_SPO2() == 1)
			{				
				IO0SET |= LED_SPO2;
				IO0SET |= BUZZER;
			}
			
			
			if (timerseg >= (tick + 500))
				{
					tick = timerseg;
					state_led = PHY_WAIT_FAST_CYCLE;
				}
			break;
			
			case PHY_WAIT_FAST_CYCLE:
				IO0SET |= LED_VM_AM;
				IO0CLR |= LED_SPO2;
				IO0CLR |= LED_ECG;
				IO0CLR |= BUZZER;
			
			
			if (timerseg >= (tick + 500))
				{
					tick = timerseg;
					led_on_off++;
					state_led = PHYSIOLOGICAL_ALARM;
			if (led_on_off == Cycle)
				{	
					state_led = PHY_WAIT_MID_CYCLE;
				if (Cycle_2 == 0)
					{	
						Cycle_2++;
						Cycle = 2;
						TIME_INT = 1500;
					}
					else 
					{
						Cycle = 3;
						Cycle_2 = 0;
						TIME_INT = 4000;
					}
				}
				}
			break;
			
			case PHY_WAIT_MID_CYCLE:
				
				if (timerseg >= (tick + TIME_INT))
					{	
						tick = timerseg;
						led_on_off = 0;
						state_led = PHYSIOLOGICAL_ALARM;
						Reset_cycle++;
					if (Reset_cycle == 4)
						{
							Reset_cycle = 0;
							state_led = PHY_WAIT_SLOW_CYCLE;
						}
					}
			break;
			
			case PHY_WAIT_SLOW_CYCLE:
				
				if (timerseg >= (tick + 10000))
					{	
						state_led = DEFINE_ALARMS_PRIORITY;
						led_on_off = 0;
						tick = timerseg;
					}
			break;
			
			case TIMER_ZERO:

			if (timerseg > 20000) timerseg = 0;
			
			timer_zero = 0;
			state_led = DEFINE_ALARMS_PRIORITY;
			break;
			
			default:
			break;
    }					
}
