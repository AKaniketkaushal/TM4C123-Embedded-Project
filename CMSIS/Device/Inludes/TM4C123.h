#ifndef TM4C123_H
#define TM4C123_H

#ifdef __cplusplus
extern "C" {
#endif

/* =========================================================================================================================== */
/* ================                                Interrupt Number Definition                                ================ */
/* =========================================================================================================================== */

typedef enum IRQn
{
    /* ===========================  ARM Cortex-M4 Specific Interrupt Numbers  ============================ */
    NonMaskableInt_IRQn           = -14,    /* -14 Non Maskable Interrupt                           */
    HardFault_IRQn                = -13,    /* -13 Cortex-M4 Hard Fault Interrupt                   */
    MemoryManagement_IRQn         = -12,    /* -12 Cortex-M4 Memory Management Interrupt            */
    BusFault_IRQn                 = -11,    /* -11 Cortex-M4 Bus Fault Interrupt                    */
    UsageFault_IRQn               = -10,    /* -10 Cortex-M4 Usage Fault Interrupt                  */
    SVCall_IRQn                   =  -5,    /*  -5 Cortex-M4 SV Call Interrupt                      */
    DebugMonitor_IRQn             =  -4,    /*  -4 Cortex-M4 Debug Monitor Interrupt                */
    PendSV_IRQn                   =  -2,    /*  -2 Cortex-M4 Pend SV Interrupt                      */
    SysTick_IRQn                  =  -1,    /*  -1 Cortex-M4 System Tick Interrupt                  */

    /* ===================  TM4C123GH6PM Specific Interrupt Numbers (143 total)  ======================= */
    GPIOA_IRQn                    =   0,    /*  0  GPIO Port A                                      */
    GPIOB_IRQn                    =   1,    /*  1  GPIO Port B                                      */
    GPIOC_IRQn                    =   2,    /*  2  GPIO Port C                                      */
    GPIOD_IRQn                    =   3,    /*  3  GPIO Port D                                      */
    GPIOE_IRQn                    =   4,    /*  4  GPIO Port E                                      */
    UART0_IRQn                    =   5,    /*  5  UART0                                            */
    UART1_IRQn                    =   6,    /*  6  UART1                                            */
    SSI0_IRQn                     =   7,    /*  7  SSI0                                             */
    I2C0_IRQn                     =   8,    /*  8  I2C0                                             */
    PWM0_FAULT_IRQn               =   9,    /*  9  PWM0 Fault                                       */
    PWM0_0_IRQn                   =  10,    /* 10  PWM0 Generator 0                                 */
    PWM0_1_IRQn                   =  11,    /* 11  PWM0 Generator 1                                 */
    PWM0_2_IRQn                   =  12,    /* 12  PWM0 Generator 2                                 */
    QEI0_IRQn                     =  13,    /* 13  QEI0                                             */
    ADC0SS0_IRQn                  =  14,    /* 14  ADC0 Sequence 0                                  */
    ADC0SS1_IRQn                  =  15,    /* 15  ADC0 Sequence 1                                  */
    ADC0SS2_IRQn                  =  16,    /* 16  ADC0 Sequence 2                                  */
    ADC0SS3_IRQn                  =  17,    /* 17  ADC0 Sequence 3                                  */
    WATCHDOG_IRQn                 =  18,    /* 18  Watchdog Timers 0 and 1                          */
    TIMER0A_IRQn                  =  19,    /* 19  16/32-Bit Timer 0A                               */
    TIMER0B_IRQn                  =  20,    /* 20  16/32-Bit Timer 0B                               */
    TIMER1A_IRQn                  =  21,    /* 21  16/32-Bit Timer 1A                               */
    TIMER1B_IRQn                  =  22,    /* 22  16/32-Bit Timer 1B                               */
    TIMER2A_IRQn                  =  23,    /* 23  16/32-Bit Timer 2A                               */
    TIMER2B_IRQn                  =  24,    /* 24  16/32-Bit Timer 2B                               */
    COMP0_IRQn                    =  25,    /* 25  Analog Comparator 0                              */
    COMP1_IRQn                    =  26,    /* 26  Analog Comparator 1                              */
    COMP2_IRQn                    =  27,    /* 27  Analog Comparator 2                              */
    SYSCTL_IRQn                   =  28,    /* 28  System Control                                   */
    FLASH_IRQn                    =  29,    /* 29  Flash Memory Control and EEPROM Control          */
    GPIOF_IRQn                    =  30,    /* 30  GPIO Port F                                      */
    GPIOG_IRQn                    =  31,    /* 31  GPIO Port G                                      */
    GPIOH_IRQn                    =  32,    /* 32  GPIO Port H                                      */
    UART2_IRQn                    =  33,    /* 33  UART2                                            */
    SSI1_IRQn                     =  34,    /* 34  SSI1                                             */
    TIMER3A_IRQn                  =  35,    /* 35  16/32-Bit Timer 3A                               */
    TIMER3B_IRQn                  =  36,    /* 36  16/32-Bit Timer 3B                               */
    I2C1_IRQn                     =  37,    /* 37  I2C1                                             */
    QEI1_IRQn                     =  38,    /* 38  QEI1                                             */
    CAN0_IRQn                     =  39,    /* 39  CAN0                                             */
    CAN1_IRQn                     =  40,    /* 40  CAN1                                             */
    HIBERNATE_IRQn                =  43,    /* 43  Hibernation Module                               */
    USB0_IRQn                     =  44,    /* 44  USB                                              */
    PWM0_3_IRQn                   =  45,    /* 45  PWM Generator 3                                  */
    UDMA_IRQn                     =  46,    /* 46  uDMA Software                                    */
    UDMAERR_IRQn                  =  47,    /* 47  uDMA Error                                       */
    ADC1SS0_IRQn                  =  48,    /* 48  ADC1 Sequence 0                                  */
    ADC1SS1_IRQn                  =  49,    /* 49  ADC1 Sequence 1                                  */
    ADC1SS2_IRQn                  =  50,    /* 50  ADC1 Sequence 2                                  */
    ADC1SS3_IRQn                  =  51,    /* 51  ADC1 Sequence 3                                  */
    GPIOJ_IRQn                    =  54,    /* 54  GPIO Port J                                      */
    GPIOK_IRQn                    =  55,    /* 55  GPIO Port K                                      */
    GPIOL_IRQn                    =  56,    /* 56  GPIO Port L                                      */
    SSI2_IRQn                     =  57,    /* 57  SSI2                                             */
    SSI3_IRQn                     =  58,    /* 58  SSI3                                             */
    UART3_IRQn                    =  59,    /* 59  UART3                                            */
    UART4_IRQn                    =  60,    /* 60  UART4                                            */
    UART5_IRQn                    =  61,    /* 61  UART5                                            */
    UART6_IRQn                    =  62,    /* 62  UART6                                            */
    UART7_IRQn                    =  63,    /* 63  UART7                                            */
    I2C2_IRQn                     =  68,    /* 68  I2C2                                             */
    I2C3_IRQn                     =  69,    /* 69  I2C3                                             */
    TIMER4A_IRQn                  =  70,    /* 70  16/32-Bit Timer 4A                               */
    TIMER4B_IRQn                  =  71,    /* 71  16/32-Bit Timer 4B                               */
    TIMER5A_IRQn                  =  92,    /* 92  16/32-Bit Timer 5A                               */
    TIMER5B_IRQn                  =  93,    /* 93  16/32-Bit Timer 5B                               */
    WTIMER0A_IRQn                 =  94,    /* 94  32/64-Bit Timer 0A                               */
    WTIMER0B_IRQn                 =  95,    /* 95  32/64-Bit Timer 0B                               */
    WTIMER1A_IRQn                 =  96,    /* 96  32/64-Bit Timer 1A                               */
    WTIMER1B_IRQn                 =  97,    /* 97  32/64-Bit Timer 1B                               */
    WTIMER2A_IRQn                 =  98,    /* 98  32/64-Bit Timer 2A                               */
    WTIMER2B_IRQn                 =  99,    /* 99  32/64-Bit Timer 2B                               */
    WTIMER3A_IRQn                 = 100,    /* 100 32/64-Bit Timer 3A                               */
    WTIMER3B_IRQn                 = 101,    /* 101 32/64-Bit Timer 3B                               */
    WTIMER4A_IRQn                 = 102,    /* 102 32/64-Bit Timer 4A                               */
    WTIMER4B_IRQn                 = 103,    /* 103 32/64-Bit Timer 4B                               */
    WTIMER5A_IRQn                 = 104,    /* 104 32/64-Bit Timer 5A                               */
    WTIMER5B_IRQn                 = 105,    /* 105 32/64-Bit Timer 5B                               */
    SYSEXC_IRQn                   = 106,    /* 106 System Exception (imprecise)                     */
    I2C4_IRQn                     = 109,    /* 109 I2C4                                             */
    I2C5_IRQn                     = 110,    /* 110 I2C5                                             */
    GPIOM_IRQn                    = 111,    /* 111 GPIO Port M                                      */
    GPION_IRQn                    = 112,    /* 112 GPIO Port N                                      */
    TAMPER_IRQn                   = 114,    /* 114 Tamper                                           */
    GPIOP0_IRQn                   = 115,    /* 115 GPIO Port P (Summary or P0)                      */
    GPIOP1_IRQn                   = 116,    /* 116 GPIO Port P1                                     */
    GPIOP2_IRQn                   = 117,    /* 117 GPIO Port P2                                     */
    GPIOP3_IRQn                   = 118,    /* 118 GPIO Port P3                                     */
    GPIOP4_IRQn                   = 119,    /* 119 GPIO Port P4                                     */
    GPIOP5_IRQn                   = 120,    /* 120 GPIO Port P5                                     */
    GPIOP6_IRQn                   = 121,    /* 121 GPIO Port P6                                     */
    GPIOP7_IRQn                   = 122,    /* 122 GPIO Port P7                                     */
    GPIOQ0_IRQn                   = 123,    /* 123 GPIO Port Q (Summary or Q0)                      */
    GPIOQ1_IRQn                   = 124,    /* 124 GPIO Port Q1                                     */
    GPIOQ2_IRQn                   = 125,    /* 125 GPIO Port Q2                                     */
    GPIOQ3_IRQn                   = 126,    /* 126 GPIO Port Q3                                     */
    GPIOQ4_IRQn                   = 127,    /* 127 GPIO Port Q4                                     */
    GPIOQ5_IRQn                   = 128,    /* 128 GPIO Port Q5                                     */
    GPIOQ6_IRQn                   = 129,    /* 129 GPIO Port Q6                                     */
    GPIOQ7_IRQn                   = 130,    /* 130 GPIO Port Q7                                     */
    GPIOR_IRQn                    = 133,    /* 133 GPIO Port R                                      */
    GPIOS_IRQn                    = 134,    /* 134 GPIO Port S                                      */
    SHA_MD5_IRQn                  = 135,    /* 135 SHA/MD5                                          */
    AES_IRQn                      = 136,    /* 136 AES                                              */
    DES_IRQn                      = 137,    /* 137 DES                                              */
    PWM1_0_IRQn                   = 138,    /* 138 PWM1 Generator 0                                 */
    PWM1_1_IRQn                   = 139,    /* 139 PWM1 Generator 1                                 */
    PWM1_2_IRQn                   = 140,    /* 140 PWM1 Generator 2                                 */
    PWM1_3_IRQn                   = 141,    /* 141 PWM1 Generator 3                                 */
    PWM1_FAULT_IRQn               = 142     /* 142 PWM1 Fault                                       */
} IRQn_Type;

/* =========================================================================================================================== */
/* ================                           Processor and Core Peripheral Configuration                     ================ */
/* =========================================================================================================================== */

#define __CM4_REV                 0x0001U   /* Core revision r0p1                                   */
#define __MPU_PRESENT             1U        /* MPU present                                          */
#define __VTOR_PRESENT            1U        /* VTOR present                                         */
#define __NVIC_PRIO_BITS          3U        /* Number of Bits used for Priority Levels (8 levels)   */
#define __Vendor_SysTickConfig    0U        /* Set to 1 if different SysTick Config is used         */
#define __FPU_PRESENT             1U        /* FPU present                                          */

#include "core_cm4.h"                       /* ARM Cortex-M4 processor and core peripherals         */
#include "system_TM4C123.h"                 /* TM4C123GH6PM System                                  */

#ifdef __cplusplus
}
#endif

#endif  /* TM4C123_H */
