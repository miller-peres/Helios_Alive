
#define FREQ_SAMPLE				125								// Frequencia de amostragem do A/D
#define CONTA_PERDA_PULSO		((unsigned short)(FREQ_SAMPLE*3.75))	// Tempo de detecção de perda de pulso
#define CONST_THRESHOLD			((unsigned short)(FREQ_SAMPLE*60))		// Constante de tempo para BPM

#define TIMER_ELETRODO_SOLTO	(unsigned short)(FREQ_SAMPLE * 0.5)
#define THRESHOULD_EL_SOLTO		7864

#define TIME_OUT_ANALISE_PMS	20

// Definição do tempo do sinal da deivação CAL
#define TEMPO_SINAL_CAL_LOW		105
#define TEMPO_SINAL_CAL_HIGH	TEMPO_SINAL_CAL_LOW + 20

#define ELETRODO_RA		0
#define ELETRODO_LA		1
#define ELETRODO_LL		2
#define ELETRODO_C		3

// Definição do byte de controle do ADS8345
#define START	0x80
#define A2		0x40
#define A1		0x20
#define A0		0x10
#define SGL		0x04
#define PD1		0x02
#define PD0		0x01

// Definição dos canais do ADS8345
#define CH0		0x00
#define CH1		A2
#define CH2		A0
#define CH3		A2 | A0
#define CH4		A1
#define CH5		A2 | A1
#define CH6		A1 | A0
#define CH7		A2 | A1 | A0

// Configuração padrão para ADC, Modo Single-End, Internal Clock Mode
#define CONFIG_ADC		START | SGL | PD1

#define AD_DERIV_DI			CONFIG_ADC | CH0
#define AD_DERIV_DII_DIII	CONFIG_ADC | CH1
#define AD_DERIV_C			CONFIG_ADC | CH2
#define AD_ELETRODO_RA		CONFIG_ADC | CH3
#define AD_ELETRODO_LA 		CONFIG_ADC | CH4
#define AD_ELETRODO_LL 		CONFIG_ADC | CH5
#define AD_ELETRODO_C 		CONFIG_ADC | CH6
#define AD_TEMP 			CONFIG_ADC | CH7

//Definição para mascara de bits de polaridade do valor de ST
#define ST_DI      1
#define ST_DII     2
#define ST_DIII    4
#define ST_AVR     8
#define ST_AVL     16
#define ST_AVF     32
#define ST_C       64

struct stEletrodo
{
	unsigned short TimerOn;
	unsigned short TimerOff;
	unsigned short Solto;
};

// Protótipo de funções
void QrsThreshold(int Sample, int SampleDcRemove);
void NivelSt(int Deriv_Filter);
//void NivelSt(short Deriv_Filter);
void QrsDetection(int Sample, int SampleDcRemove);
void CalculaMediaBpm(int NumSamples);
void ContaBpm(void);
unsigned char AjustaCurvaEcg(int Sinal);
void DetectaEletrodoSolto(void);
unsigned char InterruptEcg(int ValorAd, unsigned char Index);
