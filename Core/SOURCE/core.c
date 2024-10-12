/*
=======================================================================================================================
Author       : Mamoun
Module       : Core
File Name    : core.c
Date Created : Oct 6, 2024
Description  : Source file for the MamOS Core Module.
=======================================================================================================================
*/


/*=====================================================================================================================
 * [Details]     : This module hosts the fundamental kernel operations for MamOS.
 * [Future Work] : Change the kernel launch algorithm [calling the initial task manually].
 *                 Enhance error handling and detection.
 ====================================================================================================================*/

/*=====================================================================================================================
                                               < Includes >
=====================================================================================================================*/

#include "../../MamOSConfig.h"
#include "../../Others/std_types.h"
#include "../../Others/kernel_defs.h"
#include "../../Timer/INCLUDES/timer.h"
#include "../../System/INCLUDES/system.h"
#include "../../Memory/INCLUDES/memory.h"
#include "../../Scheduler/INCLUDES/scheduler.h"
#include "../../Queue/INCLUDES/queue.h"
#include "../../Task/INCLUDES/task.h"
#include "../INCLUDES/core_prv.h"
#include "../INCLUDES/core.h"

/*=====================================================================================================================
                                           < Global Variables >
=====================================================================================================================*/

/* Kernel Control Panel that maintains the entire system state. */
volatile MamOS_kernelControlPanelType G_kernelControlPanel = {0};

/*=====================================================================================================================
                                          < Functions Definitions >
=====================================================================================================================*/

/*=====================================================================================================================
 * [Function Name] : MamOS_init
 * [Description]   : Initializes the MamOS kernel and its core components.
 * [Arguments]     : The function Takes no arguments.
 * [return]        : The function returns void.
 ====================================================================================================================*/
void MamOS_init(void)
{
    /* Initialize all kernel subsystems. */
    MamOS_initMemory(&G_kernelControlPanel.kernelStackPointer);
    TIMER_setCallBackFunction(MamOS_schedulerTick);
    
    /* Set the PendSV interrupt periority to be the lowest interrupt priority in the system. */
    SYSTEM_setExceptionPriority(SYSTEM_PENDSV_EXCEPTION, 0XFF);

    /* Initialize Kernel Control Panel parameters. */
    G_kernelControlPanel.taskCounter = 0;
    G_kernelControlPanel.ticksCounter = 0;
    G_kernelControlPanel.mutexCounter = 0;
    G_kernelControlPanel.blockEmptyFlag = TRUE;
    G_kernelControlPanel.ptr2activeTask = NULL_PTR;
    G_kernelControlPanel.ptr2standbyTask = NULL_PTR;
    G_kernelControlPanel.readyQueue.ptr2headTask = NULL_PTR;
    G_kernelControlPanel.blockedQueue.ptr2headTask = NULL_PTR;
    
    /* Create the system idle task with lowest priority [(uint8)-1 = 255]. */
    MamOS_createTask(MamOS_idleTask, MAMOS_MIN_STACK_SIZE, (uint8)-1, 0);
}

/*=====================================================================================================================
 * [Function Name] : MamOS_launch
 * [Description]   : Launches the MamOS kernel and starts the first task execution.
 * [Arguments]     : The function Takes no arguments.
 * [return]        : The function returns void.
 ====================================================================================================================*/
void MamOS_launch(void)
{
    /* Load the initial task [the highest priority task] and remove it from the ready queue. */
    G_kernelControlPanel.ptr2activeTask = G_kernelControlPanel.readyQueue.ptr2headTask;
    MamOS_removeFromReadyQueue(G_kernelControlPanel.ptr2activeTask);

    /* Configure the system timer with a specific scheduler tick time. */
    TIMER_setPeriodicInterval(MAMOS_SCHEDULER_TICK_TIME);

    /* Set the stack pointer of the initial task as the system PSP. */
    __asm__ volatile ("LDR R2, =G_kernelControlPanel");
    __asm__ volatile ("LDR R2, [R2, #8]");
    __asm__ volatile ("LDR R2, [R2, #8]");
    __asm__ volatile ("MSR PSP, R2");

    /* Configure the system to run in unprivileged mode with PSP. */
    __asm__ volatile ("MSR CONTROL, %0" :: "r" (0X03));
    __asm__ volatile ("ISB");
    
    /* Start Initial task execution. */
    G_kernelControlPanel.ptr2activeTask->ptr2entryPoint();

    while(1);                                              /* Safety infinite loop [system should never reach here]. */
}

/*=====================================================================================================================
 * [Function Name] : MamOS_idleTask
 * [Description]   : System idle task that runs when no other tasks are ready.
 * [Arguments]     : The function Takes no arguments.
 * [return]        : The function returns void.
 ====================================================================================================================*/
static void MamOS_idleTask(void)
{
    while(1)
    {
        __asm__ volatile ("WFE");             /* WFE: Wait For Event - puts the processor into low-power sleep mode. */
    }
}
