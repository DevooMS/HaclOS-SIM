/* Standard includes. */
#include <stdio.h>
#include <string.h>
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "semphr.h"

// Define task priority, queue length, and stack size
#define TASK_PRIORITY (tskIDLE_PRIORITY + 2)
#define QUEUE_LENGTH 7 // Maximum task queue length
#define ACCESS_TASK_SATCK_SIZE configMINIMAL_STACK_SIZE * 2

// Queue to store the order of task arrival
QueueHandle_t accessQueue;
// Semaphore for resource access control
SemaphoreHandle_t resourceSemaphore;

// Simulate using a resource with a userID
void useResource(int userID){
    printf("Task %d running, using the resource\n",userID);
}

static void accessResourceTask(void *pvParameters) { // Task handling resource access
    (void)pvParameters;
    TaskHandle_t currentTask = xTaskGetCurrentTaskHandle(); // Obtain the current task handle

    if (xQueueSend(accessQueue, &currentTask, portMAX_DELAY) == pdPASS) { // Send current task handle to indicate arrival in the accessQueue
        TaskHandle_t taskInQueue;
        if (xQueueReceive(accessQueue, &taskInQueue, portMAX_DELAY) == pdPASS) { // Receive a task handle from the accessQueue
            if (currentTask == taskInQueue) { // If received task handle matches the current task handle
                if (xSemaphoreTake(resourceSemaphore, portMAX_DELAY) == pdTRUE) { // Attempt to acquire the semaphore for resource access
                    vTaskDelay(pdMS_TO_TICKS(100));
                    taskENTER_CRITICAL();
                    TaskStatus_t taskStatus;
                    vTaskGetInfo(currentTask, &taskStatus, pdTRUE, eInvalid);
                    int taskId = taskStatus.xTaskNumber; // Get the current task ID
                    useResource(taskId); // Simulate using the resource by printing the task ID
                    xSemaphoreGive(resourceSemaphore); // Release the semaphore and unregister the queue
                    vQueueUnregisterQueue(accessQueue);  
                    taskEXIT_CRITICAL();
                    vTaskDelete(NULL); // Delete the task after resource usage
                }
            }
        }
    }
    vTaskDelay(pdMS_TO_TICKS(1000)); 
}


void main_task1(void) {
    // Initialize resources and manage task creation
    resourceSemaphore = xSemaphoreCreateMutex();
    xSemaphoreGive(resourceSemaphore);
    accessQueue = xQueueCreate(QUEUE_LENGTH, sizeof(TaskHandle_t));

    for (int i = 0; i < 7; i++) { // Create seven tasks for resource access control
        xTaskCreate(accessResourceTask, "Access Task", ACCESS_TASK_SATCK_SIZE, NULL, TASK_PRIORITY, NULL);  
    }
    // Start the FreeRTOS scheduler
    vTaskStartScheduler();

    while (1) {
        // Error handling or additional operations
    }
}