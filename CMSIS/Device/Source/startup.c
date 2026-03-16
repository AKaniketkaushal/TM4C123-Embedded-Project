#include <stdint.h>
#include "hw_nvic.h"
#include "hw_types.h"

void Reset_Handler(void);
void NMI_Handler(void);
void HardFault_Handler(void);
void IntDefaultHandler(void);
void MemManage_Handler(void);
void BusFault_Handler(void);
void UsageFault_Handler(void);
void DebugMon_Handler(void);
extern void vPortSVCHandler(void);     
extern void xPortPendSVHandler(void);   
extern void xPortSysTickHandler(void);  

extern int main(void);
uint32_t pui_stack[128];
extern uint32_t __stack;

__attribute__((section(".isr_vector"))) void (*const __Vectors[])(void) = {

    (void (*)(void))(&__stack), // The initial stack pointer
    Reset_Handler,              // The reset handler
    NMI_Handler,                // The NMI handler
    HardFault_Handler,          // The hard fault handler
    MemManage_Handler,          // The MPU fault handler
    BusFault_Handler,           // The bus fault handler
    UsageFault_Handler,         // The usage fault handler
    0,                          // Reserved
    0,                          // Reserved
    0,                          // Reserved
    0,                          // Reserved
    vPortSVCHandler,            // SVCall handler
    DebugMon_Handler,           // Debug monitor handler
    0,                          // Reserved
    xPortPendSVHandler,         // The PendSV handler
    xPortSysTickHandler,            // The SysTick handler
    IntDefaultHandler,          // GPIO Port A
    IntDefaultHandler,          // GPIO Port B
    IntDefaultHandler,          // GPIO Port C
    IntDefaultHandler,          // GPIO Port D
    IntDefaultHandler,          // GPIO Port E
    IntDefaultHandler,          // UART0 Rx and Tx
    IntDefaultHandler,          // UART1 Rx and Tx
    IntDefaultHandler,          // SSI0 Rx and Tx
    IntDefaultHandler,          // I2C0 Master and Slave
    IntDefaultHandler,          // PWM Fault
    IntDefaultHandler,          // PWM Generator 0
    IntDefaultHandler,          // PWM Generator 1
    IntDefaultHandler,          // PWM Generator 2
    IntDefaultHandler,          // Quadrature Encoder 0
    IntDefaultHandler,          // ADC Sequence 0
    IntDefaultHandler,          // ADC Sequence 1
    IntDefaultHandler,          // ADC Sequence 2
    IntDefaultHandler,          // ADC Sequence 3
    IntDefaultHandler,          // Watchdog timer
    IntDefaultHandler,          // Timer 0 subtimer A
    IntDefaultHandler,          // Timer 0 subtimer B
    IntDefaultHandler,          // Timer 1 subtimer A
    IntDefaultHandler,          // Timer 1 subtimer B
    IntDefaultHandler,          // Timer 2 subtimer A
    IntDefaultHandler,          // Timer 2 subtimer B
    IntDefaultHandler,          // Analog Comparator 0
    IntDefaultHandler,          // Analog Comparator 1
    IntDefaultHandler,          // Analog Comparator 2
    IntDefaultHandler,          // System Control (PLL, OSC, BO)
    IntDefaultHandler,          // FLASH Control
    IntDefaultHandler,          // GPIO Port F
    IntDefaultHandler,          // GPIO Port G
    IntDefaultHandler,          // GPIO Port H
    IntDefaultHandler,          // UART2 Rx and Tx
    IntDefaultHandler,          // SSI1 Rx and Tx
    IntDefaultHandler,          // Timer 3 subtimer A
    IntDefaultHandler,          // Timer 3 subtimer B
    IntDefaultHandler,          // I2C1 Master and Slave
    IntDefaultHandler,          // Quadrature Encoder 1
    IntDefaultHandler,          // CAN0
    IntDefaultHandler,          // CAN1
    0,                          // Reserved
    0,                          // Reserved
    IntDefaultHandler,          // Hibernate
    IntDefaultHandler,          // USB0
    IntDefaultHandler,          // PWM Generator 3
    IntDefaultHandler,          // uDMA Software Transfer
    IntDefaultHandler,          // uDMA Error
    IntDefaultHandler,          // ADC1 Sequence 0
    IntDefaultHandler,          // ADC1 Sequence 1
    IntDefaultHandler,          // ADC1 Sequence 2
    IntDefaultHandler,          // ADC1 Sequence 3
    0,                          // Reserved
    0,                          // Reserved
    IntDefaultHandler,          // GPIO Port J
    IntDefaultHandler,          // GPIO Port K
    IntDefaultHandler,          // GPIO Port L
    IntDefaultHandler,          // SSI2 Rx and Tx
    IntDefaultHandler,          // SSI3 Rx and Tx
    IntDefaultHandler,          // UART3 Rx and Tx
    IntDefaultHandler,          // UART4 Rx and Tx
    IntDefaultHandler,          // UART5 Rx and Tx
    IntDefaultHandler,          // UART6 Rx and Tx
    IntDefaultHandler,          // UART7 Rx and Tx
    0,                          // Reserved
    0,                          // Reserved
    0,                          // Reserved
    0,                          // Reserved
    IntDefaultHandler,          // I2C2 Master and Slave
    IntDefaultHandler,          // I2C3 Master and Slave
    IntDefaultHandler,          // Timer 4 subtimer A
    IntDefaultHandler,          // Timer 4 subtimer B
    0,                          // Reserved
    0,                          // Reserved
    0,                          // Reserved
    0,                          // Reserved
    0,                          // Reserved
    0,                          // Reserved
    0,                          // Reserved
    0,                          // Reserved
    0,                          // Reserved
    0,                          // Reserved
    0,                          // Reserved
    0,                          // Reserved
    0,                          // Reserved
    0,                          // Reserved
    0,                          // Reserved
    0,                          // Reserved
    0,                          // Reserved
    0,                          // Reserved
    0,                          // Reserved
    0,                          // Reserved
    IntDefaultHandler,          // Timer 5 subtimer A
    IntDefaultHandler,          // Timer 5 subtimer B
    IntDefaultHandler,          // Wide Timer 0 subtimer A
    IntDefaultHandler,          // Wide Timer 0 subtimer B
    IntDefaultHandler,          // Wide Timer 1 subtimer A
    IntDefaultHandler,          // Wide Timer 1 subtimer B
    IntDefaultHandler,          // Wide Timer 2 subtimer A
    IntDefaultHandler,          // Wide Timer 2 subtimer B
    IntDefaultHandler,          // Wide Timer 3 subtimer A
    IntDefaultHandler,          // Wide Timer 3 subtimer B
    IntDefaultHandler,          // Wide Timer 4 subtimer A
    IntDefaultHandler,          // Wide Timer 4 subtimer B
    IntDefaultHandler,          // Wide Timer 5 subtimer A
    IntDefaultHandler,          // Wide Timer 5 subtimer B
    IntDefaultHandler,          // FPU
    0,                          // Reserved
    0,                          // Reserved
    IntDefaultHandler,          // I2C4 Master and Slave
    IntDefaultHandler,          // I2C5 Master and Slave
    IntDefaultHandler,          // GPIO Port M
    IntDefaultHandler,          // GPIO Port N
    IntDefaultHandler,          // Quadrature Encoder 2
    0,                          // Reserved
    0,                          // Reserved
    IntDefaultHandler,          // GPIO Port P (Summary or P0)
    IntDefaultHandler,          // GPIO Port P1
    IntDefaultHandler,          // GPIO Port P2
    IntDefaultHandler,          // GPIO Port P3
    IntDefaultHandler,          // GPIO Port P4
    IntDefaultHandler,          // GPIO Port P5
    IntDefaultHandler,          // GPIO Port P6
    IntDefaultHandler,          // GPIO Port P7
    IntDefaultHandler,          // GPIO Port Q (Summary or Q0)
    IntDefaultHandler,          // GPIO Port Q1
    IntDefaultHandler,          // GPIO Port Q2
    IntDefaultHandler,          // GPIO Port Q3
    IntDefaultHandler,          // GPIO Port Q4
    IntDefaultHandler,          // GPIO Port Q5
    IntDefaultHandler,          // GPIO Port Q6
    IntDefaultHandler,          // GPIO Port Q7
    IntDefaultHandler,          // GPIO Port R
    IntDefaultHandler,          // GPIO Port S
    IntDefaultHandler,          // PWM 1 Generator 0
    IntDefaultHandler,          // PWM 1 Generator 1
    IntDefaultHandler,          // PWM 1 Generator 2
    IntDefaultHandler,          // PWM 1 Generator 3
    IntDefaultHandler           // PWM 1 Fault

};

