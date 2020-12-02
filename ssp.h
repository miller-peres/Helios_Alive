#include "type.h"

DWORD SSP0Init( void );
void SPI0Send( BYTE *buf, DWORD Length );
void SPI0Receive( BYTE *buf, DWORD Length );
int ReadAdc( void );
