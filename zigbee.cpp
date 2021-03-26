#include "zigbee.h"
#include "lpc21xx.h"
#include "irq.h"
#include "global.h"

Zigbee::Zigbee(void)
{
gCPUVersionMsb = 10;
gCPUVersionLsb = 00; 
gCPURevision = 00; 
gProtocolVersion = 1;
UART0Count = 0;
}

void Zigbee::send_package(bool resend_package) //Spo2 Init_spo2
{
unsigned char i = 0;
unsigned char Checksum = 0;
port = COM0;
gValorSpo2= 99;

	if(!resend_package)
	{		
		gVetorZigbee[0] = 0x7E;  // Start Delimeter
		gVetorZigbee[1] = 0x00;  // Lenght MSB
		gVetorZigbee[2] = NUMERO_BYTES - 4;// Lenght LSB
		gVetorZigbee[3] = 0x10;  // Frame Type
		gVetorZigbee[4] = 0x00;  // Frame ID
		gVetorZigbee[5] = 0x00;  //////////MSB//////////////////////
		gVetorZigbee[6] = 0x00;  //
		gVetorZigbee[7] = 0x00;  //
		gVetorZigbee[8] = 0x00;  //   64-Bit Destination Address
		gVetorZigbee[9] = 0x00;  //
		gVetorZigbee[10] = 0x00; //
		gVetorZigbee[11] = 0x00; //
		gVetorZigbee[12] = 0x00; /////////LSB/////////////////////
		gVetorZigbee[13] = 0xFF; // MSB-16-Bit Destination Network Addres
		gVetorZigbee[14] = 0xFE; // LSB-16-Bit Destination Network Addres
		gVetorZigbee[15] = 0x00; // Broadcast Radius
		gVetorZigbee[16] = 0x00; // Options 
		gVetorZigbee[17] = 0xEA; // Û
		
		//Fernando Malta - Evita que seja enviado o valor 0x7E
		if(gCPUVersionMsb == 0x7E)gCPUVersionMsb = 0x7F;
		gVetorZigbee[18] = gCPUVersionMsb;
		if(gCPUVersionLsb == 0x7E)gCPUVersionLsb = 0x7F;
		gVetorZigbee[19] = gCPUVersionLsb; 
		if(gCPURevision == 0x7E)gCPURevision = 0x7F;
		gVetorZigbee[20] = gCPURevision;
		if(gProtocolVersion == 0x7E)gProtocolVersion = 0x7F;		
		gVetorZigbee[21] = gProtocolVersion; // PROTOCOL VERSION
		gVetorZigbee[22] = 0; // Byte não usado
		
		//teste 1 miller
		if(spo2_bpm == 0x7E)spo2_bpm = 0x7F;	
		gVetorZigbee[23] = (spo2_bpm & 0xFF00) >> 8;
		gVetorZigbee[24] = spo2_bpm & 0x00FF;
		
//		spo2_bpm = Init_spo2.Get_bpm_spo2();
//		if(Init_spo2.Get_bpm_spo2() == 0x7E)Init_spo2.Get_bpm_spo2() = 0x7F;	
//		gVetorZigbee[23] = (Init_spo2.Get_bpm_spo2()& 0xFF00) >> 8;
//		gVetorZigbee[24] = Init_spo2.Get_bpm_spo2() & 0x00FF;
		
		if(gValorSpo2 == 0x7E)gValorSpo2 = 0x7F;
		gVetorZigbee[25] = gValorSpo2;
		
		if(gNivel_st == 0x7E)gNivel_st = 0x7F;
		gVetorZigbee[26] = gNivel_st & 0x00FF;		
		if(gVBat == 0x7E)gVBat = 0x7F;
		gVetorZigbee[27] = gVBat; // BATERIA
		
		
		//Tabela C
		//Fernando Malta - Evita que seja enviado o valor 0x7E
		gVetorZigbee[30] = gDerivacao | (gBotaoDesliga << 6) | (gSincProtocolo << 5) | (gPacoteRecebido << 4) | 0x80;
		if(gSincProtocolo)gSincProtocolo = 0;
		if (gPacoteRecebido) gPacoteRecebido = 0;
				
		for(i = 3; i < NUMERO_BYTES - 1; i++)
			Checksum += gVetorZigbee[i];
			
		Checksum = 0xFF - (Checksum & 0xFF); 
		gVetorZigbee[NUMERO_BYTES - 1] = Checksum;
		
		gCountStringCentral = 0;
		
		while(gCountStringCentral < NUMERO_BYTES)uart_tx_char (0,gVetorZigbee[gCountStringCentral++]);		

		gCountCentral = 0;							
		
		for(i = 0; i < 100; i++)
		{
			gVetorZigbeeCopia[i] = gVetorZigbee[i];
		}
	}
	else
	{
		while(i < NUMERO_BYTES)uart_tx_char (0,gVetorZigbeeCopia[i++]);
	}	
}

