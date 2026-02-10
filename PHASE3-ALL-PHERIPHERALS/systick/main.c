#include "stm32f10x.h"

// 1. Private Door to PC13 using Bit-Banding
#define LED_PC13 (*((volatile uint32_t*)0x422201B4))

// 2. The Interrupt Handler
// Hardware jumps here every 1 second
void SysTick_Handler(void) {
    LED_PC13 ^= 1; // Toggle the LED
}

// 3. Simple Error Catcher
// If the CPU crashes, it usually ends up here
void HardFault_Handler(void) {
    while(1);
}

int main(void) {
    // --- STEP A: Enable GPIO Clock ---
    // Port C is on APB2, Bit 4
    RCC->APB2ENR |= (1 << 4);
    
    // --- STEP B: Configure PC13 as Output ---
    // Clear bits 20-23, then set as Output Push-Pull 2MHz (0x2)
    GPIOC->CRH &= ~(uint32_t)(0xF << 20);
    GPIOC->CRH |=  (0x2 << 20);

    // --- STEP C: Configure SysTick ---
    // At 72MHz, we use the /8 divider to get 9MHz.
    // 9,000,000 ticks = 1 second.
    SysTick->LOAD = 9000000 - 1; 
    SysTick->VAL  = 0;          // Reset current value
    
    // CTRL Bits: 
    // Bit 0: Enable = 1
    // Bit 1: TickInt = 1 (Interrupt On)
    // Bit 2: ClockSource = 0 (Use AHB/8 = 9MHz)
    SysTick->CTRL = 0x03; 

    // --- STEP D: Enable Master Interrupt Switch ---
    __enable_irq();

    while(1) {
        // CPU waits here. When SysTick hits 0, it jumps to the Handler.
        __WFI(); 
    }
}
