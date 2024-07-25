# How to execute project demos
For execute our custom demos follow this commands:

1. Open *FreeRTOSConfig.h* file in *Code/FreeRTOS12.01/Demo/CORTEX_MPS2_QEMU_IAR_GCC*

2. Modify the parameter *configUSE_EDF_SCHEDULER* setting it to 0 and *configUSE_TEST* choosing one of these values:
    - 1 for *example_task1.c*
    - 2 for *example_task2.c*
    - 3 for *example_task23.c*
    - 4 for *example_task4c.c*

3. For testing the EDF implementation, modify the parameter *configUSE_EDF_SCHEDULER* setting it to 1

4. Open the MakeFile in *Code/FreeRTOS12.01/Demo/CORTEX_MPS2_QEMU_IAR_GCC/build/gcc*
    1. Look for the *DEMOS APPLICATION* section, where you will find several lines that start with #. These are the instructions to compile and run the examples of the project.

    2. Choose the example you want to run and uncomment the corresponding line, that is, remove the # symbol at the beginning of the line. For example, if you want to run the *example_task1.c* example, uncomment the line that says *SOURCE_FILES += (DEMO_PROJECT)/example_task1.c*

    3. Comment out all the other lines of the examples, that is, add the # symbol at the beginning of each line that you do not want to run. This is to avoid conflicts or errors in the compilation.

    4. If you want to run the example that implements the edf scheduler, you need to uncomment two lines instead of one: the line that says edf: *SOURCE_FILES += (DEMO_PROJECT)/testing_part4.c* and the line that says *SOURCE_FILES += (DEMO_PROJECT)/utility.c* This is because the edf example requires an additional object file to work.

5. Now you can follow the spefic steps for compiling and executing the project on your choice system.


# 2 | Enhancing Learning Through Practical Scenarios: Applying Simulator and OS Concepts

For the part related to developing practical examples/exercises to demonstrate the functionality of the
simulator/operating system in alignment with the topics studied in class, we have chosen to create scenarios
based on imaginary use cases. We made this decision to enable us to make the theoretical concepts learned
during the course more concrete and tangible. This approach will provide us with the opportunity to
practically apply the knowledge we have acquired.

Scenarios based on imaginary use cases represent real-life situations where we, as students, can use the
simulator or operating system to solve specific problems or perform detailed actions. These exercises will
help us solidify our understanding of the topics covered in class through practical application, allowing us
to develop operational skills and practical abilities in managing the simulator or operating system.
This approach allows us to directly experience how the features of the simulator or operating system
translate into real-world solutions for real-world situations. This will provide us with a more comprehensive
and practical understanding of the concepts, preparing us to successfully utilize these skills in real-life
contexts or future projects.

## 2.1 | Resource Access Control in a Manufacturing Plant:

__Scenario Overview__ 

In a manufacturing plant, multiple automated processes need controlled access
to a critical resource, such as a robotic arm used for assembly. The processes must efficiently utilize
the robotic arm while avoiding collisions and resource contention.

__System Components__

- Tasks: Represent automated processes (e.g., assembly, quality checks).
- Resource: Represents the robotic arm utilized for assembly tasks.
- FreeRTOS: Embedded real-time operating system facilitating task management.

## 2.1.1 | Manage the access of various assembly task to the robotic arm through taskExample1:

Let’s understand together all the implementation steps and the use case flow of this example.

- Implementation Steps:
    
    - Initialization: The test function initializes the system by creating a mutex semaphore (resource-
    Semaphore) and an order queue (accessQueue). Seven assembly tasks (represented by accessRe-
    sourceTask) are created to access the robotic arm.

    - Resource Access Control: Each task, upon execution, attempts to gain access to the robotic arm by
    entering a queue (accessQueue) to ensure orderly resource access. Once a task reaches the front of
    the queue and acquires the semaphore (resourceSemaphore), it simulates utilizing the robotic arm
    (delayed by 100ms) and logs its ID using the resource through the useResource function. After using
    the resource, the task releases the semaphore, removes itself from the queue, and deletes its instance.

- Use Case Flow:

    - Task Initialization: The manufacturing plant’s system initializes, creating tasks representing various
    assembly processes. Tasks are managed by FreeRTOS.

    - Resource Access Management: Tasks execute concurrently and attempt to access the robotic arm.
    Each task joins the queue to access the resource. Tasks access the robotic arm in the order of their
    arrival, as managed by the queue. Upon gaining access, tasks simulate using the robotic arm and
    log their operation.

    - Task Completion and System Efficiency: Tasks release the resource and are removed from the queue
    after utilizing the robotic arm. As tasks complete their operations, they are deleted, ensuring an
    efficient and controlled utilization of the critical resource.



## 2.2 | Data Management in Environmental Monitoring: FreeRTOS UseCase

