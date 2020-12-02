#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "global.h"
#include <dspfns.h>

struct stDcRemove
{
	int DataXAnt;
	int DataYAnt;
};


extern long int DcRemove(int NewData, struct stDcRemove *DcRemove);
extern long int DcRemoveST(int NewData, struct stDcRemove *DcRemove);
extern float sim_rbf(float *vetor);
extern int assistolia(float *vetor);
extern void normaliza(float *vetor,float *vetor_f);
extern int32_t RoundNumber(float Value);
extern unsigned short fir_bp(unsigned short temp);




