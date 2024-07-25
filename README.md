# EDF implementation on FreeRTOs and examples with synchronization functions (Semaphore and Event Group)

# 1 | HaclOSsim

The assignment involves acquiring proficiency in utilizing an embedded operating system on an ISA
simulator, specifically QEMU , and customizing it to implement a new, straightforward feature, followed
by an evaluation on significant workloads. Potential operating systems for the project include:

- FreeRTOS
- Erika
- MicriumOS
- RT-Thread

The primary objectives of this project are as follows:

1. Gain proficiency in using QEMU for running an embedded operating system and create a tutorial
detailing the installation and usage procedures.
2. Develop practical examples/exercises demonstrating the functionality of the simulator/operating
system in alignment with the topics studied in class.
3. Customize the operating system to implement a new solution (e.g., scheduling, memory management,
etc.).
4. Evaluate and benchmark the performance improvement achieved by the newly implemented solution.
Completing items 1 and 2 is mandatory, contributing to a project evaluation of up to 24. Items 3 and 4,
while optional, are essential for achieving the maximum grade.

Our group has chosen FreeRTOS as OS to use.







# 2 | A brief theoretical overview

Before installing something we have to understand what we are installing and also why, in order to ensure
we’re not merely relying on copy-pasting commands without understanding their implications.

## 2.1 | Real-Time Operating Systems in Embedded Development

In this section, we’ll delve into the details of three integral components: Qemu, its significance when used
in conjunction with FreeRTOS, and the necessity of ARM GNU Embedded (toolchain):

- Qemu: QEMU, short for Quick EMUlator, is a powerful open-source software that allows you to
emulate and virtualize different hardware and operating systems on a host machine. It’s commonly
used in various scenarios, such as software development, testing, and running multiple operating
systems simultaneously. It’s a valuable tool for software developers, system administrators, and
anyone needing a flexible, virtualized environment for testing and development purposes..
In our case, using Qemu to simulate a processor running FreeRTOS, we are essentially creating a
virtual environment where we are able to test and debug our FreeRTOS-based applications without
needing physical hardware.

    This emulation enables you to:

    - Develop and Test: You can write, compile, and test your FreeRTOS-based applications in an
        environment that mimics the actual processor architecture. It helps identify bugs and ensures
        compatibility.

    - Debugging: QEMU provides debugging features that enable you to step through code, inspect
        memory, and track the execution flow of your FreeRTOS application. This is crucial for finding
        and fixing issues in the code.

    - Portability Testing: By simulating the processor architecture through QEMU, you can ensure
        that your FreeRTOS application behaves consistently across different platforms and processors,
        even if you don’t have access to all the hardware variations.

- FreeRTOS - FreeRTOS stands for "Real-Time Operating System". It’s an open-source, real-time
operating system kernel designed for embedded systems, specifically for microcontrollers and small
microprocessors. It’s used to manage the resources of these systems efficiently, providing multitasking,
real-time scheduling, and managing hardware interactions. FreeRTOS uses a preemptive, priority-
based scheduling algorithm.
    Scheduling:

    - Preemptive Scheduling: FreeRTOS uses preemptive scheduling, allowing higher priority tasks
            to interrupt lower priority tasks. This ensures that critical tasks can execute promptly.

    - Priority-Based: Tasks in FreeRTOS are assigned priorities. Higher priority tasks are executed
            before lower priority ones. This priority scheme helps in managing time-sensitive operations
            effectively.

    - Round-Robin: FreeRTOS also supports a round-robin scheduling mechanism within tasks of
            equal priority. This ensures fairness among tasks with the same priority level.
            Moreover, for Resource Management we need to specify that FreeRTOS provides synchronization
            mechanisms like semaphores and mutexes to manage shared resources among tasks. These aid in
            avoiding conflicts and ensuring proper resource utilization.

- ARM GNU Embedded toolchain - The ARM GNU Embedded toolchain is a collection of
open-source tools for developing software for ARM-based processors. It includes GCC, a highly
optimizing compiler. It can compile code for ARM architectures, providing efficient and optimized
machine code. Another specific tool is GDB, a powerful debugger that allows developers to step through code, inspect variables, and analyze the program’s behavior during execution. It supports debugging both local and remote targets running on ARM processors. ARM GNU Embedded toolchain is open-source. This allows developers to modify and contribute to its development,fostering a collaborative environment.




