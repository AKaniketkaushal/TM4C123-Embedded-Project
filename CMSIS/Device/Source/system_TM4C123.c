#include <stdint.h>
#include "system_TM4C123.h"

/* System Clock Frequency (Core Clock)
 * Default: 16MHz (Internal Precision Oscillator)
 * Update this after calling SysCtlClockSet() in your application
 */
uint32_t SystemCoreClock = 16000000U;  /* 16 MHz default */

/* * @brief  System Initialization
 * 
 * This function is called from Reset_Handler before main().
 * Use it for:
 * - Clock initialization (optional, can be done in main)
 * - Silicon errata workarounds
 * - FPU enable (if not done in startup)
 * - MPU configuration (if needed)
 * 
 * For TM4C123, most initialization is done in main() using TivaWare,
 * so this can remain empty.
 */
void SystemInit(void)
{
    /* FPU settings - Enable FPU if not already done in startup */
    #if (__FPU_PRESENT == 1) && (__FPU_USED == 1)
        SCB->CPACR |= ((3UL << 10*2) |  /* Set CP10 Full Access */
                       (3UL << 11*2));   /* Set CP11 Full Access */
    #endif

    /* Add any early hardware initialization here */
    /* Example: Disable interrupts during init */
    /* __disable_irq(); */
    
    /* Leave clock configuration to main() using TivaWare */
}

/* * @brief  Update SystemCoreClock variable
 * 
 * Updates SystemCoreClock with current core clock frequency.
 * 
 * For TM4C123:
 * - Call this after changing PLL/clock settings
 * - Or use TivaWare's SysCtlClockGet() instead
 * 
 * Example usage in main():
 *   SysCtlClockSet(...);
 *   SystemCoreClock = SysCtlClockGet();
 *   SystemCoreClockUpdate();
 */
void SystemCoreClockUpdate(void)
{
    /* TM4C123 Clock Calculation
     * Read RCC/RCC2 registers to determine actual clock
     * 
     * For simplicity, if using TivaWare, just do:
     *   SystemCoreClock = SysCtlClockGet();
     * in your main() after clock configuration.
     */
    
    /* Simple default: assume 16MHz if not configured */
    SystemCoreClock = 16000000U;
    
    /* TODO: Add proper clock calculation from RCC/RCC2 registers
     * if you want to implement full CMSIS compliance without TivaWare
     */
}
