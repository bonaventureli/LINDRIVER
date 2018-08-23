#include    "r_include.h"

#ifdef __IAR_SYSTEMS_ICC__
	#include <intrinsics.h>
#endif




/******************************************************************************
Imported global variables and functions (from other files)
******************************************************************************/


/******************************************************************************
Macro definitions
******************************************************************************/


/******************************************************************************
Exported global variables and functions (to be accessed by other files)
******************************************************************************/
        void    R_CLOCK_Init( void );


/******************************************************************************
Private global variables and functions
******************************************************************************/
static  void    osc_clock( void );
static  void    set_clock_domain( void );


/******************************************************************************
* Function Name : void R_CLOCK_Init( void )
* Description   : This function initializes the clock.
* Argument      : none
* Return Value  : none
******************************************************************************/
void R_CLOCK_Init( void )
{
    osc_clock();                                /* Clock oscillation         */
    set_clock_domain();                         /* Domain clock setting      */
}


/******************************************************************************
* Function Name : static void osc_clock( void )
* Description   : This function oscillates the clock (main , sub and PLL clock).
* Argument      : none
* Return Value  : none
******************************************************************************/
static void osc_clock( void )
{
    uint32_t    reg32_value;

    /* Amplification gain of the MainOSC
    MOSCC  - MainOSC Control Register
    b31:b2               - Reserved set to 0
    b0       MOSCAMPSEL  - MainOSC Frequency - 8 MHz */
    MOSCC                = 0x00000002UL;


    /* Main OSC stabilization time setup
    MOSCST - MainOSC Stabilization Time Register
    b31:b17              - Reserved set to 0
    b16:b 0  MOSCCLKST   - Count value for the MainOSC stabilization counter - (1FFFFH / fRH) */
    MOSCST               = 0x0001FFFFUL;


    /* Main OSC on
    MOSCE  - MainOSC Enable Register
    b31:b2               - Reserved set to 0
    b1       MOSCDISTRG  - MainOSC Disable Trigger - no function
    b0       MOSCENTRG   - MainOSC Enable Trigger  - starts MainOSC (Trigger bit) */
    do
    {
        reg32_value      = 0x00000001UL;
        PROTCMD0         = 0x000000A5UL;             /* Protection release the MOSCE register */
        MOSCE            = reg32_value;
        MOSCE            = ~reg32_value;
        MOSCE            = reg32_value;
    } while ( PROTS0 != 0x00000000UL );
    while ( (MOSCS & 0x00000004UL) != 0x00000004UL )
    {
        /* Wait for active of MainOSC. */
    }


    /* Set the PLL output clock frequencies fPPLLCLK and fCPLLCLK
    PLLC   - PLLC Control Register
    b31:b17              - Reserved set to 0
    b16      OUTBSEL     - Set to 1
    b15:b13              - Reserved set to 0
    b12:b11  M           - 8 MHz <= fX <= 24 MHz
    b10:b 8  PA          - 60 MHz to 80 MHz
    b 7:b 6              - Reserved set to 0
    b 5:b 0  N           - Set to 7 (PLL clock 80MHz) */
    PLLC                 = 0x00000A27UL;


    /* PLL on
    PLLE   - MainOSC Enable Register
    b31:b 2              - Reserved set to 0
    b 1      PLLDISTRG   - PLL Disable Trigger - no function
    b 0      PLLENTRG    - PLL Enable Trigger  - Starts PLL (Trigger bit) */
    do
    {
        reg32_value      = 0x00000001UL;
        PROTCMD1         = 0x000000A5UL;             /* Protection release the MOSCE register */
        PLLE             = reg32_value;
        PLLE             = ~reg32_value;
        PLLE             = reg32_value;
    } while ( PROTS1 != 0x00000000UL );
    while ( (PLLS & 0x00000004UL) != 0x00000004UL )
    {
        /* Wait for active of PLL. */
    }
    /*No subosc, do nothing*/

}


