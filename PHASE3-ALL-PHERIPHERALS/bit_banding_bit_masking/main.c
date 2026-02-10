#include<stdint.h>
#include "stm32f10x.h"

#define PH_BASE 0x40000000
#define AL_BASE 0x42000000
#define BIT_BAND_ADD(ADD, PIN) (AL_BASE + (((uint32_t)ADD - PH_BASE) * 32) + (PIN * 4))
#define GET_BIT_POINTER(ADD, PIN) (*((volatile uint32_t*)BIT_BAND_ADD(ADD, PIN)))

#define PTC_PN13 GET_BIT_POINTER(&GPIOC->ODR, 13)

void delay(int time);

int main(){

	//init
	RCC->APB2ENR |= (1<<4);//PORT C
	
	//pc13
	GPIOC->CRH &= ~(uint32_t)(0xF << 20);
  GPIOC->CRH |=  (0x2 << 20);

	while(1){
		
		PTC_PN13 = 1;
		delay(4000000);
		PTC_PN13 =0;
		delay(4000000);
		
	}




}

void delay(int time){
	
	while(time)
		time--;
}
 
