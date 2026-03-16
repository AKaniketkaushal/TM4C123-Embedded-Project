#ifndef FREERTOS_CONFIG_H
#define FREERTOS_CONFIG_H

#include <stdint.h>

/*-----------------------------------------------------------
 * Application specific definitions.
 *----------------------------------------------------------*/

/* CPU and Tick Configuration */
#define configCPU_CLOCK_HZ            ( ( uint32_t ) 80000000 )
#define configTICK_RATE_HZ            ( ( TickType_t ) 1000 )

/* Scheduler Configuration */
#define configUSE_PREEMPTION          1
#define configUSE_TIME_SLICING        1
#define configMAX_PRIORITIES          5
#define configMINIMAL_STACK_SIZE      ( 128 )
#define configTOTAL_HEAP_SIZE         ( ( size_t ) ( 20 * 1024 ) )
#define configMAX_TASK_NAME_LEN       16
#define configUSE_16_BIT_TICKS        0
#define configIDLE_SHOULD_YIELD       1

/* Hook Functions */
#define configUSE_IDLE_HOOK           0
#define configUSE_TICK_HOOK           0
#define configCHECK_FOR_STACK_OVERFLOW 2
#define configUSE_MALLOC_FAILED_HOOK  1

/* Memory Allocation */
#define configSUPPORT_STATIC_ALLOCATION   0
#define configSUPPORT_DYNAMIC_ALLOCATION  1

/* Software Timer */
#define configUSE_TIMERS              1
#define configTIMER_TASK_PRIORITY     2
#define configTIMER_QUEUE_LENGTH      10
#define configTIMER_TASK_STACK_DEPTH  256

/* Synchronization */
#define configUSE_MUTEXES             1
#define configUSE_RECURSIVE_MUTEXES   1
#define configUSE_COUNTING_SEMAPHORES 1
#define configQUEUE_REGISTRY_SIZE     8

/* Cortex-M Specific Definitions */
#define configPRIO_BITS               3

/* Interrupt Priority Configuration */
#define configLIBRARY_LOWEST_INTERRUPT_PRIORITY     7
#define configLIBRARY_MAX_SYSCALL_INTERRUPT_PRIORITY 5

#define configKERNEL_INTERRUPT_PRIORITY \
    ( configLIBRARY_LOWEST_INTERRUPT_PRIORITY << (8 - configPRIO_BITS) )

#define configMAX_SYSCALL_INTERRUPT_PRIORITY \
    ( configLIBRARY_MAX_SYSCALL_INTERRUPT_PRIORITY << (8 - configPRIO_BITS) )

/* API Function Inclusion */
#define INCLUDE_vTaskPrioritySet      1
#define INCLUDE_uxTaskPriorityGet     1
#define INCLUDE_vTaskDelete           1
#define INCLUDE_vTaskSuspend          1
#define INCLUDE_vTaskDelay            1
#define INCLUDE_vTaskDelayUntil       1
#define INCLUDE_xTaskGetSchedulerState 1
#define INCLUDE_xTaskGetCurrentTaskHandle 1

/* Assertion */
#define configASSERT(x) if((x)==0) { taskDISABLE_INTERRUPTS(); for( ;; ); }


#endif /* FREERTOS_CONFIG_H */
