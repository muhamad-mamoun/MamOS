/*
=======================================================================================================================
Author       : Mamoun
Module       : Task
File Name    : task.c
Date Created : Oct 7, 2024
Description  : Source file for the MamOS Task module.
=======================================================================================================================
*/


/*=====================================================================================================================
 * [Details]     : This module handles task management operations in MamOS,
 *                 including task creation, suspension, resumption, and delay operations.
 * [Future Work] : Support more APIs to easily manage tasks.
 *                 Enhance error handling and detection.
 ====================================================================================================================*/

/*=====================================================================================================================
                                               < Includes >
=====================================================================================================================*/

#include "../../Others/std_types.h"
#include "../../Others/kernel_defs.h"
#include "../../Queue/INCLUDES/queue.h"
#include "../INCLUDES/task_prv.h"
#include "../INCLUDES/task.h"

/*=====================================================================================================================
                                           < Global Variables >
=====================================================================================================================*/

/* Array of task control blocks for all tasks in the system. */
volatile static MamOS_taskControlBlockType G_taskControlBlocks[MAMOS_TOTAL_NUM_OF_TASKS] = {0};

/* Extern the Kernel Control Panel. */
extern MamOS_kernelControlPanelType G_kernelControlPanel;

/*=====================================================================================================================
                                          < Functions Definitions >
=====================================================================================================================*/

/*=====================================================================================================================
 * [Function Name] : MamOS_createTask
 * [Description]   : Creates a new task, sets up its stack, and adds it to the ready queue.
 * [Arguments]     : <a_ptr2taskEntryPoint> -> Pointer to the task entry point.
 *                   <a_taskStackSize>      -> Indicates to the task stack size [in words].
 *                   <a_priority>           -> Indicates to the task priority [0 ~ 255].
 *                   <a_periodicity>        -> Indicates to the periodic task periodicity [in system ticks].
 * [return]        : The function returns void.
 ====================================================================================================================*/
void MamOS_createTask(void (*a_ptr2taskEntryPoint)(void), uint16 a_taskStackSize, uint8 a_priority, uint16 a_periodicity)
{
    if(G_kernelControlPanel.taskCounter > MAMOS_MAX_NUM_OF_TASKS)
    {
        /* Invalid Operation. */
    }

    else if(a_ptr2taskEntryPoint == NULL_PTR)
    {
        /* Invalid Operation. */
    }

    else if(a_taskStackSize > MAMOS_MAX_STACK_SIZE)
    {
        /* Invalid Operation. */
    }

    else
    {
        /* Initialize task control block. */
        G_taskControlBlocks[G_kernelControlPanel.taskCounter].id = G_kernelControlPanel.taskCounter;
        G_taskControlBlocks[G_kernelControlPanel.taskCounter].delayTicks = 0;
        G_taskControlBlocks[G_kernelControlPanel.taskCounter].priority = a_priority;
        G_taskControlBlocks[G_kernelControlPanel.taskCounter].periodicity = a_periodicity;
        G_taskControlBlocks[G_kernelControlPanel.taskCounter].stackSize = a_taskStackSize;
        G_taskControlBlocks[G_kernelControlPanel.taskCounter].ptr2entryPoint = a_ptr2taskEntryPoint;
        G_taskControlBlocks[G_kernelControlPanel.taskCounter].state = MAMOS_READY_TASK;
        G_taskControlBlocks[G_kernelControlPanel.taskCounter].stackPointer = G_kernelControlPanel.kernelStackPointer;

        MamOS_initTaskStack(a_ptr2taskEntryPoint, &G_taskControlBlocks[G_kernelControlPanel.taskCounter].stackPointer);
        MamOS_addToReadyQueue(&G_taskControlBlocks[G_kernelControlPanel.taskCounter]); /* Add it to the ready queue. */

        /* Update the kernel stack pointer and the task counter. */
        G_kernelControlPanel.kernelStackPointer -= a_taskStackSize;
        G_kernelControlPanel.taskCounter++;
    }
}

/*=====================================================================================================================
 * [Function Name] : MamOS_initTaskStack
 * [Description]   : Sets up the initial stack frame for a task.
 * [Arguments]     : <a_ptr2taskEntryPoint>   -> Pointer to the task entry point.
 *                   <a_ptr2taskStackPointer> -> Pointer to the task stack pointer.
 * [return]        : The function returns void.
 ====================================================================================================================*/
