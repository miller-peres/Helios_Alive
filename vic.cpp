#include "vic.h"
#include "lpc21xx.h"
#include "global.h"

Vic::Vic(void)
{
i = 0;
//gCountZigbee = 0;
}

//	void Vic::default_VIC()
//{
//	VICDefVectAddr = 0;
//	VICVectAddr = 0;		/* Acknowledge Interrupt */ 
//    while ( 1 );
//}
	
void Vic::init_VIC()
{
    //INICIALIZA A VIC
    VICIntEnClr = 0xffffffff;
    VICVectAddr = 0;
    VICIntSelect = 0;

    /* set all the vector and vector control register to 0 */
    for ( i = 0; i < VIC_SIZE; i++ )
    {
	vect_addr = (unsigned long *)(VIC_BASE_ADDR + VECT_ADDR_INDEX + i*4);
	vect_cntl = (unsigned long *)(VIC_BASE_ADDR + VECT_CNTL_INDEX + i*4);
	*vect_addr = 0;	
	*vect_cntl = 0;
    }
	VICDefVectAddr = 0;
	VICVectAddr = 0;
    return;
}

unsigned long Vic::Set_install_irq(unsigned long int_number, void *handlerAddr) // unsigned long Vic::Set_install_irq(unsigned long UART0_INT, Treat_Data_Zigbee(start_vic))
{
    VICIntEnClr = 1 << int_number;	/* Disable Interrupt */
    
    for ( i = 0; i < VIC_SIZE; i++ )
    {
	/* find first un-assigned VIC address for the handler */

	vect_addr = (unsigned long *)(VIC_BASE_ADDR + VECT_ADDR_INDEX + i*4);
	vect_cntl = (unsigned long *)(VIC_BASE_ADDR + VECT_CNTL_INDEX + i*4);
	if ( *vect_addr == (unsigned long)NULL )
	{
	    *vect_addr = (unsigned long)handlerAddr;	/* set interrupt vector */
	    *vect_cntl = (unsigned long)(IRQ_SLOT_EN | int_number);
	    break;
	}
    }
    if ( i == VIC_SIZE )
    {
	return (false);		/* fatal error, can't find empty vector slot */
    }
    VICIntEnable = 1 << int_number;	/* Enable Interrupt */
    return (true);
}

void Vic::Set_vic_vect_addr(unsigned long VicVectAddr_update)
{
	VICVectAddr = VicVectAddr_update;
}