# 3 | Guide to installing QEMU for FreeRTOS debugging using the ARM GNU Embedded toolchain (Linux system)

This section focuses entirely on guiding you through the installation process of QEMU, setting up
FreeRTOS, and configuring the ARM GNU Embedded Toolchain. This isn’t a usage guide but rather an
initial setup that includes all the necessary commands and steps needed before utilizing these tools.


## 3.1 | Initial setup fo Ubuntu VM

In this chapter we will provides and illustrate the setup instructions and installation guide for using
FreeRTOS on QEMU on a Ubuntu virtual machine.

### 3.1.1 | Creation of the Ubuntu VM

In this guide we will use a Ubuntu VM hosted on VirtualBox. This is the recommended choice if you
can’t do a dual-boot installation on your machine; in fact this solution is prone to bugs and crashes and
so we highly recommend to use the dual-boot option.

For installing VirtualBox on your machine you can follow these steps:

1. Go to the VirtualBox website and download the latest version for your system.
2. Execute the installer and follow the installation steps.

After installing VirtualBox we have to create a VM with Ubuntu, you can follow this steps to create a VM

1. Download the Ubuntu ISO file from official website.
2. Open VirtualBox.
3. Click the botton *New*.
4. Configure the VM's settings however you like and cheking the voice wihich says deseable assisted configuration.
5. Click on ok and the execute your machine.
6. Once your machine is running procede to complete the personalisation of Ubuntu.

After creating the virtual machine you can install the VirtualBox Guest’s Additions, that will allow you
to share the clipboard between the VM and your actual machine, also this will allow you to see in full
screen the VM. In order to do so you have to:

1. Start the VM and open the terminal to executes this two commands:
    
        sudo apt update
        sudo apt install build−essential dkms linux−headers −$ ( uname −r )

    this will update and install necessary packets.

2. Check if the gcc and make have been installed.
3. Click on the "Device" option in the upper VirtualBox’s menu
4. Select the last option(with the CD icon) which says: *Insert Guest Additions CD image*
5. On the Ubuntu desktop it should appear a Cd icon, you should click on it and see if there is a .run
extension file, this file will setup the Guest’s Additions for VirtualBox.
6. To run the .run file from the terminal you have to open a terminal in this folder and execute this
command:
        
        sudo sh ./VBoxLinuxAdditions.run

7. To conclude you have to reboot the Virtual Machine.

At the end of this part you should have a running and functional Ubuntu virtual machine. If you want
to enable the shared clipboard between your machine and the VM you should power off the vm and
enter the VM settings and go to "System" an to the "Advanced" section and set the clipboard options to
bidirectional mode.



## 3.2 | Update Package Lists

Before installing new software, it’s good practice to ensure your system’s package lists are up-to-date.
This ensures that you’re fetching the latest versions of available software.

    #command to update system’s package lists
    1. sudo apt update

## 3.3 | Installing QEMU

- Install Required Dependencies

    QEMU has dependencies that need to be installed for successful compilation. These dependencies
    include build tools, libraries, and development packages.

        #command to install dependencies
        sudo apt install build-essential pkg-config zlib1g-dev libglib2.0-dev autoconf libtool libsdl1.2-dev

- Download of Qemu

    You’ll want to get the QEMU source code from its repository or you can use this command.

        sudo-get install qemu-system
    

## 3.4 | Shell’s Path:

An important step is include the qemu-system-arm emulator in your shell’s path. To check your path, run:

    which qemu-system-arm

Which should produce a valid path. If not you need manually to add QEMU to your shell’s path, in
Linux, you’ll need to modify the PATH environment variable. This variable contains a list of directories
where the shell looks for executable files. Adding QEMU to the PATH allows you to execute QEMU
commands from any directory in the terminal without specifying the full path to the executable. Firstly,
you need to know the directory where QEMU is installed. Usually, it’s in /usr/bin/ or /usr/local/bin/.

You can use the which command to find the path to the QEMU executable:

    which qemu

Open your shell configuration file (bashrc, bash profile, zshrc, or similar) using a text editor like nano or
vim. For example:

    sudo nano  ̃ /.bashrc

And you can add your path o the end of the file:

    export PATH=/path/to/qemu/directory:$PATH

Replace /path/to/qemu/directory with the actual path where QEMU is installed (output from the command
which qemu). After that you have to save the file and exit the text editor. Then, to apply the changes
immediately, either run:

    source  ̃ /.bashrc

