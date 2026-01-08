
<img width="1024" height="1024" alt="Gemini_Generated_Image_fftijlfftijlffti" src="https://github.com/user-attachments/assets/b9d7f791-4d3e-4b2c-ae22-7a78bf51ea65" />



# Phase 0 – Foundations  
## The Absolute Bare-Metal Series

> **Goal:** Build a complete mental model of what really happens between *power-on* and `main()` in a bare-metal embedded system.

This phase does **not** use:
- HAL
- CMSIS
- Arduino
- Any OS or framework

This phase teaches **how the machine actually boots and runs your code**.

---

## What You Will Learn

By the end of this phase, you will understand:

- What bare-metal programming truly means
- How a microcontroller is structured internally
- How the build toolchain works
- What ELF / HEX / BIN files really are
- How memory is organized and why it matters
- What a linker script does
- What startup code does
- How the CPU reaches `main()`

---

## 1. What is Bare-Metal Programming?

**Bare-metal programming means running your code directly on the hardware without any operating system, runtime, or hardware abstraction layer.**

Your code:
- Talks directly to hardware registers
- Controls memory layout
- Controls startup sequence
- Controls interrupts
- Owns the entire machine

No Linux.  
No Arduino.  
No HAL.  
No RTOS.

Only:
- CPU
- Flash
- RAM
- Your code

### Bare-metal vs OS-based System

| Feature | Bare-metal | OS-based |
|--------|------------|-----------|
| Boot time | Instant | Slow |
| Memory | Fully controlled | Virtualized |
| Determinism | 100% | Not guaranteed |
| Power usage | Minimal | Higher |
| Hardware access | Direct | Indirect |

---

## 2. Inside a Microcontroller

A typical microcontroller contains:

- CPU core (e.g., ARM Cortex-M)
- Flash memory (program storage)
- RAM (stack, heap, variables)
- Peripherals (GPIO, UART, SPI, I2C, Timers, etc.)
- Bus system (AHB, APB, etc.)

### Harvard Architecture

- Instruction bus fetches from Flash
- Data bus accesses RAM and peripherals

### Memory-Mapped I/O

Peripherals are accessed through memory addresses:

```c
#define GPIOA_ODR (*(volatile unsigned int*)0x4001080C)
````

Writing to this address writes directly to hardware.

---

## 3. The Build Toolchain Explained

### What actually happens when you build?

```
main.c     → compiler   → main.o
startup.s  → assembler  → startup.o
linker     → firmware.elf
objcopy    → firmware.bin / firmware.hex
```

### Important Tools

* `arm-none-eabi-gcc` → Compiler
* `arm-none-eabi-ld` → Linker
* `arm-none-eabi-objcopy` → Format conversion
* `arm-none-eabi-objdump` → Disassembly and inspection

---

## 4. ELF vs HEX vs BIN

| Format | Contains                            | Used for  |
| ------ | ----------------------------------- | --------- |
| ELF    | Full program + symbols + debug info | Debugging |
| BIN    | Raw binary image                    | Flashing  |
| HEX    | ASCII encoded binary                | Flashing  |

### Conversion Commands

```bash
arm-none-eabi-objcopy -O binary firmware.elf firmware.bin
arm-none-eabi-objcopy -O ihex   firmware.elf firmware.hex
```

> You **do not flash ELF**. You flash BIN or HEX.

---

## 5. Memory Map of a Microcontroller

Typical ARM Cortex-M memory map:

```
0x08000000 → Flash
0x20000000 → RAM
0x40000000 → Peripherals
```

### Why this matters

Your program must be placed:

* Code in Flash
* Variables in RAM
* Stack in RAM

This is controlled by the **linker script**.

---

## 6. The Linker Script (Critical Concept)

### What is a linker script?

The linker script tells the linker:

* Where Flash is
* Where RAM is
* Where to place:

  * Code (.text)
  * Initialized data (.data)
  * Uninitialized data (.bss)
  * Stack and heap

### Minimal Example

```ld
MEMORY
{
  FLASH (rx) : ORIGIN = 0x08000000, LENGTH = 128K
  RAM (rwx)  : ORIGIN = 0x20000000, LENGTH = 20K
}

SECTIONS
{
  .text : {
    *(.isr_vector)
    *(.text*)
  } > FLASH

  .data : { *(.data*) } > RAM
  .bss  : { *(.bss*)  } > RAM
}
```

> Without a linker script, your program does not know where to live in memory.

---

## 7. Startup Code

### What happens on reset?

When the CPU resets:

1. It loads Stack Pointer from address `0x00000000`
2. It loads Program Counter from address `0x00000004`
3. It jumps to the reset handler

### Startup code must:

* Set up stack pointer
* Copy `.data` from Flash to RAM
* Zero `.bss`
* Call `main()`

### Minimal Vector Table Example

```c
__attribute__((section(".isr_vector")))
void (*vectors[])(void) = {
    (void*)0x20005000,  // Initial stack pointer
    Reset_Handler
};
```

---

## 8. From Power-On to `main()`

### Complete Boot Sequence

1. Power is applied
2. CPU reads:

   * SP from address `0x00000000`
   * PC from address `0x00000004`
3. CPU jumps to `Reset_Handler`
4. Startup code:

   * Initializes RAM
   * Sets up stack
5. Calls `main()`
6. Your program starts running

> **Important:** `main()` is not the beginning of the program.
> It is just another function called by startup code.

---

## What You Should Understand After Phase 0

* How firmware is built
* Why linker scripts exist
* Why startup code exists
* How the CPU boots
* How memory layout works
* What ELF / BIN / HEX really are

---

## What Comes Next (Phase 1)

In Phase 1, we will:

* Write a minimal bare-metal program
* Build without any library or HAL
* Blink an LED using raw registers
* Touch hardware for the first time

---

## Philosophy of This Series

> Most tutorials teach you **how to use APIs**.
> This series teaches you **how the machine actually works**.

---

**Author:** Mohamed Ishauq
**Series:** The Absolute Bare-Metal Series
