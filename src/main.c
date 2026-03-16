

#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "driver/gpio.h"
#include "driver/sysctl.h"
#include "driver/uart.h"
#include "pin_map.h"
#include "TM4C123.h"
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"

extern uint32_t SystemCoreClock;

QueueHandle_t xUARTQueue;

// FreeRTOS hooks
void vApplicationStackOverflowHook(TaskHandle_t xTask, char *pcTaskName)
{
    (void)xTask;
    (void)pcTaskName;
    
    // Infinite loop for debugging
    for(;;);
}

void vApplicationMallocFailedHook(void)
{
    // Infinite loop for debugging
    for(;;);
}

// Thread-safe UART print
void UARTPrint(const char *str)
{
    taskENTER_CRITICAL();
    while (*str)
    {
        UARTCharPut(UART0_BASE, *str++);
    }
    taskEXIT_CRITICAL();
}

// UART ISR - FreeRTOS safe
void uart_isr(void)
{
    uint32_t status;
    BaseType_t xHigherPriorityTaskWoken = pdFALSE;
    
    status = UARTIntStatus(UART0_BASE, true);
    UARTIntClear(UART0_BASE, status);
    
    while (UARTCharsAvail(UART0_BASE))
    {
        char c = UARTCharGetNonBlocking(UART0_BASE);
        
        // Send to queue (FreeRTOS ISR-safe)
        xQueueSendFromISR(xUARTQueue, &c, &xHigherPriorityTaskWoken);
    }
    
    // Context switch if needed
    portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
}

// Task to process UART received characters
void vUARTProcessTask(void *pvParameters)
{
    (void)pvParameters;
    char c;
    
    UARTPrint("UART Task Running!\r\n");
    
    while (1)
    {
        // Wait for character from queue
        if (xQueueReceive(xUARTQueue, &c, portMAX_DELAY) == pdTRUE)
        {
            // Echo character
            taskENTER_CRITICAL();
            UARTCharPut(UART0_BASE, c);
            taskEXIT_CRITICAL();
            
            UARTPrint(" - received\r\n");
        }
    }
}

// Periodic task for heartbeat
void vHeartbeatTask(void *pvParameters)
{
    (void)pvParameters;
    uint32_t count = 0;
    
    UARTPrint("Heartbeat Task Running!\r\n");
    
    while (1)
    {
        UARTPrint("Alive: ");
        
        // Simple number printing
        char buf[12];
        uint32_t num = count++;
        int i = 0;
        
        if (num == 0) {
            buf[i++] = '0';
        } else {
            char temp[12];
            int j = 0;
            while (num > 0) {
                temp[j++] = '0' + (num % 10);
                num /= 10;
            }
            while (j > 0) {
                buf[i++] = temp[--j];
            }
        }
        buf[i] = '\0';
        
        UARTPrint(buf);
        UARTPrint("\r\n");
        
        vTaskDelay(pdMS_TO_TICKS(2000));  // 2 second delay
    }
}

int main(void)
{
    // 1. Initialize system clock (80 MHz)
    SysCtlClockSet(SYSCTL_SYSDIV_2_5 | SYSCTL_USE_PLL |
                   SYSCTL_XTAL_16MHZ | SYSCTL_OSC_MAIN);
    
    SystemCoreClock = SysCtlClockGet();
    
    // 2. Initialize UART hardware
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_UART0);
    
    while (!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOA));
    while (!SysCtlPeripheralReady(SYSCTL_PERIPH_UART0));
    
    GPIOPinConfigure(GPIO_PA0_U0RX);
    GPIOPinConfigure(GPIO_PA1_U0TX);
    GPIOPinTypeUART(GPIO_PORTA_BASE, GPIO_PIN_0 | GPIO_PIN_1);
    
    UARTConfigSetExpClk(UART0_BASE, SysCtlClockGet(), 115200,
                        (UART_CONFIG_WLEN_8 | UART_CONFIG_STOP_ONE |
                         UART_CONFIG_PAR_NONE));
    
    UARTFIFOEnable(UART0_BASE);
    UARTFIFOLevelSet(UART0_BASE, UART_FIFO_TX1_8, UART_FIFO_RX1_8);
    
    UARTEnable(UART0_BASE);
    
    // Test UART before FreeRTOS
    const char *msg = "\r\n=== System Starting ===\r\n";
    while (*msg) {
        UARTCharPut(UART0_BASE, *msg++);
    }
    
    // 3. Create UART queue
    xUARTQueue = xQueueCreate(32, sizeof(char));
    
    if (xUARTQueue == NULL)
    {
        // Queue creation failed - halt
        const char *err = "Queue creation failed!\r\n";
        while (*err) {
            UARTCharPut(UART0_BASE, *err++);
        }
        while(1);
    }
    
    // 4. Setup UART interrupts
    UARTIntEnable(UART0_BASE, UART_INT_RX | UART_INT_RT);
    
    // CRITICAL: Set interrupt priority correctly for FreeRTOS
    // Priority must be >= configMAX_SYSCALL_INTERRUPT_PRIORITY (160)
    // Using priority level 5 (in ARM priority scheme) = 160 in register
    NVIC_SetPriority(UART0_IRQn, configLIBRARY_MAX_SYSCALL_INTERRUPT_PRIORITY);
    
    NVIC_SetVector(UART0_IRQn, (uint32_t)&uart_isr);
    NVIC_EnableIRQ(UART0_IRQn);
    
    // 5. Create FreeRTOS tasks
    BaseType_t result;
    
    result = xTaskCreate(vUARTProcessTask,
                        "UART",
                        256,    // Stack size in words (1KB)
                        NULL,
                        2,      // Priority
                        NULL);
    
    if (result != pdPASS)
    {
        const char *err = "UART task creation failed!\r\n";
        while (*err) {
            UARTCharPut(UART0_BASE, *err++);
        }
        while(1);
    }
    
    result = xTaskCreate(vHeartbeatTask,
                        "Heartbeat",
                        256,    // Stack size in words (1KB)
                        NULL,
                        1,      // Lower priority
                        NULL);
    
    if (result != pdPASS)
    {
        const char *err = "Heartbeat task creation failed!\r\n";
        while (*err) {
            UARTCharPut(UART0_BASE, *err++);
        }
        while(1);
    }
    
    msg = "Starting FreeRTOS scheduler...\r\n";
    while (*msg) {
        UARTCharPut(UART0_BASE, *msg++);
    }
    
    // 6. Start the FreeRTOS scheduler (never returns)
    vTaskStartScheduler();
    
    // Should never reach here - scheduler failed to start
    msg = "ERROR: Scheduler failed to start!\r\n";
    while (*msg) {
        UARTCharPut(UART0_BASE, *msg++);
    }
    
    while (1);
    
    return 0;
}
