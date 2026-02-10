#include "stm32f10x.h"

void setup(void);
void EXTI0_IRQHandler(void);


int main(){
	
	int count = 0;
	setup();
	

	while(1){
	
	if(count == 214748364){
		count = 0;
		continue;
	}	
	count++;
		
	}
	

}



void setup(void){
    // 1. Enable Clocks
    RCC->APB2ENR |= (1 << 0); // AFIO
    RCC->APB2ENR |= (1 << 2); // GPIOA
    RCC->APB2ENR |= (1 << 4); // GPIOC

    // 2. PA0: Input with Pull-up
    GPIOA->CRL &= ~(uint32_t)(0xF << 0);
    GPIOA->CRL |= (0x8 << 0);  // Binary 1000: Input with pull-up/down
    GPIOA->ODR |= (1 << 0);    // Set ODR=1 to select PULL-UP (pin stays at 3.3V)

    // 3. PC13: Output
    GPIOC->CRH &= ~(uint32_t)(0xF << 20);
    GPIOC->CRH |= (0x1 << 20); // Output 10MHz

    // 4. Map PA0 to EXTI0
    AFIO->EXTICR[0] &= ~(uint32_t)(0xF << 0); 

    // 5. Configure EXTI Line 0
    EXTI->IMR |= (1 << 0);     // ENABLE the mask (1 = On)
    EXTI->FTSR |= (1 << 0);    // Falling edge ON (Press to GND)
    EXTI->RTSR &= ~(uint32_t)(1 << 0);   // Rising edge OFF

    // 6. THE MISSING LINK: Enable in NVIC
    NVIC_EnableIRQ(EXTI0_IRQn); 
}

//interrupt handle
void EXTI0_IRQHandler(void){

	if(EXTI->PR & (1 << 0)){
		
		GPIOC->ODR ^= (1 << 13);
		
		EXTI->PR |= (1 << 0);
		
	}
	
}


