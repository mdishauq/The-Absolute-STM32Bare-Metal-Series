# Phase 1 – First Contact with Hardware  
## The Absolute Bare-Metal Series

> **Goal:** Write, build, and run a **true bare-metal program** without HAL, CMSIS, Arduino, or any runtime — and control hardware using **only registers**.

This phase is about:
- Creating a minimal firmware
- Understanding what files are *actually* required
- Booting on real hardware
- Touching registers directly
- Blinking an LED with **zero libraries**

---

## What You Will Learn

By the end of this phase, you will:

- Build a bare-metal firmware from scratch
- Understand the role of:
  - `startup.s`
  - `linker.ld`
  - `main.c`
- Write a minimal bootable program
- Access registers using memory-mapped I/O
- Use `volatile` correctly
- Use bitwise operations to control hardware
- Blink an LED without any HAL or CMSIS

---

## Project Structure

```

Phase_1_First_Bare_Metal_Code/
├── linker.ld
├── startup.s
├── main.c
├── Makefile
└── README.md

````

---

## 1. The Absolute Minimum Files

A bare-metal system needs only:

- A linker script → describes memory
- Startup code → sets up RAM and jumps to main
- main.c → your application
- A build system → Makefile

There is **no standard library** and **no runtime** unless you add them.

---

## 2. Minimal `main.c`

This is the smallest valid C program:

```c
int main(void)
{
    while (1)
    {
        // Infinite loop
    }
}
````

This already runs on the CPU — if startup and linker are correct.

---

## 3. Why `volatile` is Mandatory for Hardware

Hardware registers can change **outside program control**.

So this is required:

```c
#define GPIO_ODR (*(volatile unsigned int*)0x4001080C)
```

Without `volatile`:

* The compiler may remove reads/writes
* Your code may simply stop working

> **Rule:** All memory-mapped registers must be `volatile`.

---

## 4. Bitwise Register Programming

Hardware registers control **multiple features in one 32-bit value**.

You must use masks:

```c
// Set bit
REG |=  (1 << 5);

// Clear bit
REG &= ~(1 << 5);

// Toggle bit
REG ^=  (1 << 5);
```

This is **not optional**. This is how all real firmware works.

---

## 5. Reading the Datasheet (Mandatory Skill)

Before writing code, you must find:

* RCC register for clock enable
* GPIO mode register
* GPIO output register
* Bit positions for each field

> The datasheet is the **real API** of the chip.

---

## 6. Example: GPIO Register Addresses (Example MCU)

Example (STM32-style):

```c
#define RCC_APB2ENR  (*(volatile unsigned int*)0x40021018)
#define GPIOC_CRH   (*(volatile unsigned int*)0x40011004)
#define GPIOC_ODR   (*(volatile unsigned int*)0x4001100C)
```

---

## 7. Enabling Peripheral Clock

Before using GPIO, you must enable its clock:

```c
RCC_APB2ENR |= (1 << 4);  // Enable GPIOC clock
```

---

## 8. Configuring GPIO as Output

```c
GPIOC_CRH &= ~(0xF << 20);  // Clear config bits
GPIOC_CRH |=  (0x1 << 20);  // Set output mode
```

---

## 9. Toggling the LED

```c
while (1)
{
    GPIOC_ODR ^= (1 << 13);  // Toggle pin
    for (volatile int i = 0; i < 500000; i++); // crude delay
}
```

---

## 10. Full Example `main.c`

```c
#define RCC_APB2ENR  (*(volatile unsigned int*)0x40021018)
#define GPIOC_CRH   (*(volatile unsigned int*)0x40011004)
#define GPIOC_ODR   (*(volatile unsigned int*)0x4001100C)

int main(void)
{
    // Enable GPIOC clock
    RCC_APB2ENR |= (1 << 4);

    // Configure PC13 as output
    GPIOC_CRH &= ~(0xF << 20);
    GPIOC_CRH |=  (0x1 << 20);

    while (1)
    {
        GPIOC_ODR ^= (1 << 13);

        for (volatile int i = 0; i < 500000; i++);
    }
}
```
---

## 11. What You Have Actually Achieved

You have:

* Booted a CPU with your own startup
* Used your own linker script
* Written code that talks directly to silicon
* Controlled hardware without any library
* Built a **true bare-metal system**

---

## 12. Important Engineering Notes

* This delay loop is **not accurate**
* This is **not low power**
* This is **not production code**

It is used only to prove:

> You can control hardware at the lowest level.

---

## 13. What Comes Next (Phase 2)

In Phase 2, we will dive into:

* CPU core registers
* Stack and stack frames
* Assembly and C interface
* Exception model
* HardFault debugging

---

## Philosophy Reminder

> Frameworks make you productive.
> Fundamentals make you powerful.

---

**Author:** Mohamed Ishauq
**Series:** The Absolute Bare-Metal Series
