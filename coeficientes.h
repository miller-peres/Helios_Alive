#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "global.h"
#include <dspfns.h>

#define SIZE_WAV_NORMAL_SINUS	125
#define SIZE_WAV_VFIB			136


#define TAMANHO 125
#define CENTROS 8

extern float average[TAMANHO];
extern float st_dev[TAMANHO];
extern float centers_S[TAMANHO][CENTROS];
extern float normalization[2];

extern float variance[CENTROS];
extern float weight[CENTROS+1];
 
extern int16_t DemoSinusDI[SIZE_WAV_NORMAL_SINUS];
extern int16_t DemoSinusDII[SIZE_WAV_NORMAL_SINUS];
extern int16_t DemoSinusC[SIZE_WAV_NORMAL_SINUS];

extern int16_t DemoVfibDI[SIZE_WAV_VFIB];
extern int16_t DemoVfibDII[SIZE_WAV_VFIB];
extern int16_t DemoVfibC[SIZE_WAV_VFIB];



