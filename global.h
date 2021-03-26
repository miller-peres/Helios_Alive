#include "serial.h"
#include "type.h"

#define FREQ_SAMPLE				125	

#define TX0						P0_0
#define	SCK0					P0_4
#define	MOSI0 					P0_6
//#define BUZZER    				P0_7
#define TX1						P0_8
#define	ON_OFF					P0_10
#define	LED_ECG					P0_13
#define	LED_SPO2				P0_12
#define	LED_ON_BAT		  		P0_17
#define CS_AD                 	P0_16
#define	LED_ENF					P0_11
#define	DER_1		  			P0_22
#define	DER_2		  			P0_23
#define	RESET_ZIGBEE  			P0_18
#define	RSSI 					P0_28
#define BOTAO_ON_OFF          	P0_29
#define LED_VM_AM				P0_30

#define TIME_OUT_ANALISE_PMS		20
#define	ECG_SOLTO								0x01
#define	ECG_ASSISTOLIA					0x02
#define ECG_INDICA_CHOQUE				0x04
#define BPM_OUT         				0x08
#define ECG_CHAMADA_ENFERMEIRA  0x10
#define ECG_BATERIA_FRACA       0x20
#define ECG_SINAL_ST       	  	0x40
#define ECG_ST_OUT							0x80

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

#define SIZE_COEFF_LP_ECG		33
#define NOVO_BUFFER     		1111
#define SEM_NOVO_BUFFER 		2222

//#define TESTE_ANALISE 			130 // MODIFICADO PARA ATENDER A F.V. DO JAULIMETRO VALMAR
#define TESTE_ANALISE 			90 // MODIFICADO PARA ATENDER A F.V. DO JAULIMETRO VALMAR
#define TRIGGER_REDE  			290 // MODIFICADO PARA ATENDER A F.V. DO JAULIMETRO VALMAR
#define TAMANHO 				125
#define ADSIZE 					625
#define BUF1_TOGGLE    			4444
#define BUF2_TOGGLE    			3333

#define LIMITE_THRESHOLD_QRS	50
#define DELAY_QRS				38

#define ECG2_BIP                0x08

// Definição para tipos de cabos ECG utilizados com relação ao número de vias (03 ou 05 vias)
#define CABO_ECG_03V			0
#define CABO_ECG_05V			1

// Definições da seleção de derivação
#define SPO2                    0x01
#define DERIV_DI				0x02
#define DERIV_DII				0x04
#define DERIV_DIII				0x08

#define LIMITE_ELETRODO_SOLTO   100
#define TEMPO_ELETRODO_SOLTO    200

#define FILTRO_DIGITAL_LIGADO	3
#define FILTRO_DIGITAL_DESLIG	4

// Define qual onda será simulada no modo Demonstração
#define DEMO_NORMAL_SINUS		1
#define DEMO_VFIB				2

// Definições do detector de Assistolia
#define THRESHOULD_ASSYSTOLE 	((short)400)
#define TIME_ASSYSTOLE			FREQ_SAMPLE*6		// Tempo de ausência de sinal para detecção de assistolia

//#define NUMERO_BYTES 						152
#define NUMERO_BYTES 			100
#define NUMERO_BYTES_REDUZIDO	32
//#define NUMERO_PONTOS_CURVA 	34
#define NUMERO_PONTOS_CURVA 	68
//#define INICIO_CURVA_ECG    	65
//#define INICIO_CURVA_SPO2   	31
#define INICIO_CURVA		   	31

#define TEMPO_BOTAO_LIGA        20000 //10 segundos // ERA 40000
#define TEMPO_DESL_CHAM_ENF     12000 //3 segundos
#define TEMPO_LIG_CHAM_ENF      4000  //1 segundo
#define TEMPO_PISCA_LED_BAIXA   1500  //0.25 segundo RECONTAR
#define TEMPO_PISCA_LED_ALTA    900  //0.25 segundo RECONTAR
#define TEMPO_PISCA_BIP         500   //0.125 segundo
#define DELAY_INICIALIZACAO     2
#define ALARME_FISIOLOGICO     	0x80
#define DELAY_STAB_SINAL_ECG 	15
#define DELAY_STAB_SINAL_OXI    15
#define BUFF_SIZE_VETOR         136