void Zigbee::uart_tx_char(char port, unsigned char ch)
{
	  if (port == COM0) 
  {
     while (!(U0LSR & 0x20));
     U0THR = ch;
  }
  else 
  {
     while (!(U1LSR & 0x20));
     U1THR = ch;
  }
}

void Zigbee::config_COM_zigbee(Vic init_VIC_cpy)
{
	port = COM0;
	n = 8;
	StopBits = 1;
	Parity = NONE; 
	bps = 115200;
	baud = UART_BAUD(bps);
	PINSEL0 |= BIT_2 | BIT_0; //Habilita TXD0 e RXD0
	U0LCR = (n == 7 ? BIT_1 :(BIT_1 | BIT_0)); // Define numero de bits de dados / se n == 7 U0LCR recebe BIT_1 senao recebe ...
	U0LCR |= (StopBits == 2 ? BIT_2 : 0); // Define stop bits...
	if((Parity == EVEN)||(Parity == ODD)) 
	{
		U0LCR |=0x08; // Define paridade ...
	}
	else 
	{
		U0LCR &= 0xF7;
	}
	if(Parity==EVEN)
	{
		U0LCR |=0x10;
	}
	else 
	{
		U0LCR &= 0xEF;
	}
	U0LCR |= 0x80;
	//baud = 10;
	//U0FDR = 0x85;
	U0DLL  = baud;			  
	U0DLM  = (baud >> 8);				
	U0LCR &= ~(0x80);				                                        
	U0IER = BIT_0 | BIT_2;   // Habilita int RDA e RX                          
	init_VIC_cpy.Set_install_irq(UART0_INT, (void *)Treat_Data_Zigbee(init_VIC_cpy));
	//install_irq (UART0_INT, (void *)Treat_Data_Zigbee(init_VIC_cpy)); // CONFIGURA_INTERRUPCAO_VIC(0,UartHandlerUART0,UART0);		
}

void Zigbee::COM_tx_buffer()
{
	for(;;)
	{
		//Verifica se chegou ao final do buffer nBytes==0
		if (nBytes == 0)
		break;   
		while (!TX_READY_UART(COM0));
		U0THR = *pBuffer;
		//Acerta numero de bytes faltantes e incrementa pointer para proximo caractere...
		nBytes--;
		pBuffer++;		
	}
}

