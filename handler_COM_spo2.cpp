#include "handler_COM_spo2.h"
#include "irq.h"
#include "lpc21xx.h"

//Definições de SPO2
#define PERDA_PULSO       		0x01
#define ARTEFATO          		0x02
#define SINAL_FRACO       		0x04
#define BUSCANDO_SINAL    		0x08
#define BUSCA_LONGA       		0x10
#define SENSOR_DESCONECTADO 	0x20
#define SEM_DEDO          		0x40
#define SPO2_OUT				0x80

#define PLETHMAX  				99
#define PLETHINVALID 			0x7F
#define SPO2INVALID 			0x7F
#define SPO2PRINVALID 			0x3FF
#define OXI_HUMAN				1
#define OXI_VET					2

#define IIR_PEND	0x01
#define IIR_RLS		0x03
#define IIR_RDA		0x02
#define IIR_CTI		0x06
#define IIR_THRE	0x01

#define LSR_RDR		0x01
#define LSR_OE		0x02
#define LSR_PE		0x04
#define LSR_FE		0x08
#define LSR_BI		0x10
#define LSR_THRE	0x20
#define LSR_TEMT	0x40
#define LSR_RXFE	0x80
#define BUFSIZE		0x100
unsigned char UART1Buffer[BUFSIZE];

handler_COM_spo2::handler_COM_spo2(){UART1TxEmpty = 1;}
	
void handler_COM_spo2::handler_FSM_spo2()
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
		gCountBCI = 0;
	}
	
	if (gMonitoraSpo2)
	{
		switch(gCountBCI)
		{
			case 0: //bits 0 - 3: Signal Strength (0xF = invalid)
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
				gCountBCI++;
			}
			break;
			
			case 1: //bits 0 - 6: Plethysmogram
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
				gCountBCI++;
			break;
			
			case 2: //bits 0 - 3: Bargraph
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
				gCountBCI++;
			break;
			
			case 3: //bits 0 - 6: Rate bits 0 - 6
				//bit 7: 0(synch bit)
				if (gRevisionReady)
				gRevisionString[1] = RxDado;
				else
				gPulseRate = RxDado & 0x7F;
				gCalculatedChecksum +=  RxDado;
				gCountBCI++;
			break;
			
			case 4: //bits 0 - 6: SpO2 bits 0 - 6
				//bit 7: 0(synch bit)
				if (gRevisionReady)
				gRevisionString[2] = RxDado;
				else
				{
					gSpO2Value = RxDado;
					if (gSpO2Value >= SPO2INVALID)
					gSpO2Value = SPO2INVALID;
				}
				gCalculatedChecksum +=  RxDado;
				gCountBCI++;
			break;
			
			case 5: //bits 0 - 1:
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
			gCountBCI++;
			break;
			
			case 6:
				//bits 0 - 6: Perfusion Index bits 0 - 6
				//bit 7: 0 (synch bit)
				if (gRevisionReady )
				{
					gRevisionString[5] = RxDado;
				}
				else
					//PerfusionIndex = (unsigned int)RxDado
					gCalculatedChecksum +=  RxDado;
					gCountBCI++;
			break;
			
			case 7:
				//bits 0 - 4: Perfusion Index bits 7 - 11
				//bit 5 1 = PI Sensitivity is ON
				//bit 7: 0 (synch bit)
				if (!(gRevisionReady))
				{
					//PISensitivity = RxDado & 0x20;
					//PerfusionIndex += (unsigned int)(RxDado & 0x1F) * 128;
				}
				gCalculatedChecksum +=  RxDado;
				gCountBCI++;
			break;
			
			case 8:
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
				gCountBCI++;
			break;
			
			case 9:
				//bits 0-6: Spare
				//bit 7: 0 (synch bit)
				gCalculatedChecksum += RxDado;
				gCountBCI++;
			break;
				
			case 10:
				//bits 0-6 Checksum Bits 0-6
				//bit 7: 0 (synch bit)
				gReceivedChecksum = RxDado;
				gCountBCI++;
			break;
			
			case 11:
				//bits 0-6 Checksum Bits 7-13
				//bit 7: 0 (synch bit)
				gReceivedChecksum += RxDado * 128;
				if (gCalculatedChecksum + gReceivedChecksum == 16384)
				{
					if(!gDemo)
					{
						gStatusSpo2 = ((gLostPulse >> 5) | (gArtifact >> 1) | (gSmallPulse >> 1) | (gSearching >> 2) | gSearchTooLong | gProbebUnpluged | (gCheckSensor << 2));
						
						if(gStatusSpo2 & (gProbebUnpluged | (gCheckSensor << 2)))
						{
							gCurvaSpo2 = 0;
							gValorSpo2 = 0;
							gBpmSpo2 = 0;
						}
						else
						{
							gCurvaSpo2 = gPlethValue;
							gValorSpo2 = gSpO2Value;
							if(gValorSpo2 == 127)gValorSpo2 = 0;
							gBpmSpo2 = gPulseRate;
							if(gBpmSpo2 > 254) gBpmSpo2 = 0;
						}
						if(gRevisionString[0])
						{
							if(gRevisionString[0] == 'A' && gRevisionString[1] == 'L')gOxiModel = OXI_HUMAN;
							else if(gRevisionString[0] == 'A' && gRevisionString[1] == 'V')gOxiModel = OXI_VET;
						} 
					}
				}
				else
				{
					//BadChecksum = 1;
				}
				gCountBCI = 0;
			break;
				
			default: //something went wrong, don't depend on the data
				gCountBCI = 0;
			break;
		}
	}
	else
		gStatusSpo2 = 0;
		
	
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
			VICVectAddr = 0;		/* Acknowledge Interrupt */
			return;
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
	VICVectAddr = 0;		/* Acknowledge Interrupt */
}