#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"
#include "queue.h"

#define NUM_USERS 7

SemaphoreHandle_t xSemaphore;   // Semaphore to control access to shared resource
QueueHandle_t xQueue;           // Queue for storing execution order of tasks
int usersCompleted = 0;         // Counter for completed users

void useResource(int userId) {
    printf("User %d is using the resource\n", userId);
    // Code to use the resource
}

void example_task2(void *pvParameters) {
    int userId = (int)pvParameters;

    if (xSemaphoreTake(xSemaphore, portMAX_DELAY)) { // Attempt to take semaphore with indefinite timeout
        useResource(userId); // Use the shared resource
        xSemaphoreGive(xSemaphore); // Release the semaphore

        taskENTER_CRITICAL(); // Enter critical section

        usersCompleted++; // Increment completed users counter
        xQueueSendToBack(xQueue, &userId, portMAX_DELAY); // Send user ID to the queue
        if (usersCompleted == NUM_USERS) { // If all users have completed
            int userOrder;
            printf("Execution order: ");
            while (xQueueReceive(xQueue, &userOrder, 0)) { // Receive user IDs from the queue
                printf("%d ", userOrder); // Print user ID
            } 
            printf("\n");
            printf("END\n");
        }
        
        taskEXIT_CRITICAL(); // Exit critical section
    }
    
    vTaskDelete(NULL);
}

void main_task2() {
    xSemaphore = xSemaphoreCreateMutex(); // Create a semaphore
    xQueue = xQueueCreate(NUM_USERS, sizeof(int)); // Create a queue to store execution order
    xSemaphoreGive(xSemaphore); // Initialize semaphore as available

    for (int i = 0; i < NUM_USERS; i++) {
        int priority = (i % 2 == 0) ? 2 : 1; // Assign higher priority to even IDs
        xTaskCreate(example_task2, "UserTask", configMINIMAL_STACK_SIZE, (void *)i, priority, NULL); // Create user tasks
    }
    
    
    vTaskStartScheduler(); // Start FreeRTOS scheduler
}
