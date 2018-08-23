#include "r_include.h"





#pragma interrupt INTOSTM0 ( enable = false, channel = 76, callt = false, fpu = false )
void INTOSTM0(void);


/******************************************************************************
* Function Name : void INTOSTM0 ( void )
* Description   : This function is INTOSTM0 interrupt processing. (table refer.)
*               : INTOSTM0
* Argument      : none
* Return Value  : none
******************************************************************************/
void INTOSTM0(void)
{
	
	OSTM0_Tick++;
	if(OSTM0_Tick>0xffffff)
	OSTM0_Tick=0;	

}