extern int __text_start__;
extern int __ram_vectors_start__;
extern int __bss_start__;
extern int __bss_end__;
extern int __etext;
extern int __data_start__;
extern int __data_end__;

void Reset_Handler(void)
{

    uint32_t *src = &__etext;
    uint32_t *dest = &__data_start__;

    while (dest < (uint32_t *)&__data_end__)
    {
        *dest++ = *src++;
    }

    __asm("    ldr     r0, =__bss_start__\n"
          "    ldr     r1, =__bss_end__\n"
          "    mov     r2, #0\n"
          "    .thumb_func\n"

          "zero_loop:\n"
          "        cmp     r0, r1\n"
          "        it      lt\n"
          "        strlt   r2, [r0], #4\n"
          "        blt     zero_loop");

    src = (uint32_t *)&__text_start__;
    dest = (uint32_t *)&__ram_vectors_start__;
    for (int i = 0; i < 155; i++)
    {
        dest[i] = src[i];
    }

    HWREG(NVIC_VTABLE) = (uint32_t)&__ram_vectors_start__;
    HWREG(NVIC_CPAC) = ((HWREG(NVIC_CPAC) &
                         ~(NVIC_CPAC_CP10_M | NVIC_CPAC_CP11_M)) |
                        NVIC_CPAC_CP10_FULL | NVIC_CPAC_CP11_FULL);

    main();
}

__attribute__((weak)) void NMI_Handler(void)
 {
    while (1)
    {
        
    }
    
 }
__attribute__((weak)) void HardFault_Handler(void)
 {
    while(1)
    {
    }
 }
__attribute__((weak)) void IntDefaultHandler(void)
 {
    while(1)
    {
    }
 }

__attribute__((weak)) void MemManage_Handler(void)
{
    while (1)
    { 
    }
}

__attribute__((weak)) void BusFault_Handler(void)
{
     while(1)
     {
     } 
}

__attribute__((weak)) void UsageFault_Handler(void) 
{
     while(1)
     {
     } 
}


__attribute__((weak)) void DebugMon_Handler(void) 
{ 
    while(1)
    {

    } 
}


