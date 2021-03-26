
class handler_COM_spo2
{	
	public:
		handler_COM_spo2(void);
		void handler_FSM_spo2();
			
			//Variaveis SPO2
		unsigned char  gCountBCI;
		unsigned char gPlethValue;
		unsigned char gOxBar;
		unsigned int gPulseRate;
		unsigned char gSearchTooLong;
		unsigned char gProbebUnpluged;
		unsigned char gCheckSensor;
		unsigned char gSearching;
		unsigned char gPulseBeep;
		unsigned int gSpO2Value;
		unsigned int gCalculatedChecksum;
		unsigned int gReceivedChecksum;
		unsigned char gRevisionReady;
		char 		  gRevisionString[10];
		unsigned char gCurvaSpo2;
		unsigned char gValorSpo2;	
		unsigned short gBpmSpo2;	
		unsigned char gOxiModel;
		unsigned char gLostPulse;
		unsigned char gArtifact;
		unsigned char gSmallPulse; 
		
		unsigned char IIRValue, LSRValue;
		unsigned char Dummy;
		unsigned char RxDado;
		unsigned char UART1TxEmpty;
		
		unsigned char gMonitoraSpo2;
		unsigned char gDemo;
		unsigned char gStatusSpo2;
		unsigned long UART1Status;
		unsigned long UART0Count;
		int UART1Count;
};