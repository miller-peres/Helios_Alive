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

//#include "fsm_master.h"


Led::Led(void){}

// PARA ECG
void Led::ECG_Alta_Ligado(void) 
{
	
	IO0CLR |= DER_1;
	IO0SET |= LED_ECG;
	
	IO0CLR |= LED_SPO2;
	IO0CLR |= LED_ENF;
	IO0CLR |= LED_ON_BAT;
			
}

void Led::ECG_Media_Ligado(void) 
{
	IO0SET |= DER_1;
	IO0CLR |= LED_ECG;
	
	IO0SET |= LED_SPO2;
	IO0SET |= LED_ENF;
	IO0SET |= LED_ON_BAT;
		
}

// PARA SPO2
void Led::SPO2_Alta_Ligado(void) 
{
	IO0CLR |= DER_1;
	IO0SET |= LED_SPO2;
	
	IO0CLR |= LED_ECG;
	IO0CLR |= LED_ENF;
	IO0CLR |= LED_ON_BAT;
}

void Led::SPO2_Media_Ligado(void) 
{
	IO0SET |= DER_1;
	IO0CLR |= LED_SPO2;
	
	IO0SET |= LED_ECG;
	IO0SET |= LED_ENF;
	IO0SET |= LED_ON_BAT;
		
}



void Led::BAT_Media_Ligado(void) 
{
	IO0SET |= DER_1;
	IO0CLR |= LED_ON_BAT;
	
		
}

//PARA ENF
void Led::ENF_Alta_Ligado(void) 
{
	IO0CLR |= DER_1;
	IO0SET |= LED_ENF;
	
	IO0CLR |= LED_SPO2;
	IO0CLR |= LED_ECG;
	IO0CLR |= LED_ON_BAT;
}

void Led::ENF_Media_Ligado(void) 
{
	IO0SET |= DER_1;
	IO0CLR |= LED_ENF;
	
	IO0SET |= LED_SPO2;
	IO0SET |= LED_ECG;
	IO0SET |= LED_ON_BAT;
		
}

void Led::Desliga(void) 
{
	IO0CLR |= DER_1;
	IO0CLR |= LED_ENF;
	
	IO0CLR |= LED_SPO2;
	IO0CLR |= LED_ECG;
	IO0CLR |= LED_ON_BAT;
		
}

void Led::ECG_Alta(void) 
{
	
	IO0CLR |= LED_ECG;
	if ((timerseg > 0) && (timerseg < 400))
	{
		IO0CLR |= DER_1;
		IO0SET |= LED_ECG;
	}
			if ((timerseg > 1000) && (timerseg < 1500))
	{
		IO0CLR |= DER_1;
		IO0SET |= LED_ECG;
	}
	
	if ((timerseg > 2000) && (timerseg < 2500))
	{
		IO0CLR |= DER_1;
		IO0SET |= LED_ECG;
	}
	
	if ((timerseg > 5500) && (timerseg < 6000))
	{
		IO0CLR |= DER_1;
		IO0SET |= LED_ECG;
	}
	
		if ((timerseg > 6500) && (timerseg < 7000))
	{
		IO0CLR |= DER_1;
		IO0SET |= LED_ECG;
	}
	
	if ((timerseg > 10000) && (timerseg < 10500))
	{
		IO0CLR |= DER_1;
		IO0SET |= LED_ECG;
	}
	
	if ((timerseg > 11000) && (timerseg < 11500))
	{
		IO0CLR |= DER_1;
		IO0SET |= LED_ECG;
	 }
	
	if ((timerseg > 12000) && (timerseg < 12500))
	{
		IO0CLR |= DER_1;
		IO0SET |= LED_ECG;
	 }
	
	if ((timerseg > 15500) && (timerseg < 16000))
	{
		IO0CLR |= DER_1;
		IO0SET |= LED_ECG;
	  }
	
	if ((timerseg > 16500) && (timerseg < 17000))
	{
		IO0CLR |= DER_1;
		IO0SET |= LED_ECG;
  }
		if (timerseg > 26000)timerseg = 0;
	}

void Led::ECG_Media(void) 
{
		IO0SET |= LED_ECG;
	
	if (timerseg == 1)
	{

		IO0SET |= DER_1;
		IO0CLR |= LED_ECG;
		
		IO0SET |= LED_ENF;
		IO0SET |= LED_ON_BAT;
	  IO0SET |= LED_SPO2;
		
	}
			
	if ((timerseg > 1) && (timerseg < 600))
	{
		IO0SET |= DER_1;
		IO0CLR |= LED_ECG;	
		
		IO0SET |= LED_ENF;
		IO0SET |= LED_ON_BAT;
		IO0SET |= LED_SPO2;
						
	}
	
	if ((timerseg > 1600) && (timerseg < 2200))
	{
		IO0SET |= DER_1;
		IO0CLR |= LED_ECG;
		
		IO0SET |= LED_ENF;
		IO0SET |= LED_ON_BAT;
		IO0SET |= LED_SPO2;
	
	}
	
	if ((timerseg > 3200) && (timerseg < 3800))
	{
		IO0SET |= DER_1;
		IO0CLR |= LED_ECG;
		
		IO0SET |= LED_ENF;
		IO0SET |= LED_ON_BAT;
		IO0SET |= LED_SPO2;
	}
	
	if (timerseg > 18800)timerseg = 0;
}
	


