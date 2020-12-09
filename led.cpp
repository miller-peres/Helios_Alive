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

Led::Led(void){}

void Led::FSM_LED(void)
{
		switch (state_led)
		{
			case 0:
				//timerseg++;	
				Led LED_OBJ;
				tick = timerseg;
				Cycle = 3;
				TIME_INT = 1800;
				
			//FLAGS DE TESTE MOMENTANEO
				flag_tec_alarm = 1; // TESTE
				flag_phy_alarm = 0;
				flag_tec_alarm_ECG = 1;
				flag_tec_alarm_SPO2 = 1;
				flag_tec_alarm_BAT = 0;
				flag_phy_alarm_SPO2 = 0;
				flag_phy_alarm_ECG = 0;
				
				state_led = 1;

			break;
			
			case 1:
				// DEFINE PRIORIDADE PARA ALARME FISIOLÓGICO
				if ((flag_tec_alarm == 1) && (flag_phy_alarm == 1))
				{
					state_led = 5;
				}
				
				if (flag_tec_alarm == 1)
				{
					state_led = 2;
				}
				
				if (flag_phy_alarm == 1)
				{
					state_led = 5;
				}
			break;
				
				// ALARMES TÉCNICOS
				case 2:
					
					if (timerseg % 2 == 0)
					{
					IO0SET |= DER_1;
					IO0SET |= LED_SPO2;
					IO0SET |= LED_ENF;
					IO0SET |= LED_ECG;
					IO0SET |= BUZZER;
					IO0SET |= LED_ON_BAT;
					
				
				// LIGA O LED ESPECIFICO DO ALARME TECNICO
				if (flag_tec_alarm_BAT == 1)  IO0CLR |= LED_ON_BAT;
				if (flag_tec_alarm_ECG == 1)  IO0CLR |= LED_ECG;
				if (flag_tec_alarm_SPO2 == 1) IO0CLR |= LED_SPO2;
				if (flag_tec_alarm_ENF == 1)  IO0CLR |= LED_ENF;
						
				
					}
					// LIGA LED EQUIPAMENTO LIGADO SE BATERIA ESTIVER ACIMA DE 6%
					if ((timerseg % 2 != 0)  && (flag_tec_alarm_BAT == 0))
					{
						
						IO0SET |= LED_ON_BAT;
						IO0SET |= BUZZER;
						IO0CLR |= LED_SPO2;
						IO0CLR |= LED_ECG;
						IO0CLR|= LED_ENF;
						IO0CLR |= DER_1;
						
					}
				
				if (timerseg >= (tick + 1000))
				{
					state_led = 3;
					tick = timerseg;
				}
				break;
				
				case 3:
					IO0CLR |= LED_SPO2;
					IO0CLR |= LED_ECG;
					IO0CLR|= LED_ENF;
					IO0CLR |= DER_1;
					IO0CLR |= BUZZER;
					
					if((timerseg % 2 != 0)  && (flag_tec_alarm_BAT == 0)) IO0SET |= LED_ON_BAT;
					else IO0CLR |= LED_ON_BAT;
				
				if (timerseg >= (tick + 1000))
				{
					state_led = 1;
					tick = timerseg;
					led_on_off++;
					if (led_on_off == 3)
					{
						state_led = 4;
					}
				}
			
				break;
				
				case 4:
					if((timerseg % 2 != 0)  && (flag_tec_alarm_BAT == 0)) IO0SET |= LED_ON_BAT; // COORIGE BUG DE LUMINOSIDADE LED VERDE
					else IO0CLR |= LED_ON_BAT;
					
					if (timerseg >= (tick + 20000))
				{
					state_led = 1;
					led_on_off = 0;
					tick = timerseg;
					
				}
								
				break;
				
				// ALARMES FISIOLÓGICOS
				case 5:
				
				// LIGA LED EQUIPAMENTO LIGADO SE BATERIA ESTIVER ACIMA DE 6%
				if((timerseg % 2 != 0)  && (flag_tec_alarm_BAT == 0))
				{	
					IO0SET |= LED_ON_BAT;
					IO0CLR |= DER_1;
				}
				
					IO0CLR |= DER_1;
					IO0SET |= BUZZER;
					
				
				// LIGA O LED ESPECIFICO DO ALARME FISIOLÓGICO
				if (flag_phy_alarm_ECG == 1)  IO0SET|= LED_ECG;
				if (flag_phy_alarm_SPO2 == 1) IO0SET |= LED_SPO2;
				
				
				if (timerseg >= (tick + 500))
				{
					tick = timerseg;
					state_led = 6;
				}
				break;
				
				case 6:
					
					IO0CLR |= DER_1;
					IO0CLR |= LED_SPO2;
					IO0CLR |= LED_ECG;
					IO0CLR |= BUZZER;
				
				
				if (timerseg >= (tick + 500))
				{
					tick = timerseg;
					led_on_off++;
					state_led = 5;
					if (led_on_off == Cycle)
					{	
						state_led = 7;
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
				case 7:
					
					if (timerseg >= (tick + TIME_INT))
					{	
						tick = timerseg;
						led_on_off = 0;
						state_led = 5;
						Reset_cycle++;
						if (Reset_cycle == 4)
						{
							Reset_cycle = 0;
							state_led = 8;
						}
					}
				break;
				case 8:
					
				if (timerseg >= (tick + 10000))
				{	
					state_led = 1;
					led_on_off = 0;
					tick = timerseg;
				}
				break;
				
				default:
				break;
    }					
}