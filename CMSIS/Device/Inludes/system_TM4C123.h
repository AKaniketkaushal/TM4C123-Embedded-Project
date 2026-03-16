#ifndef SYSTEM_TM4C123_H
#define SYSTEM_TM4C123_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

/* System Clock Frequency (Core Clock) */
extern uint32_t SystemCoreClock;

/* * @brief Setup the microcontroller system.
 * Initialize the System and update the SystemCoreClock variable.
 * This function is called from startup before main().
 */
void SystemInit(void);

/* * @brief Update SystemCoreClock variable.
 * Updates the SystemCoreClock with current core Clock 
 * retrieved from CPU registers.
 */
void SystemCoreClockUpdate(void);

#ifdef __cplusplus
}
#endif

#endif /* SYSTEM_TM4C123_H */
