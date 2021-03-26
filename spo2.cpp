#include "spo2.h"
#include "lpc21xx.h"
//#include "irq.h"
#include "global.h"



enum STATE_TREAT_DATA_SPO2_FSM
{
	PROBE_VERIFY = 0,
	PLETH_VALUE,
	SENSOR_CHECK,
	PULSE_RATE,
	SPO2_VALUE,
	SPO2_STATUS,
	GET_REVISION,
	VERIFY_STEP1,
	REVISION_VERIFY,
	VERIFY_STEP2,
	VERIFY_STEP3,
	ASSIGN_DATA,
};

Spo2::Spo2(void)
{
	spo2_alarm_min = 85;
	spo2_alarm_max = 100;
	gMonitoraSpo2 = true;
}

void Spo2::config_COM_spo2(Vic init_VIC_cpy)
{
	port_spo2 = COM1;
	n_spo2 = 8;
	StopBits_spo2 = 1;
	Parity_spo2 = EVEN; 
	bps_spo2 = 19200;
	baud_spo2 = UART_BAUD(bps_spo2);
		
	//Habilita TXD1 e RXD1
	PINSEL0 |= BIT_18 | BIT_16;
	// Define numero de bits de dados
	U1LCR = (n_spo2 == 7 ? BIT_1 : (BIT_1 | BIT_0));
	// Define stop bits...
	U1LCR |= (StopBits_spo2 == 2 ? BIT_2 : 0);
	// Define paridade ...
	U1LCR |= ((Parity_spo2 == EVEN)||(Parity_spo2 == ODD)? BIT_3 : 0);
	U1LCR |= ((Parity_spo2 == EVEN)? BIT_4 : 0);
	U1LCR |= 0x80;

	U1DLL  = baud_spo2;			  
	U1DLM  = (baud_spo2 >> 8);

	U1LCR &= ~(0x80);			
	// Habilita int RDA e RX                                          
	U1IER = BIT_0 | BIT_2;   
if (port_spo2 == COM1) 
{
	while (!(U0LSR & 0x20));
	U1THR = ch;
}

init_VIC_cpy.Set_install_irq(UART1_INT, (void *)Treat_Data_SPO2_BCI(init_VIC_cpy));
//install_irq (UART1_INT, (void *)Treat_Data_SPO2_BCI(init_VIC_cpy)); //handler_FSM_spo2 UartHandlerUART1
}

