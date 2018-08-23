#include "r_include.h"


uint32_t OSTM0_Tick=0;
const uint32_t OSTM_1MS =40000; //40000 1ms , 4000 10ms 


void OSTM0_Init(uint32_t value)
{
	OSTM0.CTL=0x00;
	
	OSTM0.CMP=value;
	
	//ICOSTM0 =0x0007;		//set OSTM0 to lowest level interrupt priority
	//ICOSTM0&=0xFFF0; 		//set OSTM0 to highest level interrupt priority

	RFOSTM0 =0;				//clear interrupt flag
	MKOSTM0 =1;				//disable interrupt 
	TBOSTM0 =1;				//set interrupt mode to table reference mode 
	MKOSTM0 =0;				//enable interrupt
}


void OSTM0_Start(void)
{
	OSTM0.TS=0x01;
}
void OSTM0_Stop(void)
{
	OSTM0.TT=0x01;
}



uint32_t  OSTM0_Get_Tick(void)
{
	return OSTM0_Tick;
}


uint8_t  OSTM0_Delay(uint32_t Delay_ms)
{
 uint32_t tickstart = 0;
 tickstart = OSTM0_Get_Tick();
  while((OSTM0_Get_Tick() - tickstart) < Delay_ms)
  {
  }
  return 1;
}





