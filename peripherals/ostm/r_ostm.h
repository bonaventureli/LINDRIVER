#ifndef OSTM_H
#define OSTM_H

extern uint32_t OSTM0_Tick;
extern const uint32_t OSTM_1MS;


void OSTM0_Init(uint32_t value);
void OSTM0_Start(void);

void OSTM0_Stop(void);



uint32_t  OSTM0_Get_Tick(void);


uint8_t  OSTM0_Delay(uint32_t Delay_ms);






#endif