void* Spo2::Treat_Data_SPO2_BCI(Vic init_VIC_cpy)
{
	
	IENABLE;					/* handles nested interrupt */	
	IIRValue = U1IIR;

	IIRValue >>= 1;				/* skip pending bit in IIR */
	IIRValue &= 0x07;			/* check bit 1~3, interrupt identification */
	
	T1IR  = 0; 
	
	RxDado = U1RBR;		
	// if the synch bit is set, it is the start of a new packet, reset all values
	if (RxDado & 0x80)
	{
		gCountBCI = PROBE_VERIFY;
	}
	
	if (gMonitoraSpo2)
	{
		switch(gCountBCI)
		{
			case PROBE_VERIFY: //bits 0 - 3: Signal Strength (0xF = invalid)
			//bit 4: searching too long, bit
			//bit 5: Probe Unplugged
			//bit 6: pulse beep
			//bit 7: 1 (synch bit)
			if (RxDado & 0x80)
			{
				if (RxDado == 0x80)
				{
					gRevisionReady = 0x80;
				}
				//SignalStrength = (RxDado & 0x0F);
				gSearchTooLong = RxDado & 0x10;
				gProbebUnpluged = RxDado & 0x20;
				gPulseBeep = RxDado & 0x40;
				gCalculatedChecksum = RxDado;
				gCountBCI = PLETH_VALUE;
			}
			break;
			
			case PLETH_VALUE: //bits 0 - 6: Plethysmogram
				//bit 7: 0 (synch bit)
				if (!((gRevisionReady) && RxDado == 0x00))
				{
					gRevisionReady = 0;
					gPlethValue = RxDado;
					if (gPlethValue > PLETHMAX && gPlethValue != PLETHINVALID)
					{
						gPlethValue = PLETHMAX;
					}
				}
				gCalculatedChecksum +=  RxDado;
				gCountBCI = SENSOR_CHECK;
			break;
			
			case SENSOR_CHECK: //bits 0 - 3: Bargraph
				//bit 4: no finger in probe
				//bit 5: searching for pulse
				//bit 6: sleep mode indicator bit
				//bit 7: 0 (synch bit)
				if (gRevisionReady)
				gRevisionString[0] = RxDado;
				else
				{
					gOxBar = RxDado & 0xF;
					gCheckSensor = RxDado & 0x10;
					gSearching = RxDado & 0x20;
					//SleepMode = RxDado & 0x40;
				}
				//gCalculatedChecksum += (unsigned int) RxDado
				gCalculatedChecksum += RxDado;
				gCountBCI = PULSE_RATE;
			break;
			
			case PULSE_RATE: //bits 0 - 6: Rate bits 0 - 6
				//bit 7: 0(synch bit)
				if (gRevisionReady)
				gRevisionString[1] = RxDado;
				else
				gPulseRate = RxDado & 0x7F;
				gCalculatedChecksum +=  RxDado;
				gCountBCI = SPO2_VALUE;
			break;
			
			case SPO2_VALUE: //bits 0 - 6: SpO2 bits 0 - 6
				//bit 7: 0(synch bit)
				if (gRevisionReady)
				gRevisionString[2] = RxDado;
				else
				{
					spo2_value_prev = RxDado;
					if (spo2_value_prev >= SPO2INVALID)
					spo2_value_prev = SPO2INVALID;
				}
				gCalculatedChecksum +=  RxDado;
				gCountBCI = SPO2_STATUS;
			break;
			
			case SPO2_STATUS: //bits 0 - 1:
				// 00 = 4 beat SpO2 8 sec PR Averaging
				// 01 = 8 beat SpO2 8 sec PR Averaging
				// 10 = 16 beat SpO2 16 sec PR Averaging
				// 11 = 16 beat SpO2 8 sec PR Averaging
				//bit 2: artifact
				//bit 3: small Pulse
				//bit 4: Revision Level Reply
				//bit 5: Lost Pulse
				//bit 6: disable auto pleth scaling
				//bit 7: 0 (synch bit)
			if (gRevisionReady)
			{
				gRevisionString[3] = '.';
				gRevisionString[4] = RxDado;
			}
			else
			{
				//OxAveragingSetting = RxDado & 0x03;
				gArtifact = RxDado & 0x04;
				gSmallPulse = RxDado & 0x08;
				gLostPulse = RxDado & 0x20;
				//AutoSynchOff = RxDado & 0x40;
			}
			gCalculatedChecksum +=  RxDado;
			gCountBCI = GET_REVISION;
			break;
			
			case GET_REVISION:
				//bits 0 - 6: Perfusion Index bits 0 - 6
				//bit 7: 0 (synch bit)
				if (gRevisionReady )
				{
					gRevisionString[5] = RxDado;
				}
				else
					//PerfusionIndex = (unsigned int)RxDado
					gCalculatedChecksum +=  RxDado;
					gCountBCI = VERIFY_STEP1;
			break;
			
			case VERIFY_STEP1:
				//bits 0 - 4: Perfusion Index bits 7 - 11
				//bit 5 1 = PI Sensitivity is ON
				//bit 7: 0 (synch bit)
				if (!(gRevisionReady))
				{
					//PISensitivity = RxDado & 0x20;
					//PerfusionIndex += (unsigned int)(RxDado & 0x1F) * 128;
				}
				gCalculatedChecksum +=  RxDado;
				gCountBCI = REVISION_VERIFY;
			break;
			
			case REVISION_VERIFY:
				//bits 0-2: Rate bits 7-9
				//bits 3-6: Unused
				//bit 7: 0 (synch bit)
				if (gRevisionReady == 0)
				{
					gPulseRate += (RxDado & 0x07) * 128;
					if (gPulseRate >= SPO2PRINVALID)
					gPulseRate = SPO2PRINVALID;
				}
				gCalculatedChecksum += RxDado;
				gCountBCI = VERIFY_STEP2;
			break;
			
			case VERIFY_STEP2:
				//bits 0-6: Spare
				//bit 7: 0 (synch bit)
				gCalculatedChecksum += RxDado;
				gCountBCI = VERIFY_STEP3;
			break;
				
			case VERIFY_STEP3:
				//bits 0-6 Checksum Bits 0-6
				//bit 7: 0 (synch bit)
				gReceivedChecksum = RxDado;
				gCountBCI = ASSIGN_DATA;
			break;
			
			case ASSIGN_DATA: // PEGA CURVA
				//bits 0-6 Checksum Bits 7-13
				//bit 7: 0 (synch bit)
				gReceivedChecksum += RxDado * 128;
				if (gCalculatedChecksum + gReceivedChecksum == 16384)
				{
					if(!gDemo)
					{
						 Set_status_spo2((gLostPulse >> 5) | (gArtifact >> 1) | (gSmallPulse >> 1) | (gSearching >> 2) | gSearchTooLong | gProbebUnpluged | (gCheckSensor << 2));
						
						if(Get_status_spo2() & (gProbebUnpluged | (gCheckSensor << 2)))
						{
							spo2_curve = 0;
							spo2_value = 0;
							spo2_bpm = 0;
						}
						else
						{	
							Set_curva_spo2(gPlethValue);
							Set_bpm_spo2(spo2_value_prev);
							
							if(spo2_value == 127)
							{	
								spo2_value = 0;
							}
							Set_bpm_spo2(gPulseRate);
							if(spo2_bpm > 254)
							{
								spo2_bpm = 0;
							}
						}
						if(gRevisionString[0])
						{
							if(gRevisionString[0] == 'A' && gRevisionString[1] == 'L')
							{
								gOxiModel = OXI_HUMAN;
							}
							else if(gRevisionString[0] == 'A' && gRevisionString[1] == 'V')
							{	
								gOxiModel = OXI_VET;
							}
						} 
					}
				}
				else
				{
					//BadChecksum = 1;
				}
				gCountBCI = PROBE_VERIFY;
			break;
				
			default: //something went wrong, don't depend on the data
				gCountBCI = PROBE_VERIFY;
			break;
		}
	}
	else
		spo2_status = 0;
		
	
	if(IIRValue == IIR_RLS)		/* Receive Line Status */
	{
		LSRValue = U1LSR;
		/* Receive Line Status */
		if ( LSRValue & (LSR_OE|LSR_PE|LSR_FE|LSR_RXFE|LSR_BI) )
		{
			/* There are errors or break interrupt */
			/* Read LSR will clear the interrupt */
			UART1Status = LSRValue;
			Dummy = U1RBR;		/* Dummy read on RX to clear 
			interrupt, then bail out */
			Dummy = Dummy & 0xFF;
			IDISABLE;
			init_VIC_cpy.Set_vic_vect_addr(0);
			//VICVectAddr = 0;		/* Acknowledge Interrupt */
			//return;
		}
		if ( LSRValue & LSR_RDR )	/* Receive Data Ready */			
		{
			/* If no error on RLS, normal ready, save into the data buffer. */
			/* Note: read RBR will clear the interrupt */
			UART1Buffer[UART1Count] = U1RBR;
			UART1Count++;
			if ( UART1Count == BUFSIZE )  // definido como BUFSIZE = 0x100
			{
				UART1Count = 0;		/* buffer overflow */
			}
			
		}
		else if ( IIRValue == IIR_RDA )	/* Receive Data Available */
		{
			/* Receive Data Available */
			UART1Buffer[UART1Count] = U1RBR;
			UART1Count++;	
			if ( UART1Count == BUFSIZE )
			{
				UART1Count = 0;		/* buffer overflow */
			}
		}
	}
	else if ( IIRValue == IIR_CTI )	/* Character timeout indicator */
	{
		/* Character Time-out indicator */
		UART1Status |= 0x100;		/* Bit 9 as the CTI error */
	}
	else if ( IIRValue == IIR_THRE )	/* THRE, transmit holding register empty */
	{
		/* THRE interrupt */
		LSRValue = U1LSR;		/* Check status in the LSR to see if
		valid data in U0THR or not */
		if ( LSRValue & LSR_THRE )
		{
			UART1TxEmpty = 1;
		}
		else
		{
			UART1TxEmpty = 0;
		}
	}
	T1IR        = 1; 
	IDISABLE;
	init_VIC_cpy.Set_vic_vect_addr(0);
	//VICVectAddr = 0;		/* Acknowledge Interrupt */
	IO0SET |= BUZZER;
}