or open a new terminal window/tab. Adding QEMU to the PATH simplifies command execution. You can run QEMU commands from any directory without needing to navigate to the specific directory where QEMU is installed. This convenience can improve workflow efficiency, especially when working on various projects or using QEMU frequently.


## 3.5 | Setting Up FreeRTOS and ARM GNU Embedded Toolchain:

- ARM GNU

    To install the arm tool-chain needed for building and executing Freertos on Qemu you have to follow this
    passages:

    1. Run this command to install the gcc

            sudo apt install arm-none-eabi-gcc

    2. Run this command to install the gdb

            sudo apt install arm-none-eabi-gdb

    __Note:__ Unfortunately this command will not install the arm version of gdb but another type of gdb called
    "gdb-multiarch". This is because the gdb-arm-none-eabi package was removed from Debian and
    therefore also from Ubuntu, because it was no longer maintained1. So, you could install gdb-multiarch, which should work for your purpose.

- FreeRTOS

    To set-up correctly FreeRTOS visit the official FreeRTOS website or its repository to download the
    FreeRTOS source code, in our case it was FreeRTOS v202212.01 repository.
    

### 3.5.1 | Building and executing the demo application - GCC Makefile

To execute the emulation of your demo on FeeRTOS on QEMU you have to follow this passages:

1. Open *FreeRTOS/Demo/CORTEX_MPS2_QEMU_IAR_GCC/main.c*

2. Set *mainCREATE_SIMPLE_BLINKY_DEMO_ONLY* to generate either the simply blinky demo, or the
comprehensive test and demo application, as required.

3. Open a command prompt and navigate to the *FreeRTOS/Demo/CORTEX_MPS2_QEMU_IAR_GCC/build/gcc*
directory.

4. Type "make" in the command prompt. The project should build without any compiler errors or
warnings1 A successful build creates the elf file RTOSDemo.out in the folder output. If you are not able to run this command be sure that you have already installed make in your system, in order to do this you can run:

        sudo apt install make

5. Start QEMU with the following command line, replacing *[path-to]* with the correct path to the *RTOSDemo.out* file generated by the GCC build or open the terminal in the output folder.

        qemu-system-arm -machine mps2-an385 -cpu cortex-m3 -kernel [path-to]/RTOSDemo.out -monitor none -nographic -serial stdio -s -S

   - __−machine mps2−an385__:
    specifies the model of the machine to emulate, in this case an ARM MPS2 development board
    with a Cortex-M3 CPU.

   - __-cpu cortex-m3__:
    specifies the type of CPU to emulate, in this case a Cortex-M3 CPU that is an ARMv7-M
    CPU.

   - __−kernel [path-to]/RTOSDemo.out__:
    specifies the file that contains the kernel or the firmware to load and run on the emulated
    machine, in this case a file called RTOSDemo.out that is located in a certain folder.

   - __−monitor none__:
    disables the monitor of QEMU, which is an interactive console that allows you to control and
    monitor the emulated machine.

   - __-nographic__:
    disables the graphics of QEMU, which is a window that shows the video output of the emulated
    machine.

   - __-serial stdio__:
    redirects the serial output of the emulated machine to the standard input/output of the terminal
    that runs QEMU, so that you can interact with the emulated machine through the terminal.

   - __−s__:
    enables a GDB server on port 1234, which allows you to debug the emulated machine through
    a GDB client.

   - __−S__:
    freezes the CPU at startup, so that you can start the emulated machine only after connecting
    it to the GDB client.


6. Write this command to link the gdb, replacing *[path-to]* with the correct path to the *RTOSDemo.out* file generated by the GCC build or open the terminal in the output folder:

        gdb [path-to]/RTOSDemo.out

7. Connect to QEMU (the default port for QEMU is 1234) with the following command:

        target remote localhost:1234

8. Now you can use the commands of the debugger 





# 4 | Guide to installing QEMU for FreeRTOS debugging using the VisualStudio Code Debug configuration (macOS 14 Sonoma system)

## 4.1 | Brew Installation

To install QEMU and the ARM toolchain, it is necessary to use Homebrew. Homebrew is a package
manager for macOS that significantly simplifies the software installation and management process. This
choice is particularly advantageous because it allows you to easily obtain all the dependencies and libraries
required for QEMU and the ARM toolchain, enabling you to quickly start working on ARM-related
projects on macOS. By using Homebrew, the risk of installation errors is reduced, ensuring greater
efficiency in the overall development and testing process.

    # I installed Homebrew by running the following command in my Terminal:
    /bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/HEAD/install.sh)"