extern BYTE UART0Buffer[BUFSIZE];
extern BYTE UART1Buffer[BUFSIZE];
extern unsigned short ADCresult[4];

extern unsigned int gTimeOutAnalisePms;
extern unsigned char gMonAtivoChoque;
extern unsigned char gVBat;
extern unsigned int gCanalAD;
extern unsigned int gTempoTeclaLiga;
extern unsigned char  gVetorVelocidade[3];	
extern unsigned char  gVelocidade;
extern unsigned short int gIntervaloValorNum;
extern unsigned int gTempoPiscaLed;
extern unsigned int gTempoBip;
extern unsigned int gTempoBip2;
extern unsigned int gEletrodoSolto;
extern unsigned int gLedEnf;
extern unsigned int gLedEnfAnt;
extern unsigned char gStatusSpo2;
extern unsigned char gDemo;
extern unsigned char gFlagCalculaBpm;
extern unsigned char gLiberaAnalisePms;
extern unsigned int gPassoAnalisaRitmo;
extern unsigned int gChoqueIndicado;
extern unsigned char gResetFilterIir;
extern unsigned char gFlagDelayElSolto;
extern unsigned char gFlagDelaySensDesc;
extern unsigned int timerseg;



//MILLER
extern unsigned int START_FSM;
//static unsigned int timerseg = 0;


#ifdef ST_FILTER
#else
	#define ST_FILTER
	struct stFilter
	{
		int Buffer[SIZE_COEFF_LP_ECG];
		int PtrNewData;
		int *PtrCoeff;
		int SizeCoeff;
	};
#endif

extern struct stFilter stDerivDI;
extern struct stFilter stDerivDII;
extern struct stFilter stDerivC;	
	
extern int gBufBpmMedia[32];	
	
// Coeficientes do filtro de ECG.
extern int CoeffLpEcg[SIZE_COEFF_LP_ECG];	

extern unsigned short gIndexBufAnalise;
extern int gNovoBuffer;	
extern int gAssistolia;
extern float gVetorTeste[TAMANHO];
extern int gBufferNowAnalise;	
extern short gBufferAnalise[ADSIZE];	
extern short gBufferAnalise2[ADSIZE];	
extern int gDeriv;
extern int gTempoAjThreshold;
extern int gConsTempoThreshold;	
extern unsigned short gFlagAssystole;
extern unsigned short gCountAssystole;
extern unsigned char gDemoCurva;
	
extern int gThresholdQrs;
extern int gConsTempoThreshold;
extern int gTempoAjThreshold;
extern int gTempoAjAmplitude;
extern int gDeriv;
extern int gAmplitudeSinal;
extern int gContagemBpm;
extern unsigned char gFlagCalculaBpm;
extern unsigned char gDelayBpm;
extern unsigned char gResetFilterIir;
extern unsigned char gDelayEstabDeriv;
extern unsigned short gValorBpm;
extern unsigned short gSomatorio;
extern unsigned short gEcgMedia;	
extern unsigned short gEcgBpmInst;
extern unsigned char gPerdaPulso;
extern unsigned short gCountAssystole;
extern unsigned char gQrsDetectado;
extern unsigned char gFlagEnviaBpm;
extern unsigned char gEcgCableConfig;
extern unsigned char gDerivacao;
extern unsigned char gFiltroDigitalEcg;
extern unsigned char gEcgDerivDI;
extern unsigned char gEcgDerivDII;
extern unsigned char gEcgDerivDIII;
extern unsigned char gEcgDerivAVR;
extern unsigned char gEcgDerivAVL;
extern unsigned char gEcgDerivAVF;
extern unsigned char gEcgDerivC;
extern unsigned char gCurvaEcg;
extern unsigned int gProtocolVersion;
extern unsigned int gCPUVersionMsb;
extern unsigned int gCPUVersionLsb; 
extern unsigned int gCPURevision;
extern unsigned int gBatFraca;
extern unsigned int gTensaoEletrodo1;
extern unsigned int gTensaoEletrodo2;
extern unsigned int  gTempoEletrodoSolto;
extern unsigned int  gTempoUso;
extern unsigned char gFlag1Segundo;
extern int         gDerivST;
extern unsigned char gAlarmeFisiologico;
extern int gMaxCurvaEcg;
extern int gMinCurvaEcg;
extern int gContMaxCurvaEcg;
extern int gContMinCurvaEcg;