static void MamOS_initTaskStack(void (*a_ptr2taskEntryPoint)(void), uint32** a_ptr2taskStackPointer)
{
    (*a_ptr2taskStackPointer)--;
    (**a_ptr2taskStackPointer) = 0X01000000;                                      /* Set up the xPSR register value. */

    (*a_ptr2taskStackPointer)--;
    (**a_ptr2taskStackPointer) = (uint32)a_ptr2taskEntryPoint;                      /* Set up the PC register value. */

    (*a_ptr2taskStackPointer)--;
    (**a_ptr2taskStackPointer) = 0XFFFFFFFD;                                        /* Set up the LR register value. */

    /* Set up the {R0-R3, R12} registers value. */
    for(uint8 counter = 0; counter < 5; counter++)
    {
        (*a_ptr2taskStackPointer)--;
        (**a_ptr2taskStackPointer) = 0X00000000;
    }

    /* Set up the {R4-R11} registers value [optional]. */
    for(uint8 counter = 0; counter < 8; counter++)
    {
        (*a_ptr2taskStackPointer)--;
        (**a_ptr2taskStackPointer) = 0XDEAEAEAD;
    }
}

/*=====================================================================================================================
 * [Function Name] : MamOS_suspendTask
 * [Description]   : Suspends a specified task from scheduling.
 * [Arguments]     : <a_ptr2taskEntryPoint> -> Indicates to the required task to be suspended.
 * [return]        : The function returns void.
 ====================================================================================================================*/
void MamOS_suspendTask(void (*a_ptr2taskEntryPoint)(void))
{
    /* Search for the required task. */
    for(uint8 iterator = 1; iterator < G_kernelControlPanel.taskCounter; iterator++)
    {
        if(G_taskControlBlocks[iterator].ptr2entryPoint == a_ptr2taskEntryPoint)
        {
            if(G_taskControlBlocks[iterator].state == MAMOS_READY_TASK)
            {
                MamOS_removeFromReadyQueue(&G_taskControlBlocks[iterator]);
            }

            else if(G_taskControlBlocks[iterator].state == MAMOS_BLOCKED_TASK)
            {
                MamOS_removeFromBlockedQueue(&G_taskControlBlocks[iterator]);
            }

            G_taskControlBlocks[iterator].state = MAMOS_SUSPENDED_TASK;
            break; /* Task found and suspended, exit the loop. */
        }
    }
}

/*=====================================================================================================================
 * [Function Name] : MamOS_resumeTask
 * [Description]   : Resumes a suspended task.
 * [Arguments]     : <a_ptr2taskEntryPoint> -> Indicates to the required task to be resumed.
 * [return]        : The function returns void.
 ====================================================================================================================*/
void MamOS_resumeTask(void (*a_ptr2taskEntryPoint)(void))
{
    /* Search for the required task. */
    for(uint8 iterator = 1; iterator < G_kernelControlPanel.taskCounter; iterator++)
    {
        if(G_taskControlBlocks[iterator].ptr2entryPoint == a_ptr2taskEntryPoint)
        {
            MamOS_addToReadyQueue(&G_taskControlBlocks[iterator]);
            break; /* Task found and resumed, exit the loop. */
        }
    }
}

/*=====================================================================================================================
 * [Function Name] : MamOS_taskDelay
 * [Description]   : Delays the current task for a specified number of ticks.
 * [Arguments]     : <a_delayTicks> -> Indicates to the number of ticks to delay the task.
 * [return]        : The function returns void.
 ====================================================================================================================*/
void MamOS_taskDelay(uint16 a_delayTicks)
{
    /* Set the delay for the active task with a specific value and request a task transition. */
    G_kernelControlPanel.ptr2activeTask->delayTicks = a_delayTicks;
    MAMOS_TASK_TRANS_REQUEST();
}

/*=====================================================================================================================
 * [Function Name] : MamOS_taskYield
 * [Description]   : Yields the current task after finishing its function allowing other tasks to run.
 * [Arguments]     : The function Takes no arguments.
 * [return]        : The function returns void.
 ====================================================================================================================*/
void MamOS_taskYield(void)
{
    /* Set the delay for the active task to its periodicity and request a task transition. */
    G_kernelControlPanel.ptr2activeTask->delayTicks = G_kernelControlPanel.ptr2activeTask->periodicity;
    MAMOS_TASK_TRANS_REQUEST();
}
