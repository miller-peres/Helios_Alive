#include <string.h>
#include <stdio.h>
#include <math.h>
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
#include "main.h"


using namespace std;

class Led
{
	public:
	Led(void);
	
	void ECG_Alta(void);
	void ECG_Media(void);
	
	void SPO2_Alta(void);
	void SPO2_Media(void);
	
	void BAT_OK(void);
	void BAT_Media(void);
	
	void ENF_Alta(void);
	void ENF_Media(void);
			
};