// Variaveis Segmento ST
extern unsigned short gNivel_st;
extern unsigned short gDesnivel_st;
extern unsigned char gStMascara;
extern unsigned char gStMascaraAnt;
extern unsigned char gStMascaraAntAnt;
extern  short gSinalDerivada;
extern short gMaior_st;
extern unsigned short gQrs_st;
extern short gMedia_st[10];
extern unsigned short gContador_deslocamento;
	
//Variaveis SPO2
extern unsigned char  gCountBCI;
extern unsigned char gPlethValue;
extern unsigned char gOxBar;
extern unsigned int gPulseRate;
extern unsigned char gSearchTooLong;
extern unsigned char gProbebUnpluged;
extern unsigned char gCheckSensor;
extern unsigned char gSearching;
extern unsigned char gPulseBeep;
extern unsigned int gSpO2Value;
extern unsigned int gCalculatedChecksum;
extern unsigned int gReceivedChecksum;
extern unsigned char gRevisionReady;
extern char gRevisionString[10];
extern unsigned char gCurvaSpo2;
extern unsigned char gValorSpo2;
extern unsigned short gBpmSpo2;	
extern unsigned char gOxiModel;
extern unsigned char gLostPulse;
extern unsigned char gArtifact;
extern unsigned char gSmallPulse;

//Variaveis Zigbee
extern unsigned char  gCountZigbee ;
extern unsigned char  gVetorZigbee[100];
extern unsigned char  gVetorZigbeeCopia[100];
extern unsigned char  gVetorZigbee2[100];
extern unsigned char  gBytesCentral[100];
extern unsigned char  gCountCentral;
extern unsigned char  gCountStringCentral;
extern unsigned char  gContCurvaCentral; 
extern unsigned char  gAlarmeStMin;
extern unsigned char  gAlarmeStMax;
extern unsigned short  gAlarmeBpmMin;
extern unsigned short  gAlarmeBpmMax;
extern unsigned char  gAlarmeSpo2Min;
extern unsigned char  gAlarmeSpo2Max;
extern unsigned char  gLeito;	
extern unsigned char  gTipoCurva;
extern unsigned char  gVelocidade;
extern unsigned char  gLiberaBufCentral;
extern unsigned char  gVetorVelocidade[3];	
extern unsigned short int gIntervaloValorNum;
extern unsigned char  gVetorST[3];
extern unsigned char gVersaoProtocolo;
extern unsigned char gReenviaPacote;
extern unsigned char gBotaoDesliga;
extern unsigned char gLiberaDesliga;
extern unsigned char gPacoteRecebido;
extern unsigned char gBpmForaFaixa;
extern unsigned char gStForaFaixa;
extern unsigned char gSpo2ForaFaixa;
extern unsigned char gMonitoraEcg;
extern unsigned char gMonitoraSpo2;
extern unsigned char gMonitoraPms;

extern char gMedeBat;
extern unsigned char gAlarmeEcg;
extern unsigned char gAlarmeSpo2;
extern unsigned char gAlarmePulse;
extern unsigned int gIndexVetor;
extern int gValorAd[BUFF_SIZE_VETOR];
extern unsigned char gBufferSpo2[BUFF_SIZE_VETOR];
extern  unsigned char gSincProtocolo;

extern float x[35];//35 posicoes
extern float yzero ;
extern float b_[25] ;

#define SIZE_WAV_SPO2	434
extern unsigned char DemoCurvaSPO2[434]; 
extern unsigned char gFlagDelayTrocaDer;
extern unsigned char gDerivacaoAnt;
extern unsigned char gDelayBat;
#define DELAY_ALARMES 	20
extern unsigned char gCountAlEcg ;
extern unsigned char gAlarmeEcgDelay;
extern unsigned char gCountAlSpo2;
extern unsigned char gAlarmeSpo2Delay;
extern unsigned char gCountAlPulse;
extern unsigned char gAlarmePulseDelay;

