#include "FreeRTOS.h"
#include "task.h"
#include "FreeRTOSConfig.h"

/* Define the periods for Task1 and Task2 in ticks */
#define TASK1_PERIOD    3
#define TASK2_PERIOD    5

/* Function prototypes */
static void vTask1(void *pvParameters);
static void vTask2(void *pvParameters);

/* Simulated LED state */
static BaseType_t xLEDState = pdFALSE;

int EDF_sim(void)
{
    /* Initialize any hardware or peripherals here if needed */

    /* Create Task1 and Task2 with different periods */
    xTaskPeriodicCreate(vTask1, "Task1", configMINIMAL_STACK_SIZE, NULL, TASK1_PERIOD, NULL, TASK1_PERIOD);
    xTaskPeriodicCreate(vTask2, "Task2", configMINIMAL_STACK_SIZE, NULL, TASK2_PERIOD, NULL, TASK2_PERIOD);

    /* Start the FreeRTOS scheduler */
    vTaskStartScheduler();

    /* It should never reach here */
    for (;;)
    {
    }
}

/* Task1 function */
static void vTask1(void *pvParameters)
{
    (void)pvParameters;
    TickType_t xLastWakeTime = xTaskGetTickCount();  // Get the current tick count

    for (;;)
    {
        /* Print a message indicating Task1 is executing */
        printf("Task1 executing...\n");

        /* Simulate resource usage (e.g., toggle an LED) */
        xLEDState = !xLEDState;
        printf("Task1 using resource (LED state: %s)...\n", xLEDState ? "ON" : "OFF");
        
        /* Print the current tick count for Task1 */
        printf("Task1 tick count: %u\n", (unsigned int)xLastWakeTime);

  
        /* Task delay until the next wake time */
        vTaskDelayUntil(&xLastWakeTime , TASK1_PERIOD);
        
       
    }
}

/* Task2 function */
static void vTask2(void *pvParameters)
{
    (void)pvParameters;
    TickType_t xLastWakeTime = xTaskGetTickCount();  // Get the current tick count

    for (;;)
    {
        /* Print a message indicating Task2 is executing */
        printf("Task2 executing...\n");

        /* Simulate resource usage (e.g., toggle an LED) */
        xLEDState = !xLEDState;
        printf("Task2 using resource (LED state: %s)... \n", xLEDState ? "ON" : "OFF");
        
        /* Print the current tick count for Task2 */
        printf("Task2 tick count: %u\n", (unsigned int)xLastWakeTime);
        /* Task delay until the next period */
        vTaskDelayUntil(&xLastWakeTime, TASK2_PERIOD);
        
    }
}