This command executed a script that installed Homebrew on my system. This script fetches the Homebrew
installation script from its GitHub repository and runs it using the /bin/bash shell, which sets up
Homebrew on your macOS system. It’s a convenient way to get Homebrew up and running, allowing you
to easily manage software packages and dependencies.

## 4.2 | Installing QEMU

- Download of Qemu
    Using Homebrew to install QEMU and its dependencies is a smart choice, as it simplifies the
    installation process and ensures you have the latest version. It’s a convenient package manager for
    macOS that can save you a lot of time and effort.

        sudo brew install qemu

    To confirm that QEMU has been successfully installed, you can check its version using the following
    command in the Terminal:

        qemu-system-x86_64 --version

## 4.3 | Setting Up FreeRTOS and ARM GNU Embedded Toolchain:

- ARM GNU

    To install the ARM-none-eabi-gcc toolchain, you can use Homebrew’s formula provided by ar-
    mmbed/formulae. Run the following command:

        brew install arm-none-eabi-gcc

    After the installation is complete, you can verify whether ARM-none-eabi-gcc is installed successfully.

        arm-none-eabi-gcc --version

- FreeRTOS:

    To set up FreeRTOS correctly, we visited the official FreeRTOS website to download the FreeRTOS
    source code. In our case, we used the "FreeRTOS v202212.01 repository."
    Once you’ve obtained the source code, the final step is to build and run the demo to ensure that
    everything has been installed correctly. Navigate to the demo folder, and execute the following
    command:

        make

    This action will generate a "Build" directory housing an executable file. In our scenario, we named it "RTOSDemo.out."

## 4.4 | Shell’s Path

Configuring the system PATH is a crucial step in ensuring that the toolchain is readily accessible from
any directory within your system. By adding the toolchain’s path to the system’s PATH variable, you
streamline the process of using the toolchain for development and execution of commands.

    nano  ̃ /.bash_profile

Append the following line to the file, replacing / path/to/toolchain/bin with the actual path to your
toolchain’s bin directory:

    export PATH=$PATH:/path/to/toolchain/bin

To apply the changes immediately, you can either restart your Terminal session or run the following
command:

    source  ̃ /.bash_profile

By making this modification, you ensure that the toolchain’s binaries are accessible system-wide, simplifying
your development workflow and enabling you to use the toolchain from any directory in your macOS
environment.

## 4.5 | FreeRTOS Visual Studio Debug

Debugging FreeRTOS applications in Visual Studio is a crucial step in ensuring the reliability and
performance of your embedded systems. In this chapter, we’ll walk through the process of setting up and
debugging a FreeRTOS project in Visual Studio.

### Configure Project Settings

To enable the execution of "Build""RTOSDemo.out" while running it in QEMU, it’s necessary to create
or modify a configuration within the "Build"".vscode" folder of your Visual Studio Code project. This
configuration file is typically named "Build""launch.json" and contains parameters that specify how the
debugging process should be set up.

    {
        "version": "0.2.0",
        "configurations": [
            {
            "name": "Launch QEMU RTOSDemo", // Name of the configuration
            "type": "cppdbg", // Debugging type for C/C++ projects
            "request": "launch", // Launch request
            "program": "Path to the executable to debug",
            "cwd": "${workspaceFolder}", // Current working directory
            "miDebuggerPath": "// Path to the debugger executable",
            "miDebuggerServerAddress": "localhost:1234",
            "stopAtEntry": true,
            "preLaunchTask": "Run QEMU"
            }
        ]
    }

- Customize Configurations

    - __Name__: You can customize the name of the configuration to reflect its purpose.

    - __Program__: Specify the path to the "RTOSDemo.out" executable.

    - __miDebuggerPath__: Set the path to the debugger executable (e.g., GDB for ARM-none-eabi).

    - __miDebuggerServerAddress__: Configure the address and port where the debugger server for QEMU is
    running.

    - __stopAtEntry__: Decide whether to stop at the program’s entry point.

    - __preLaunchTask__: If you need to run any pre-launch tasks (e.g., starting QEMU), specify their names
    here.

Start Debugging Now, when you want to debug your "RTOSDemo.out" in QEMU, you can select this
configuration in Visual Studio Code and start the debugging session. This configuration automates the
process of launching QEMU and debugging your application.





