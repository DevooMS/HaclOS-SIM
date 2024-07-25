#include "FreeRTOS.h"
#include "task.h"

// Prototipi delle funzioni dei task
void vTaskA(void );
void vTaskB(void );



int main4c(void) {
    xTaskCreate(vTaskA, "TaskA", configMINIMAL_STACK_SIZE, NULL, 1, NULL);
    xTaskCreate(vTaskB, "TaskB", configMINIMAL_STACK_SIZE, NULL, 1, NULL);
    vTaskStartScheduler();
    for (;;);
}

void vTaskA(void) {
    for (;;) {
        printf("Task A\n");
    }
}

void vTaskB(void) {
    for (;;) {
        printf("Task B\n");
    }
}