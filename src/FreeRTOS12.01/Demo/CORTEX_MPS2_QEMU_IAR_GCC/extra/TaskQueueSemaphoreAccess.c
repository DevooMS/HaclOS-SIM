/* Standard includes */
#include <stdio.h>

/* Kernel includes */
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "semphr.h"

#define TASK_PRIORITY (tskIDLE_PRIORITY + 2)
#define QUEUE_LENGTH 7 // Maximum task queue length

QueueHandle_t accessQueue; // Queue to store the order of task arrival
SemaphoreHandle_t resourceSemaphore;

// Task that requests access to the semaphore
static void task1(void *pvParameters) {
    (void)pvParameters;

    for (;;) {
        TaskHandle_t currentTask = xTaskGetCurrentTaskHandle();

        // Add the task to the queue to request semaphore access
        if (xQueueSend(accessQueue, &currentTask, portMAX_DELAY) == pdPASS) {
            TaskHandle_t taskInQueue;
            xQueueReceive(accessQueue, &taskInQueue, portMAX_DELAY);

            // Check if it's this task's turn in the queue
            if (taskInQueue == currentTask) {
                // Attempt to take the semaphore (resource)
                if (xSemaphoreTake(resourceSemaphore, portMAX_DELAY) == pdTRUE) {

                    printf("Task 1 running\r\n");
                    vTaskDelay(pdMS_TO_TICKS(1000)); // Simulate resource usage
                    printf("Task 1 releasing resource\n");

                    // Release the semaphore after utilizing the resource
                    xSemaphoreGive(resourceSemaphore);

                    // Re-insert the task into the queue to request access again
                    xQueueSend(accessQueue, &currentTask, portMAX_DELAY);
                    xQueueReceive(accessQueue, &taskInQueue, portMAX_DELAY);
                }
            }
        }

        // Introduce a delay or other operations before reattempting access
        vTaskDelay(pdMS_TO_TICKS(500));
    }
}

static void task2(void *pvParameters) {
    (void)pvParameters;

    for (;;) {
        TaskHandle_t currentTask = xTaskGetCurrentTaskHandle();

        // Add the task to the queue to request semaphore access
        if (xQueueSend(accessQueue, &currentTask, portMAX_DELAY) == pdPASS) {
            TaskHandle_t taskInQueue;
            xQueueReceive(accessQueue, &taskInQueue, portMAX_DELAY);

            // Check if it's this task's turn in the queue
            if (taskInQueue == currentTask) {
                // Attempt to take the semaphore (resource)
                if (xSemaphoreTake(resourceSemaphore, portMAX_DELAY) == pdTRUE) {

                    printf("Task 2 running\r\n");
                    vTaskDelay(pdMS_TO_TICKS(1000)); // Simulate resource usage
                    printf("Task 2 releasing resource\n");

                    // Release the semaphore after utilizing the resource
                    xSemaphoreGive(resourceSemaphore);

                    // Re-insert the task into the queue to request access again
                    xQueueSend(accessQueue, &currentTask, portMAX_DELAY);
                    xQueueReceive(accessQueue, &taskInQueue, portMAX_DELAY);
                }
            }
        }

        // Introduce a delay or other operations before reattempting access
        vTaskDelay(pdMS_TO_TICKS(500));
    }
}

static void task3(void *pvParameters) {
    (void)pvParameters;

    for (;;) {
        TaskHandle_t currentTask = xTaskGetCurrentTaskHandle();

        // Add the task to the queue to request semaphore access
        if (xQueueSend(accessQueue, &currentTask, portMAX_DELAY) == pdPASS) {
            TaskHandle_t taskInQueue;
            xQueueReceive(accessQueue, &taskInQueue, portMAX_DELAY);

            // Check if it's this task's turn in the queue
            if (taskInQueue == currentTask) {
                // Attempt to take the semaphore (resource)
                if (xSemaphoreTake(resourceSemaphore, portMAX_DELAY) == pdTRUE) {

                    printf("Task 3 running\r\n");
                    vTaskDelay(pdMS_TO_TICKS(1000)); // Simulate resource usage
                    printf("Task 3 releasing resource\n");

                    // Release the semaphore after utilizing the resource
                    xSemaphoreGive(resourceSemaphore);

                    // Re-insert the task into the queue to request access again
                    xQueueSend(accessQueue, &currentTask, portMAX_DELAY);
                    xQueueReceive(accessQueue, &taskInQueue, portMAX_DELAY);
                }
            }
        }

        // Introduce a delay or other operations before reattempting access
        vTaskDelay(pdMS_TO_TICKS(500));
    }
}



void TaskQueueSemaphoreAccess(void) {

    // Create semaphore to manage mutually exclusive access to the resource
    resourceSemaphore = xSemaphoreCreateMutex();
    xSemaphoreGive(resourceSemaphore);

    // Create a queue to manage the order of task arrival
    accessQueue = xQueueCreate(QUEUE_LENGTH, sizeof(TaskHandle_t));

    // Create tasks
    xTaskCreate(task1, "Task 1", configMINIMAL_STACK_SIZE, NULL, TASK_PRIORITY, NULL);
    xTaskCreate(task2, "Task 2", configMINIMAL_STACK_SIZE, NULL, TASK_PRIORITY, NULL);
    xTaskCreate(task3, "Task 3", configMINIMAL_STACK_SIZE, NULL, TASK_PRIORITY, NULL);

    // Start FreeRTOS scheduler
    vTaskStartScheduler();

    // Code should not reach here under normal circumstances
    while (1) {
        // Handle errors or perform additional operations
    }
}