__Scenario__: Database Access Management in an Environmental Monitoring System

__Context__: Imagine an environmental monitoring system with multiple sensors scattered throughout a
large facility, such as an industrial plant. Each sensor collects data on various environmental parameters
like temperature, humidity, pollutant levels, etc. These data are periodically sent to a central processing
unit to be recorded in a database.

__Use Case for taskExample2__:

1. Multiple Sensors (Users): Each sensor is represented as a "user" in the FreeRTOS system. There
are "NUM USER" sensors, each with a unique ID.
2. Data Collection and Forwarding: Each sensor (task) attempts to send its data to the central database.
However, database access must be synchronized to avoid conflicts and data corruption.
3. Mutex Usage (xMutex): taskExample2 uses a mutex to ensure that only one sensor at a time
can access the database. When a sensor (task) wants to send its data, it first acquires the mutex
(xSemaphoreTake), ensuring exclusive access to the database.
4. Data Logging: Once access is obtained, the sensor sends its data to the database (useResource),
and then releases the mutex (xSemaphoreGive), allowing other sensors to access the database.
5. Synchronization and Reporting: Each time a sensor completes data transmission, it increments
the usersCompleted counter and adds itself to the queue (xQueueSendToBack). When all sensors
have sent their data, taskExample2 triggers an event group (xEventGroupSetBits) to signal the
completion of the data collection cycle. Subsequently, it prints the order in which sensors completed
data transmission, providing a useful log for debugging or future analysis.
6. Task Termination: After completing its operations, the task self-deletes (vTaskDelete).

__Benefits of this Approach__ 

- Efficient Synchronization: Prevents simultaneous access to the database, reducing the risk of conflicts
or data corruption.
- Access Order: Provides controlled access order for sensors to the database, valuable in environments
where timing and data collection order are critical. 
- Scalability and Flexibility: Easily adaptable to a variable number of sensors or changes in task
priorities. 
- Traceability: Records the task completion order, aiding in debugging and analysis of collected data.



# 3 | FreeRTOS customization 

## 3.1 | implementation of Earliest Deadline First (EDF) scheduler

### 3.1.1 | EDF dynamic scheduling algorithm

The EDF algorithm for process scheduling is a dynamic priority scheduling algorithm that is used inreal-time systems. In a dynamic priority scheduler, the tasks are executed in the order determined by their priority which is computed at run-time, also in this type of scheduler, as the name suggest, the
priority assignment is dynamic, the same task may have different priorities at different time. In the EDF,the priorities are assigned to the tasks according to their absolute deadlines, and the task with the earliest deadline for execution have the highest priority.
A set of periodic tasks is schedulable with EDF if and only if the following feasibility condition is respected:

$$\sum_{i=1}^n \frac{C_i}{T_i} \leq 1$$

Where C_i is the worst-case execution and Ti is the period of each task.

### 7.1.2 | EDF implementation

In order to ensure the correctness of the scheduler, the following assumptions are applied:

- Only periodic tasks are considered.

- Task deadline equals task period.

- Only schedulable tasks are set.

- Independent tasks without shared resources or synchronization issues.

The implementation details of the proposed Earliest Deadline First (EDF) scheduler are as follows:

- A configuration variable, configUSE_EDF_SCHEDULER, is added to the FreeRTOS configuration file (FreeRTOS.h). Setting this variable to 1 enables the EDF scheduler.

- A new Ready List (xReadyTasksListEDF) is declared and the method prvInitialiseTaskLists()
    has been modified in order to inizialize properly this new list;

- The prvAddTaskToReadyList() method is modified to insert tasks into xReadyTasksListEDF based on their deadlines.

- Task structures are updated to include a xTaskPeriod variable to store task periods.

- A new task initialization method, xTaskPeriodicCreate(), is created.

- The management of the IDLE task is adjusted to ensure it remains at the lowest priority and due to this constraint, also the vTaskStartScheduler() method is modified.

- The context switch mechanism (vTaskSwitchContext()) is modified to ensure the running task is
    correctly updated based on the new Ready List.


### 3.2 | implementation of floatToChar

The provided implementation, addresses the issue of printing float values from the terminal in C. It
introduces a function named floatToChar, which converts a floating-point number to a string.

Key points of the implementation include:

- Handling Negative Numbers: If the input number is negative, the function adds a minus sign
(’-’) to the output string and converts the number to its absolute value.

- Extraction of Integer and Decimal Parts: The function separates the floating-point number
into its integer and decimal components. It converts the integer part to a string using sprintf, then
proceeds to handle the decimal part separately.

- Converting Decimal Part to String: The decimal part is converted by multiplying it by 10 and
extracting the integer part of the result successively to obtain each decimal digit. These digits are
added to the string buffer, with the number of digits controlled by the precision parameter.

- String Termination: The resulting string is terminated with a null character to indicate the end
of the string.