# 5 | Guide to install QEMU and execute FreeRTOS demos on Windows

## 5.1 | Installing MYSYS2

Install MYSYS2 following these instructions or this link: https://www.msys2.org/
1. Download the installer: msys2-x86_64-20240113.exe

2. Run the installer.

3. Enter your desired Installation Folder.

4. When done, click Finish.

Now MSYS2 is ready for you and a terminal for the UCRT64 environment will launch.

## 5.2 | Installing QEMU

- Install QEMU using one of the following commmands:
    - For 32 bit Windows 7 or above (in MINGW32):
            pacman -S mingw-w64-i686-qemu
    - For 64 bit Windows 7 or above (in MINGW64):
            pacman -S mingw-w64-x86_64-qemu
    - For 64 bit Windows 8.1 or above (in UCRT64):
            pacman -S mingw-w64-ucrt-x86_64-qemu

## 5.2 | Installing ARM Toolchain

Download arm-none-eabi-gcc compiler from: https://developer.arm.com/downloads/-/arm-gnu-toolchain-downloads

1. Run the installer.
2. Enter your desired Installation Folder.
3. When done, click Finish.

## 5.3 | Installing and setting up FreeRTOS

To execute the emulation of your demo on FeeRTOS on QEMU you have to follow this passages:

1. Download FreeRTOS from his website: https://www.freertos.org/index.html
2. Add the path to your arm-none-eabi-gcc compiler, to your environment variables:
    - Search "Edit the system environment variables" on yur PC;
    - in the "Advanced" tab, click on "Environment Variables";
    - in the section "User variables" click on "New", then "Browse Dyrectory" and find the path of your arm compiler; then confirm;

3. install Cmake from this link: https://cmake.org/download/

4. Now you are ready to execute your FreeRTOS demo:
    - Open FreeRTOS/Demo/CORTEX_MPS2_QEMU_IAR_GCC/main.c, and set mainCREATE_SIMPLE_BLINKY_DEMO_ONLY to 1
    - Open a command prompt and navigate to the FreeRTOS/Demo/CORTEX_MPS2_QEMU_IAR_GCC/build/gcc directory.
    - Type "make" in the command prompt. The project should build without any compiler errors
    - A successful build creates the file FreeRTOS/Demo/CORTEX_MPS2_QEMU_IAR_GCC/build/gcc/output/RTOSDemo.out.
    - open your MYSYS2 terminal (the one where you installed QEMU) and start QEMU with the following command line, replacing [path-to]  with the correct path to the RTOSDemo.out file generated by the GCC build:

            qemu-system-arm -machine mps2-an385 -cpu cortex-m3 -kernel [path-to]/RTOSDemo.out -monitor none -nographic -serial stdio -s -S
        Omit the "-s -S" if you just want to run the FreeRTOS application in QEMU without attaching the debugger.
         
5. Now, if you want to attach the debugger:
    - open a terminal (PowerShell) and type: 

                 arm-none-eabi-gdb [path-to]/RTOSDemo.out

    - Connect to QEMU (the default port for QEMU is 1234) with the following command:

                target remote localhost:1234

6. Now you can use the commands of the debugger 






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


# 6 | Enhancing Learning Through Practical Scenarios: Applying Simulator and OS Concepts

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

## 6.1 | Resource Access Control in a Manufacturing Plant:

__Scenario Overview__ 

In a manufacturing plant, multiple automated processes need controlled access
to a critical resource, such as a robotic arm used for assembly. The processes must efficiently utilize
the robotic arm while avoiding collisions and resource contention.

__System Components__

- Tasks: Represent automated processes (e.g., assembly, quality checks).
- Resource: Represents the robotic arm utilized for assembly tasks.
- FreeRTOS: Embedded real-time operating system facilitating task management.

## 6.1.1 | Manage the access of various assembly task to the robotic arm through taskExample1:

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



## 6.2 | Data Management in Environmental Monitoring: FreeRTOS UseCase

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



# 7 | FreeRTOS customization 

## 7.1 | implementation of Earliest Deadline First (EDF) scheduler

### 7.1.1 | EDF dynamic scheduling algorithm

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


### 7.2 | implementation of floatToChar

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

# 8 | Implementing Task Synchronization and Periodic Scheduling in FreeRTOS

