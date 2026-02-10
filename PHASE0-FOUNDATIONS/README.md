
<img width="1024" height="1024" alt="Gemini_Generated_Image_fftijlfftijlffti" src="https://github.com/user-attachments/assets/b9d7f791-4d3e-4b2c-ae22-7a78bf51ea65" />



# ⚡ Absolute Bare Metal Series
### *Mastering the Silicon: Register-Level STM32 Development*

This series is a comprehensive journey into the **ARM Cortex-M3** architecture. The core philosophy is **Zero Abstraction**: no HAL, no Standard Peripheral Libraries, and no CMSIS wrappers where possible. Every project is implemented by manipulating memory-mapped registers directly using the hardware reference manual.

## 🛠 The Engineering Stack
* **Target:** STM32F1 (ARM Cortex-M3 Core)
* **IDE:** Keil µVision 5
* **Compiler:** ARMCC (Version 5/6)
* **Documentation:** STM32F10xxx Reference Manual (RM0008)

---

## 🗺 Project Roadmap

### 🧱 LEVEL 1 — Absolute Basics (Board Bring-up)
1.  **Minimal Boot Project:** Startup code and memory map layout without CMSIS.
2.  **Blink LED:** Direct manipulation of `RCC_APB2ENR`, `GPIOC_CRH`, and `GPIOC_ODR`.
3.  **GPIO Input:** Reading button states via the `IDR` register.
4.  **Bit-Banding/Masking:** Implementing surgical bit control for atomic-like GPIO access.
5.  **External Interrupt (EXTI):** Mapping GPIO to the interrupt controller via `AFIO_EXTICR`.
6.  **SysTick Delay:** Utilizing the Cortex-M core timer for precise software blocking.
7.  **General Purpose Timer (TIM) Delay:** Configuring `PSC` and `ARR` for hardware-based timing.
8.  **PWM Output:** Hardware-automated signal generation for LEDs/Motors.
9.  **Millisecond Tick System:** Establishing a global timebase for system services.

### 🔌 LEVEL 2 — Communication Peripherals
10. **UART TX (Polling):** Calculating baud rates and managing the `USART_SR` status flags.
11. **UART TX/RX (Polling):** Full-duplex manual data exchange.
12. **UART Interrupt Driver:** Asynchronous communication using RXNE/TXE interrupts.
13. **SPI Master (Polling):** Synchronous data transfer for high-speed peripherals.
14. **SPI Master (Interrupt):** Offloading SPI management to the interrupt controller.
15. **I2C Master (Polling):** Implementing Start/Address/Ack/Stop sequences manually.
16. **I2C Master (Interrupt):** State-machine driven I2C communication.
17. **Mini Printf:** Developing a custom `printf` implementation over UART.

### ⚡ LEVEL 3 — Data Movement & Performance
18. **ADC Single Conversion:** Reading analog voltages using the `ADC_CR2` trigger.
19. **ADC Continuous + Timer:** Automating sampling with hardware timer triggers.
20. **DMA Memory-to-Peripheral:** Moving data arrays to peripherals with 0% CPU load.
21. **DMA Peripheral-to-Memory:** Streamlining ADC data collection via DMA.
22. **Zero-CPU UART:** Fully automated UART transmission using DMA channels.

### 🧠 LEVEL 4 — System & Reliability
23. **Independent Watchdog (IWDG):** System recovery from hardware/software hangs.
24. **Window Watchdog (WWDG):** Precise software execution timing enforcement.
25. **RTC Timekeeping:** Managing the Real-Time Clock for calendar functions.
26. **Low-Power Modes:** Implementing Sleep, Stop, and Standby for battery efficiency.
27. **Reset Cause Detection:** Identifying why the system restarted (POR/WWDG/IWDG).

### 🧩 LEVEL 5 — Professional-Level
28. **Custom Bootloader:** Creating a resident program to manage application jumps.
29. **Firmware Update (UART):** Over-the-air (OTA) style updates via serial link.
30. **Driver Framework:** Organizing register-level code into reusable, professional drivers.

---

## 📜 Principles of the Series
* **Manual Clock Gating:** Every peripheral starts "dead." We enable them bit-by-bit in the `RCC`.
* **Interrupt Hygiene:** Manual management of Pending (`PR`) and Status (`SR`) registers is mandatory.
* **Data Sheet First:** Every line of code is cross-referenced with the **RM0008 Reference Manual**.
* **Efficiency:** Optimizing for code size and CPU cycles by removing overhead.

---
*Developed as a rigorous study of embedded systems engineering.*

**Author:** Mohamed Ishauq
**Series:** The Absolute Bare-Metal Series