/******************************************************************************
* Function Name : static void set_clock_domain( void )
* Description   : This function sets the domain clock.
* Argument      : none
* Return Value  : none
******************************************************************************/
static void set_clock_domain( void )
{
    uint32_t    reg32_value;

    /* Source Clock Setting for C_ISO_CPUCLK
    CKSC_CPUCLKS_CTL - C_ISO_CPUCLK Source Clock Selection Register
    b31:b 2                        - Reserved set to 0
    b 1:b 0            CPUCLKSCSID - Source Clock Setting for C_ISO_CPUCLK - CPPLLCLK */
    do
    {
        reg32_value                = 0x00000003UL;
        PROTCMD1                   = 0x000000A5UL;   /* Protection release the CKSC_CPUCLKS_CTL register */
        CKSC_CPUCLKS_CTL           = reg32_value;
        CKSC_CPUCLKS_CTL           = ~reg32_value;
        CKSC_CPUCLKS_CTL           = reg32_value;
    } while ( PROTS1 != 0x00000000UL );
    while ( CKSC_CPUCLKS_ACT != reg32_value )
    {
        /* Wait for CKSC_CPUCLKS_CTL to set. */
    }

    /* Clock Divider Setting for C_ISO_CPUCLK
    CKSC_CPUCLKD_CTL - C_ISO_CPUCLK Divided Clock Selection Register
    b31:b 2                        - Reserved set to 0
    b 1:b 0            CPUCLKDCSID - Source Clock Setting for C_ISO_CPUCLK - CKSC_CPUCLKS_CTL selection / 1 */
    do
    {
        reg32_value                = 0x00000001UL;
        PROTCMD1                   = 0x000000A5UL;   /* Protection release the CKSC_CPUCLKD_CTL register */
        CKSC_CPUCLKD_CTL           = reg32_value;
        CKSC_CPUCLKD_CTL           = ~reg32_value;
        CKSC_CPUCLKD_CTL           = reg32_value;
    } while ( PROTS1 != 0x00000000UL );
    while ( CKSC_CPUCLKD_ACT != reg32_value )
    {
        /* Waiting for CKSC_CPUCLKD_CTL to set. */
    }

    /* Source Clock Setting for C_ISO_PERI1
    CKSC_IPERI1S_CTL - C_ISO_PERI1 Source Clock Selection Register
    b31:b 2                        - Reserved set to 0
    b 1:b 0            IPERI1SCSID - Source Clock Setting for C_ISO_PERI1 - PPLLCLK */
    do
    {
        reg32_value                = 0x00000002UL;
        PROTCMD1                   = 0x000000A5UL;   /* Protection release the CKSC_IPERI1S_CTL register */
        CKSC_IPERI1S_CTL           = reg32_value;
        CKSC_IPERI1S_CTL           = ~reg32_value;
        CKSC_IPERI1S_CTL           = reg32_value;
    } while ( PROTS1 != 0x00000000UL );
    while ( CKSC_IPERI1S_ACT != reg32_value )
    {
        /* Waiting for CKSC_IPERI1S_CTL to set. */
    }

    /* Source Clock Setting for C_ISO_PERI2
    CKSC_IPERI2S_CTL - C_ISO_PERI2 Source Clock Selection Register
    b31:b 2                        - Reserved set to 0
    b 1:b 0            IPERI2SCSID - Source Clock Setting for C_ISO_PERI2 - PPLLCLK2 */
    do
    {
        reg32_value                = 0x00000002UL;
        PROTCMD1                   = 0x000000A5UL;   /* Protection release the CKSC_IPERI2S_CTL register */
        CKSC_IPERI2S_CTL           = reg32_value;
        CKSC_IPERI2S_CTL           = ~reg32_value;
        CKSC_IPERI2S_CTL           = reg32_value;
    } while ( PROTS1 != 0x00000000UL );
    while ( CKSC_IPERI2S_ACT != reg32_value )
    {
        /* Waiting for CKSC_IPERI2S_CTL to set. */
    }

    /* Source Clock Setting for C_ISO_CSI
    CKSC_ICSIS_CTL - C_ISO_CSI Source Clock Selection Register
    b31:b 2                        - Reserved set to 0
    b 1:b 0              ICSISCSID - Source Clock Setting for C_ISO_CSI - PPLLCLK */
    do
    {
        reg32_value                = 0x00000002UL;
        PROTCMD1                   = 0x000000A5UL;   /* Protection release the CKSC_ICSIS_CTL register */
        CKSC_ICSIS_CTL             = reg32_value;
        CKSC_ICSIS_CTL             = ~reg32_value;
        CKSC_ICSIS_CTL             = reg32_value;
    } while ( PROTS1 != 0x00000000UL );
    while ( CKSC_ICSIS_ACT != reg32_value )
    {
        /* Waiting for CKSC_ICSIS_CTL to set. */
    }

    /* Source Clock Setting for   C_ISO_LIN  
    CKSC_ILINS_CTL	 -   C_ISO_LIN   Source Clock Selection Register
    b31:b 2                        - Reserved set to 0
    b 1:b 0              ILINSCSID - Source Clock Setting for  C_ISO_LIN  - PPLLCLK/2 */

    do
    {
        reg32_value                = 0x00000003UL;
        PROTCMD1                   = 0x000000A5UL;   /* Protection release the CKSC_ILINS_CTL register */
        CKSC_ILINS_CTL             = reg32_value;
        CKSC_ILINS_CTL             = ~reg32_value;
        CKSC_ILINS_CTL             = reg32_value;
    } while ( PROTS1 != 0x00000000UL );
    while ( CKSC_ILINS_CTL != reg32_value )
    {
        /* Waiting for CKSC_ILINS_CTL to set. */
    }


	
}

