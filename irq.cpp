/*****************************************************************************
 *   irq.c: Interrupt handler C file for Philips LPC214x Family Microprocessors
 *
 *   Copyright(C) 2006, Philips Semiconductor
 *   All rights reserved.
 *
 *   History
 *   2005.10.01  ver 1.00    Prelimnary version, first Release
 *
******************************************************************************/
#include "lpc21xx.h"			/* LPC23XX Peripheral Registers	*/
#include "type.h"
#include "irq.h"

/** DefaultVICHandler
 *
 * @brief      		    Default VIC interrupt handler.
 * @brief				This handler is set to deal with spurious 
 * @brief				interrupt.
 * @brief				If the IRQ service routine reads the VIC
 * @brief				address register, and no IRQ slot responses
 * @brief				as described above, this address is returned.
 * @return 		    None
 * 
 */ 
void DefaultVICHandler (void) __irq
{
    /* if the IRQ is not installed into the VIC, and interrupt occurs, the
    default interrupt VIC address will be used. This could happen in a race 
    condition. For debugging, use this endless loop to trace back. */
    /* For more details, see Philips appnote AN10414 */
    VICVectAddr = 0;		/* Acknowledge Interrupt */ 
    while ( 1 );
}

/** init_VIC
 *
 * @brief		Initialize VIC interrupt controller.
 * @return		None
 * 
 */
void init_VIC(void)  {
    DWORD i = 0;
    DWORD *vect_addr, *vect_cntl;
   	
    /* initialize VIC*/
    VICIntEnClr = 0xffffffff;
    VICVectAddr = 0;
    VICIntSelect = 0; // MILLER AQUI VERIFICA SE SERÁ IRQ(0) OU FIQ(1) MÉDIA OU ALTA PRIORIDADE

    /* set all the vector and vector control register to 0 */
    for ( i = 0; i < VIC_SIZE; i++ )
    {
	vect_addr = (DWORD *)(VIC_BASE_ADDR + VECT_ADDR_INDEX + i*4);
	vect_cntl = (DWORD *)(VIC_BASE_ADDR + VECT_CNTL_INDEX + i*4);
	*vect_addr = 0;	
	*vect_cntl = 0;
    }

    /* Install the default VIC handler here */
    VICDefVectAddr = (DWORD)DefaultVICHandler;   
    return;
}

/** install_irq
 *
 * @brief               Install interrupt handler
 * @brief 				The max VIC size is 16, but, there are 32 interrupt
 * @brief 				request inputs. Not all of them can be installed into
 * @brief 				VIC table at the same time.
 * @brief 				The order of the interrupt request installation is
 * @brief 				first come first serve.
 * @param  	  		    IntNumber Interrupt number 
 * @param               HandlerAddr interrupt handler address
 * @return 		        true or false, when the table is full, return false
 * 
 */ 
DWORD install_irq( DWORD IntNumber, void *HandlerAddr )
{
    DWORD i;
    DWORD *vect_addr;
    DWORD *vect_cntl;
      
    VICIntEnClr = 1 << IntNumber;	/* Disable Interrupt */
    
    for ( i = 0; i < VIC_SIZE; i++ )
    {
	/* find first un-assigned VIC address for the handler */

	vect_addr = (DWORD *)(VIC_BASE_ADDR + VECT_ADDR_INDEX + i*4);
	vect_cntl = (DWORD *)(VIC_BASE_ADDR + VECT_CNTL_INDEX + i*4);
	if ( *vect_addr == (DWORD)NULL )
	{
	    *vect_addr = (DWORD)HandlerAddr;	/* set interrupt vector */
	    *vect_cntl = (DWORD)(IRQ_SLOT_EN | IntNumber);
	    break;
	}
    }
    if ( i == VIC_SIZE )
    {
	return( FALSE );		/* fatal error, can't find empty vector slot */
    }
    VICIntEnable = 1 << IntNumber;	/* Enable Interrupt */
    return( TRUE );
}

/** uninstall_irq
 *
 * @brief		Uninstall interrupt handler
 * @brief		Find the interrupt handler installed in the VIC
 * @brief		based on the interrupt number, set the location
 * @brief		back to NULL to uninstall it.
 * @param 	    IntNumber Interrupt number
 * @return		true or false, when the interrupt number is not found, return false
 * 
 */ 
DWORD uninstall_irq( DWORD IntNumber )
{
    DWORD i;
    DWORD *vect_addr;
    DWORD *vect_cntl;
      
    VICIntEnClr = 1 << IntNumber;	/* Disable Interrupt */
    
    for ( i = 0; i < VIC_SIZE; i++ )
    {
	/* find first un-assigned VIC address for the handler */
	vect_addr = (DWORD *)(VIC_BASE_ADDR + VECT_ADDR_INDEX + i*4);
	vect_cntl = (DWORD *)(VIC_BASE_ADDR + VECT_CNTL_INDEX + i*4);
	if ( (*vect_cntl & ~IRQ_SLOT_EN ) == IntNumber )
	{
	    *vect_addr = (DWORD)NULL;	/* clear the VIC entry in the VIC table */
	    *vect_cntl &= ~IRQ_SLOT_EN;	/* disable SLOT_EN bit */	
	    break;
	}
    }
    if ( i == VIC_SIZE )
    {
	return( FALSE );		/* fatal error, can't find interrupt number 
					in vector slot */
    }
    VICIntEnable = 1 << IntNumber;	/* Enable Interrupt */
    return( TRUE );
}

