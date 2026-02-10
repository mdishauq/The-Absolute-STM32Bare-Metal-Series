#include "stm32f10x.h"

void clock_init(void);
void pin_init(void);
void SysTick_Handler(void);

int main(){

	clock_init();
	pin_init();
	SysTick->LOAD = 9000000 - 1;
	SysTick->VAL = 0;
	SysTick->CTRL = (1 << 0) | (1 << 1);
	while(1){
	 __NOP();
	}


}


void clock_init(){
    // 1. Switch System Clock back to HSI (Internal 8MHz)
    RCC->CFGR &= ~(uint32_t)(0x3 << 0); // SW bits to 00 (HSI)
    while(((RCC->CFGR >> 2) & 0x3) != 0x0); // Wait for SWS to show HSI
    
    // 2. Turn OFF the PLL so we can change the multiplier
    RCC->CR &= ~(1 << 24); // PLLOFF
    
    // 3. Now perform your setup
    RCC->CR |= (1 << 16); // HSE ON
    while(!(RCC->CR & (1 << 17))); 

    FLASH->ACR = 0x02; 

    // Clear and set APB1
    RCC->CFGR &= ~(uint32_t)(0x7 << 8);
    RCC->CFGR |= (1 << 10); 

    // CLEAR AND SET PLL MULTIPLIER (Set to x2 for the test)
    RCC->CFGR &= ~(uint32_t)(0xF << 18);
    RCC->CFGR |= (0x0 << 18); // x2

    RCC->CFGR |= (1 << 16); // HSE as source
    
    // 4. Turn PLL back ON and wait for it to lock
    RCC->CR |= (1 << 24);
    while(!(RCC->CR & (1 << 25))); 

    // 5. Switch System Clock to the new PLL configuration
    RCC->CFGR |= (1 << 1); // Select PLL (10)
    while(((RCC->CFGR >> 2) & 0x3) != 0x2);
}

void pin_init(){
	RCC->APB2ENR |= (1 << 4);//enable the port c
	GPIOC->CRH &= ~(uint32_t)(0xF << 20);
	GPIOC->CRH |= (1 << 20);//
}

void SysTick_Handler(void){
	GPIOC->ODR ^= (1 << 13);
}

