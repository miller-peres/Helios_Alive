#include "vic.h"

class Spo2
{	
	public:
		Spo2(void);
		void config_COM_spo2(Vic);
		void* Treat_Data_SPO2_BCI(Vic); 
	    void monitora_spo2();

		unsigned char Get_curva_spo2(void);
		void Set_curva_spo2(unsigned char value);

		unsigned char Get_bpm_spo2(void);
		void Set_bpm_spo2(unsigned char value);

		unsigned char Get_valor_spo2(void);
		void Set_valor_spo2(unsigned char value);

		unsigned char Get_status_spo2(void);
		void Set_status_spo2(unsigned char value);
	
		unsigned char  spo2_alarm_min;
		unsigned char  spo2_alarm_max;
	
		void Set_AlarmSpo2Min(unsigned char value);
		void Set_AlarmSpo2Max(unsigned char value);

// DEFINIÇÕES DE CONFIG DE COM SPO2
#define   	COM1    	1
#define		UART1_INT	7
#define  	EVEN   		0
#define   	ODD    		1
#define	  	NONE		2
#define   	FOSC 		10000000              // Frequencia do cristal  = 10MHz.
#define   	PLL_M 		6 				   // PLL_M
#define   	VPBDIV_VAL	1			   // Sem multipliccao do clock
#define   	UART_BAUD(baud) (unsigned int)(((FOSC*PLL_M/VPBDIV_VAL) / ((baud) * 16.0)) + 0.5)
#define   	BIT_0  		0x00000001   
#define 	BIT_1   	0x00000002   
#define 	BIT_2  	 	0x00000004    
#define 	BIT_3   	0x00000008    
#define 	BIT_4   	0x00000010    
#define 	BIT_16  	0x00010000  
#define 	BIT_18  	0x00040000  
#define BUZZER    				P0_7

// DEFINIÇÕES DE TRATAMENTO DE SPO2
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

// CONFIGURA E ATIVA A INTERRUPCAO PARA O CANAL x                             =
//============================================================================*/

#define CONFIGURA_INTERRUPCAO_VIC(canal,isr,dispositivo)                     \
{                                                                            \
  VICVectAddr##canal = (unsigned)isr;                                        \
  VICVectCntl##canal = VIC_CH_##dispositivo | ATIVA_VIC_VECT;                \
  VICIntEnable = VIC_MASK_##dispositivo;                                     \
}

#define DADO_DISPONIVEL_UART(COM1) (U1LSR & 0x01)
#define TX_READY_UART(COM1)        (U1LSR & 0x20)
#define DADO_RX_UART(COM1)         (U1RBR)
#define LSR(COM1)                  (U1LSR = 1)

//============================================================================*/

#if NESTED_INTERRUPT
#define IENABLE __asm { MRS sysreg, SPSR; MSR CPSR_c, #SYS32Mode }
#define IDISABLE __asm { MSR CPSR_c, #(IRQ32Mode|I_Bit); MSR SPSR_cxsf, sysreg }
#else
#define IENABLE ;
#define IDISABLE ;
#endif
	
	private:
		// variáveis de configurações COM	
		char port_spo2;
		char n_spo2;
		char StopBits_spo2;
		char Parity_spo2;
		long bps_spo2;
		int baud_spo2;
		char ch;
	
		//Variaveis TRATA DADOS SPO2
		unsigned int spo2_value_prev;	
		unsigned int spo2_value;
		unsigned char spo2_curve;
		unsigned int spo2_bpm;
		unsigned char spo2_status;
	
		unsigned char  gCountBCI;
		unsigned char gPlethValue;
		unsigned char gOxBar;
		unsigned int gPulseRate;
		unsigned char gSearchTooLong;
		unsigned char gProbebUnpluged;
		unsigned char gCheckSensor;
		unsigned char gSearching;
		unsigned char gPulseBeep;
		
		unsigned int gCalculatedChecksum;
		unsigned int gReceivedChecksum;
		unsigned char gRevisionReady;
		char 		  gRevisionString[10];
	
			
		unsigned char gOxiModel;
		unsigned char gLostPulse;
		unsigned char gArtifact;
		unsigned char gSmallPulse; 
		
		unsigned char IIRValue, LSRValue;
		unsigned char Dummy;
		unsigned char RxDado;
		unsigned char UART1TxEmpty;
		
		bool gMonitoraSpo2;
		unsigned char gDemo;
		unsigned long UART1Status;
		unsigned long UART0Count;
		bool alarme_spo2_phy;
		bool alarme_spo2_tec;
		int UART1Count;
		

};
