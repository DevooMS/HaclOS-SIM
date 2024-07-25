#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"
#include "utility.h"

int task1_T = 4;    // Period of task 1
int task2_T = 5;    // Period of task 2
int task1_C = 2;    // Time of execution of task 1
int task2_C = 2;    // Time of execution of task 2


void TSK_A (void *pvParameters); // Prototype for Task A
void TSK_B (void *pvParameters); // Prototype for Task B



int main_part4(void) {

    if(isSchedulable(task1_C, task1_T, task2_C, task2_T) != pdTRUE) {    // Check for schedulability
             return -1;
    }
    else{
    xTaskPeriodicCreate( TSK_A, ( const char * ) "A",configMINIMAL_STACK_SIZE, NULL, 1, NULL, task1_T); // Create Task A
    xTaskPeriodicCreate( TSK_B, ( const char * ) "B",configMINIMAL_STACK_SIZE, NULL, 1, NULL, task2_T );// Create Task B

    // Inizialize the scheduler
    vTaskStartScheduler();

    // When the scheduler is initialized, the execution flow will never return here
    while (1);

    return 0;
    }
}

void TSK_A(void *pvParameters) {
    TickType_t xLastWakeTime = xTaskGetTickCount(); // Initialize the task's temporal base

    while (1) {
        // SImulate the execution time of the task
         xTaskDelayUntil(&xLastWakeTime, task1_T);
    }
}


void TSK_B(void *pvParameters) {
    TickType_t xLastWakeTime = xTaskGetTickCount(); // Initialize the task's temporal base

    while (1) {
        // Simulate the execution time of the task
        xTaskDelayUntil(&xLastWakeTime, task2_T);   
    }
}