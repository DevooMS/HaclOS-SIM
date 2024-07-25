#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"
#include "queue.h"
#include "event_groups.h"
#define NUM_USERS 7
#define HIGH_PRIORITY_USERS 5

SemaphoreHandle_t xMutex;           // Mutex for the resource
EventGroupHandle_t xTask2Events;    // Event group for task 2
QueueHandle_t xQueue;               // Queue for task 2
TaskHandle_t tasks[NUM_USERS];      // Task 3
int highPriorityUsersDone = 0;      // Number of high priority users that have finished
int usersCompleted = 0;             // Number of users that have finished


void useResource(int userId) {      // Function to use the resource
    
    printf("User %d is using the resource\n", userId); //Code to use the resource
    
}

void taskExample2(void *pvParameters) { // Task 2
    int userId = (int)pvParameters;     // ID user

    if (xSemaphoreTake(xMutex, portMAX_DELAY)) { // If the mutex is available
        useResource(userId);    // Use the resource
        xSemaphoreGive(xMutex); // Release the mutex

        taskENTER_CRITICAL();   // Enter critical section

        usersCompleted++;
        xQueueSendToBack(xQueue, &userId, portMAX_DELAY);           // Add the user ID to the queue
        if (usersCompleted == NUM_USERS) {                          // If all users have finished
            
            int userOrder;                                          // Variable to store the user order
            xEventGroupSetBits(xTask2Events, (1 << NUM_USERS) - 1); // Notify task 3 that all users have finished
            printf("Execution order: ");                       // Print the order of execution
            while (xQueueReceive(xQueue, &userOrder, 0)) {          // If there are still items in the queue
                printf("%d ", userOrder);                           // Print the user ID     
            }
            printf("\n");
            printf("\n");
           
        }
        
        taskEXIT_CRITICAL();                                        // Exit critical section
    }
    
    vTaskDelete(NULL);                                                // Task finished
}

void taskExample3(void *pvParameters) {                                // Task 3
    int userId = (int)pvParameters;                                    // ID user
    xEventGroupWaitBits(xTask2Events, (1 << NUM_USERS) - 1, pdFALSE, pdTRUE, portMAX_DELAY); // Wait for all users to finish
    if (userId <= HIGH_PRIORITY_USERS) { // High Priority User
      
        printf("High Priority User %d is using the resource\n", userId); //Code to use the resource

        highPriorityUsersDone++;
        if (highPriorityUsersDone == HIGH_PRIORITY_USERS) {                  // If all high priority users have finished
            // Notify low priority users
            for (int i = HIGH_PRIORITY_USERS; i < NUM_USERS; i++) {         // Notify low priority users
                xTaskNotifyGive(tasks[i]);                                  // Notify the task
            }
        }
        
    } else { // Low priority users
        // Assure that all high priority users have finished
    
        printf("Low Priority User %d is using the resource\n", userId);
    }

    vTaskDelete(NULL);
}
void main_task23() {
    xMutex = xSemaphoreCreateMutex(); // Create the mutex
    xQueue = xQueueCreate(NUM_USERS, sizeof(int));
    xTask2Events = xEventGroupCreate(); 
    
    for (int i = 0; i < NUM_USERS; i++) {
        int priority = (i % 2 == 0) ? 2 : 1; // Priority of the task
        
        xTaskCreate(                        // Create the task
            taskExample2,                   // Call function
            "taskExample2",                 // Name of the task
            configMINIMAL_STACK_SIZE,       // Size of the stack
            (void *)i,                      // Parameter passed to the function
            priority,                       // Priority of the task
            NULL                            // Handle of the task
        );
    }


    for (int i = 1; i <= NUM_USERS; i++) {
        xTaskCreate(                             // Create the task
            taskExample3,                        // Call function
            "taskExample3",                      // Name of the task
            1000,                                // Size of the stack
            (void *)i,                           // Parameter passed to the function
            (i <= HIGH_PRIORITY_USERS ? 2 : 1),  // Priority of the task
            &tasks[i - 1]                        // Handle of the task
        );
    }
   
    

    vTaskStartScheduler();                       // Start the scheduler
}