## 8.1 | Overview
The code defines two periodic tasks, TSK A and TSK B, each with its own execution time (task1 C and task2 C) and period (task1 T and task2 T).
The main part of the code checks the schedulability of these tasks using isSchedulable function and, if schedulable, creates the tasks with xTaskPeriodicCreate and starts the FreeRTOS scheduler with vTaskStartScheduler().

## 8.2 | Main Concepts

- Tasks: In FreeRTOS, tasks are independent threads of execution. Each task is defined by a function,
such as TSK A and TSK B, that includes the task’s code.

- Periodicity: Each task is designed to execute periodically, with its period specified by task1 T and
task2 T. The period is the time interval between successive starts of the task.

- Execution Time: The execution time (task1 C and task2 C) represents how long each task takes to
complete its duties before it yields control back to the scheduler.

- Schedulability Check: Before starting the tasks, the code checks if the tasks are schedulable
(isSchedulable function), ensuring that the system can meet all task deadlines under the specified
constraints.

- Task Creation and Scheduling: Using xTaskPeriodicCreate, each task is created with a specified
priority, stack size, and period. The scheduler is then started with vTaskStartScheduler, at which
point the tasks begin executing according to their periods and priorities.

- xTaskGetTickCount: This function returns the current tick count, providing a time reference for
scheduling periodic activities.

## 8.3 | Key FreeRTOS Concepts

- traceTASK SWITCHED OUT: This macro logs a message every time a task is switched out of the
CPU. It uses pcTaskGetName(NULL) to get the name of the currently running task, which is being
switched out, and prints a message indicating that this task has been switched out.

- traceTASK SWITCHED IN: Similar to the previous macro, but in this case, it logs a message every
time a task is switched into the CPU. It also uses pcTaskGetName(NULL) to get the name of the
task that is now running and prints a message indicating that this task has been switched in.

- traceTASK DELAY UNTIL: This macro logs a message when a task is put into a delay until a
specified time (xTimeToWake). It’s used to trace when tasks are being delayed, which is common
in RTOS for managing task execution timing and ensuring tasks do not run longer than necessary.
The macro also uses pcTaskGetName(NULL) to identify the task being delayed.

## 8.4 | Tests and Results

Each task function obtains the current tick count upon entry (xLastWakeTime = xTaskGetTickCount())
to establish a reference time for its periodic execution.
They simulate the task’s execution time by delaying for task1 C or task2 C ticks, respectively.
Then, they use vTaskDelayUntil to wait until the next period, effectively pacing the task to run at its specified periodic rate.
When the EDF scheduler is enabled, the snippet defines three macros (traceTASK SWITCHED OUT,
traceTASK SWITCHED IN, and traceTASK DELAY UNTIL) that are used for tracing task behavior.
These macros make use of the printf function to log messages related to task switching and delays, as
example below:

    FEASIBLE CPU UTILIZATION: 100.0
    TASK A SWITCHED IN
    TASK A DELAYING UNTIL 2
    TASK A SWITCHED OUT
    TASK B SWITCHED IN
    TASK B DELAYING UNTIL 2
    TASK B SWITCHED OUT
    TASK IDLE SWITCHED IN
    TICK : 1
    TICK : 2
    TASK IDLE SWITCHED OUT
    TASK A SWITCHED IN
    TASK A DELAYING UNTIL 4
    TASK A SWITCHED OUT
    TASK B SWITCHED IN
    TASK B DELAYING UNTIL 4
    TASK B SWITCHED OUT
    TASK IDLE SWITCHED IN
    TICK : 3
    TICK : 4
    TASK IDLE SWITCHED OUT

- Task Alternation and CPU Utilization: The output shows that tasks A and B alternate in execution,
respecting their WCETs of 2 time units and waiting for their next period to be executed again. This
is in accordance with the CPU utilization calculation that indicates 100.

- Delays Until Specific Ticks: The output shows that each task executes for a period, then puts itself
on hold (”DELAYING”) until the specified tick. This pattern repeats, with tasks being scheduled to
execute at their appropriate periods. This behavior is consistent with a system that uses EDF to
handle periodic tasks with fixed deadlines.

- Task Idle: There are periods when the ”IDLE” task is scheduled between the execution of tasks
A and B. This indicates that, after executing each task and waiting until the next deadline, the
processor has no tasks to execute, correctly reflecting the periods when tasks A and B are inactive
due to their scheduled waits.
