/******************************************************************************
* File Name     : r_main.c
* Version       : 1.0
* Device(s)     : R7F7010254 RH850/F1L
* Tool-Chain    : CS+ V6.00
* Description   : This file is a main sample of the LIN function.
*******************************************************************************
*******************************************************************************
* History       : DD.MM.YYYY Version Description
*               : 16.08.2018 1.00    First Release
******************************************************************************/

/******************************************************************************
Includes <System Includes>
******************************************************************************/

#include 	"r_include.h"

/******************************************************************************
Imported global variables and functions (from other files)
******************************************************************************/
extern  void        R_CLOCK_Init( void );

/******************************************************************************
Macro definitions
******************************************************************************/

/******************************************************************************
Exported global variables and functions (to be accessed by other files)
******************************************************************************/


/******************************************************************************
Private global variables and functions
******************************************************************************/
void		main( void );
void 		HW_Init (void);


/******************************************************************************
* Function Name : void main( void )
* Description   : This function is sample main processing.
* Argument      : none
* Return Value  : none
******************************************************************************/
void main( void )
{
	uint8_t i;
    /**************************************************/
    /* initialize                                     */
    /**************************************************/
	HW_Init();
	LIN1_EN;
	OSTM0_Delay(100);	
	
    while (1U)
    {
		for (i=0;i<4;i++)
		{
			RLIN3_Init(RLIN3_0);
			RLIN3_Tx_Frame(RLIN3_0,Lin_NAD_Info[i],Lin_Tx_Buffer);
			OSTM0_Delay(10);   
		}	    
    }

}



void HW_Init (void)
{


    /* interrupt disable */
    __DI();
    /* clock setting */
    R_CLOCK_Init();
    /* interrupt enable */
    __EI();

    OSTM0_Init(OSTM_1MS);
    OSTM0_Start();	

}