void Spo2::monitora_spo2()
{
	if (gMonitoraSpo2)
	{
		if(!((SEM_DEDO | SENSOR_DESCONECTADO) & spo2_status))
		{
			if((spo2_value < spo2_alarm_min) || (spo2_value > spo2_alarm_max))
			{
				alarme_spo2_phy = true;
			}
			else alarme_spo2_phy = false;		
		}
	}
}


void Spo2::Set_curva_spo2(unsigned char value)
{
	spo2_curve = value;
}
unsigned char Spo2::Get_curva_spo2(void)
{
	return spo2_curve;
}


void Spo2::Set_bpm_spo2(unsigned char value)
{
	spo2_bpm = value;
}

unsigned char Spo2::Get_bpm_spo2(void)
{
	return spo2_bpm;
}

void Spo2::Set_valor_spo2(unsigned char value)
{
	spo2_value = value;
}

unsigned char Spo2::Get_valor_spo2(void)
{
	return spo2_value;
}

void Spo2::Set_status_spo2(unsigned char value)
{
	spo2_status = value;
}

unsigned char Spo2::Get_status_spo2(void)
{
	return spo2_status;
}

void Spo2::Set_AlarmSpo2Min(unsigned char value)
{
	spo2_alarm_min = value;
}

void Spo2::Set_AlarmSpo2Max(unsigned char value)
{
	spo2_alarm_max = value;
}

