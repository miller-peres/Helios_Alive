#include "vic.h"
#include <string.h>
#include <stdio.h>

class Zigbee
{	
	public:
		Zigbee(void);
		void config_COM_zigbee(Vic);
		void Treat_Data_Zigbee(); //Vic
		void send_package(bool resend_package); //Spo2
		void COM_tx_buffer();
		void uart_tx_char(char port, unsigned char ch);
		unsigned char resend_package_general;
//		template<typename T, typename R>
//	    void* void_cast(R(T::*f));
		

		// DEFINIÇÕES DE CONFIG DE COM ZIGBEE
		#define  COM0   0
		#define  EVEN   0
		#define  ODD    1
		#define	 NONE	2
		#define   	FOSC 		10000000              // Frequencia do cristal  = 10MHz.
		#define   	PLL_M 		6 				   // PLL_M
		#define   	VPBDIV_VAL	1			   // Sem multipliccao do clock
		#define TX0						P0_0
		#define SPO2                    0x01
		#define DERIV_DI				0x02
		#define DERIV_DII				0x04
		#define DERIV_DIII				0x08 // VERIFICAR DEMAIS DERIVAÇÕES

		#define IIR_RLS		0x03
		#define LSR_RDR		0x01
		#define LSR_OE		0x02
		#define LSR_PE		0x04
		#define LSR_FE		0x08
		#define LSR_BI		0x10
		#define LSR_THRE	0x20
		#define LSR_TEMT	0x40
		#define LSR_RXFE	0x80
		#define BUFSIZE		0x100
		#define IIR_RDA		0x02
		#define IIR_PEND	0x01
		#define IIR_RLS		0x03
		#define IIR_CTI		0x06
		#define IIR_THRE	0x01

		#define NUMERO_BYTES 			100
		#define NUMERO_BYTES_REDUZIDO	32
		#define NUMERO_PONTOS_CURVA 	68
		#define INICIO_CURVA		   	31
		#define   	UART_BAUD(baud) (unsigned int)(((FOSC*PLL_M/VPBDIV_VAL) / ((baud) * 16.0)) + 0.5)
		#define BIT_2   0x00000004  
		#define BIT_0   0x00000001   
		#define BIT_1   0x00000002    
		#define	DER_1		  			P0_22
		#define	DER_2		  			P0_23
		#define P0_22 BIT_22
		#define P0_23 BIT_23
		#define BIT_22  0x00400000    
		#define BIT_23  0x00800000    
		#define BUZZER    				P0_7

		// CONFIGURA E ATIVA A INTERRUPCAO PARA O CANAL x                             =
		//============================================================================*/

		#define CONFIGURA_INTERRUPCAO_VIC(canal,isr,dispositivo)                     \
		{                                                                            \
		  VICVectAddr##canal = (unsigned)isr;                                        \
		  VICVectCntl##canal = VIC_CH_##dispositivo | ATIVA_VIC_VECT;                \
		  VICIntEnable = VIC_MASK_##dispositivo;                                     \
		}

		#define DADO_DISPONIVEL_UART(COM0) (U0LSR & 0x01)
		#define TX_READY_UART(COM0)        (U0LSR & 0x20)
		#define DADO_RX_UART(COM0)         (U0RBR)
		#define LSR(COM0)                  (U0LSR = 1)

		
	private:
		// variáveis de configurações COM	
		unsigned int Conexao;
		unsigned int Reset_Zigbee;
		char port;
		char n;
		char StopBits;
		char Parity;
		long bps;
		int baud;
		unsigned char *pBuffer;
		short int nBytes;
		
		// variáveis de configurações remover depois
		unsigned char RxDado;
		unsigned char  gCountZigbee;
		unsigned char  gVetorZigbee[100];
		unsigned char  gVetorZigbeeCopia[100];
		unsigned char  gVetorZigbee2[100];
		unsigned char  gBytesCentral[100];
		unsigned char  gCountCentral;
		unsigned char  gCountStringCentral;
		unsigned char  gContCurvaCentral; 
		unsigned char  gAlarmeStMin;
		unsigned char  gAlarmeStMax;
		unsigned short  gAlarmeBpmMin;
		unsigned short  gAlarmeBpmMax;
		unsigned char  gAlarmeSpo2Min;
		unsigned char  gAlarmeSpo2Max;
		unsigned char  gLeito;	
		unsigned char  gTipoCurva;
		unsigned char  gVelocidade;
		unsigned char  gLiberaBufCentral;
		unsigned char  gVetorVelocidade[3];	
		unsigned short int gIntervaloValorNum;
		unsigned char  gVetorST[3];
		unsigned char gVersaoProtocolo;
		//unsigned char gReenviaPacote;
		unsigned char gBotaoDesliga;
		unsigned char gLiberaDesliga;
		unsigned char gPacoteRecebido;
		unsigned char gBpmForaFaixa;
		unsigned char gStForaFaixa;
		unsigned char gSpo2ForaFaixa;
		unsigned char gMonitoraEcg;
		unsigned char gMonitoraSpo2;
		unsigned char gMonitoraPms;
		unsigned char ReenviaPacote;
		unsigned int gCPUVersionMsb;
		unsigned int gCPUVersionLsb; 
		unsigned int gCPURevision; 
		unsigned int gProtocolVersion;
		unsigned int gIndexVetor;
		unsigned long UART0Status;
		unsigned char IIRValue;
		unsigned char Dummy;
		unsigned char LSRValue;
		unsigned long UART0Count;
		unsigned char UART0TxEmpty;
		int a;

		// REMOVER DEPOIS PEGAR DA CLASSE ALARMES
		unsigned int spo2_bpm;
		unsigned int gValorSpo2;
		unsigned int gNivel_st;
		unsigned int gVBat;
		unsigned int gEletrodoSolto;
		bool gFlagAssystole;
		unsigned int gAlarmeEcgDelay;
		unsigned int gMonAtivoChoque;
		unsigned int gStMascara;
		unsigned int gLedEnf;
		unsigned int gStatusSpo2;
		unsigned int gBatFraca;
		unsigned int gDerivacao;
		unsigned int gSincProtocolo;
		
		template<typename T, typename R>
		void* void_cast(R(T::*f)())
		{
			union 
			{
				R(T::*pf)();
				void* p;
			};
			pf = f;
			return p;
		}

};