void* Zigbee::Treat_Data_Zigbee(Vic init_VIC_cpy)
{
	IO0SET |= BUZZER;
	spo2_bpm++;
	
	unsigned char RxDado = 0;
	unsigned char UART0Buffer[BUFSIZE];
	IENABLE;					/* handles nested interrupt */	
	IIRValue = U0IIR;
	IIRValue >>= 1;				/* skip pending bit in IIR */
	IIRValue &= 0x07;			/* check bit 1~3, interrupt identification */
	RxDado = U0RBR;		
	if (RxDado == 0x7E)gCountZigbee = 0;
	else gCountZigbee++;
	gVetorZigbee2[gCountZigbee] = RxDado;
	
	if((gCountZigbee == 29) && (gVetorZigbee2[15] == 0xEA) && (gVetorZigbee2[16] == 0x69) && (gVetorZigbee2[17] == 0x6E) && (gVetorZigbee2[18] == 0x73))
	{
		gVersaoProtocolo = gVetorZigbee2[19];
		
		gDerivacao = gVetorZigbee2[20] & 0x0F;
		gLiberaDesliga = (gVetorZigbee2[20] & 0x40) >> 6;
		gSincProtocolo = (gVetorZigbee2[20] & 0x20) >> 5;
		gMonitoraEcg = (gVetorZigbee2[20] & 0x10) >> 4;
		gMonitoraSpo2 = (gVetorZigbee2[20] & 0x80) >> 7;
		resend_package_general = (gVetorZigbee2[21] & 0x01);
		gMonitoraPms = (gVetorZigbee2[21] & 0x02) >> 1;					
		gAlarmeStMin = gVetorZigbee2[22];
		gAlarmeStMax = gVetorZigbee2[23];
		gAlarmeBpmMax = gVetorZigbee2[24] | (gVetorZigbee2[25] << 8);
		gAlarmeBpmMin = gVetorZigbee2[26] | (gVetorZigbee2[27] << 8);
		gAlarmeSpo2Min = gVetorZigbee2[28];
		gAlarmeSpo2Max = gVetorZigbee2[29]; 
		
		if(resend_package_general)
		{
			send_package(true);
			resend_package_general = false;
		}
		else
			gPacoteRecebido = 1;
		
		if(gSincProtocolo)
		{	
			gCountCentral = 0;
			gIndexVetor = 0;
		}
	}
	
	if ( IIRValue == IIR_RLS )	/* Receive Line Status */
	{
		LSRValue = U0LSR;
		/* Receive Line Status */
		if ( LSRValue & (LSR_OE|LSR_PE|LSR_FE|LSR_RXFE|LSR_BI) )
		{
			/* There are errors or break interrupt */
			/* Read LSR will clear the interrupt */
			UART0Status = LSRValue;
			Dummy = U0RBR;		/* Dummy read on RX to clear
			interrupt, then bail out */
			Dummy = Dummy & 0xFF; 
			IDISABLE;
			VICVectAddr = 0;
			init_VIC_cpy.Set_vic_vect_addr(0);
			//return;
		}
		if ( LSRValue & LSR_RDR )	/* Receive Data Ready */			
		{
			/* If no error on RLS, normal ready, save into the data buffer. */
			/* Note: read RBR will clear the interrupt */
			UART0Buffer[UART0Count] = U0RBR;
			UART0Count++;
			if ( UART0Count == BUFSIZE )
			{
				UART0Count = 0;		/* buffer overflow */
			}
		}
	}
	else if ( IIRValue == IIR_RDA )	/* Receive Data Available */
	{
		/* Receive Data Available */
		UART0Buffer[UART0Count] = U0RBR;
		UART0Count++;
		if ( UART0Count == BUFSIZE )
		{
			UART0Count = 0;		/* buffer overflow */
		}
	}
	else if ( IIRValue == IIR_CTI )	/* Character timeout indicator */
	{
		/* Character Time-out indicator */
		UART0Status |= 0x100;		/* Bit 9 as the CTI error */
	}
	else if ( IIRValue == IIR_THRE )	/* THRE, transmit holding register empty */
	{
		/* THRE interrupt */
		LSRValue = U0LSR;		/* Check status in the LSR to see if
		valid data in U0THR or not */
		if ( LSRValue & LSR_THRE )
		{
			UART0TxEmpty = 1;
		}
		else
		{
			UART0TxEmpty = 0;
		}
	}
	IO0CLR |= BUZZER;
	IDISABLE;
	VICVectAddr = 0;
	init_VIC_cpy.Set_vic_vect_addr(0);
	//COM_tx_buffer();
}