void Led::SPO2_Alta(void) 
{
	IO0CLR |= LED_SPO2;
	
	if ((timerseg > 0) && (timerseg < 400))
	{
		IO0CLR |= DER_1;
		IO0SET |= LED_SPO2;
	}
			if ((timerseg > 1000) && (timerseg < 1500))
	{
		IO0CLR |= DER_1;
		IO0SET |= LED_SPO2;
	}
	
	if ((timerseg > 2000) && (timerseg < 2500))
	{
		IO0CLR |= DER_1;
		IO0SET |= LED_SPO2;
	}
	
	if ((timerseg > 5500) && (timerseg < 6000))
	{
		IO0CLR |= DER_1;
		IO0SET |= LED_SPO2;
	}
	
		if ((timerseg > 6500) && (timerseg < 7000))
	{
		IO0CLR |= DER_1;
		IO0SET |= LED_SPO2;
	}
	
	if ((timerseg > 10000) && (timerseg < 10500))
	{
		IO0CLR |= DER_1;
		IO0SET |= LED_SPO2;
	}
	
	if ((timerseg > 11000) && (timerseg < 11500))
	{
		IO0CLR |= DER_1;
		IO0SET |= LED_SPO2;
	}
	
	if ((timerseg > 12000) && (timerseg < 12500))
	{
		IO0CLR |= DER_1;
		IO0SET |= LED_SPO2;
	}
	
	if ((timerseg > 15500) && (timerseg < 16000))
	{
		IO0CLR |= DER_1;
		IO0SET |= LED_SPO2;
	  }
	
	if ((timerseg > 16500) && (timerseg < 17000))
	{
		IO0CLR |= DER_1;
		IO0SET |= LED_SPO2;
  }
		if (timerseg > 26000)timerseg = 0;
	}
	
	void Led::SPO2_Media(void) 
{
		IO0CLR |= DER_1;	
		//IO0SET |= LED_ON_BAT;	
		//IO0SET |= LED_ECG;
		//IO0SET |= LED_SPO2;
		//IO0SET |= LED_ENF;	
	
	if (timerseg == 1)
	{
		IO0SET |= DER_1;
		IO0CLR |= LED_SPO2;
		IO0SET |= BUZZER;
		
		IO0SET |= LED_ENF;	
	}
	
	if ((timerseg > 1) && (timerseg < 600))
	{
		IO0SET |= DER_1;
		IO0CLR |= LED_SPO2;
		IO0SET |= BUZZER;
		
		IO0SET |= LED_ENF;	
	}
	
	if ((timerseg > 1600) && (timerseg < 2200))
	{
		IO0SET |= DER_1;
		IO0CLR |= LED_SPO2;
		IO0SET |= BUZZER;
		
		IO0SET |= LED_ENF;	
	}
	
	if ((timerseg > 3200) && (timerseg < 3800))
	{
			IO0SET |= DER_1;
			IO0CLR |= LED_SPO2;			
		  IO0SET |= BUZZER;
		
			IO0SET |= LED_ENF;	
	}
	
	if (timerseg > 18800){timerseg = 0;}
	
}


void Led::ENF_Media(void) 
{
		IO0SET |= LED_ENF;
	
	if (timerseg == 1)
	{
		
		IO0SET |= DER_1;
		IO0CLR |= LED_ENF;
		
		IO0SET |= LED_ECG;
		IO0SET |= LED_ON_BAT;
		IO0SET |= LED_SPO2;
		
	}
	
	
	if ((timerseg > 0) && (timerseg < 600))
	{
		
		IO0SET |= DER_1;
		IO0CLR |= LED_ENF;
			
		IO0SET |= LED_ECG;
		IO0SET |= LED_ON_BAT;
		IO0SET |= LED_SPO2;	
			
	}
	
	if ((timerseg > 1600) && (timerseg < 2200))
	{
	
		IO0SET |= DER_1;
		IO0CLR |= LED_ENF;
			
		IO0SET |= LED_ECG;
		IO0SET |= LED_ON_BAT;
		IO0SET |= LED_SPO2;	
		
	}
	
	if ((timerseg > 3200) && (timerseg < 3800))
	{
		IO0SET |= DER_1;
		IO0CLR |= LED_ENF;
	  		
		IO0SET |= LED_ECG;
		IO0SET |= LED_ON_BAT;
		IO0SET |= LED_SPO2;	
	}
	if (timerseg > 18800)timerseg = 0;
}

void Led::ON_BAT_Media(void) 
{		
		IO0CLR |= DER_1;
		//IO0SET |= LED_SPO2;
		//IO0SET |= LED_ECG;
		//IO0SET |= LED_ENF;	
		//IO0SET |= LED_ON_BAT;
	
	if (alarme_led.get_flag_timer_125ms() == 1)
	{
		IO0SET |= DER_1;
		IO0CLR |= LED_ON_BAT;
		IO0SET |= BUZZER;
		
		IO0SET |= LED_ENF;	
	}
	

	if (alarme_led.get_flag_timer_125ms() == 1)
	{
			IO0SET |= DER_1;
			IO0CLR |= LED_ON_BAT;
			IO0SET |= BUZZER;
	}	
			
	if (alarme_led.get_flag_timer_125ms() == 1)
	{
			IO0SET |= DER_1;
			IO0CLR |= LED_ON_BAT;
			IO0SET |= BUZZER;
		
			IO0SET |= LED_ENF;	
	}
	
	if (alarme_led.get_flag_timer_5000ms() == 1)timerseg = 0;
		
}

//PARA BATERIA
void Led::BAT_OK_Ligado(void) 
{
			IO0CLR |= DER_1;
			IO0SET |= LED_ON_BAT;
			IO0CLR |= LED_SPO2;
			IO0CLR |= LED_ENF;
			IO0CLR |= LED_ECG;
}