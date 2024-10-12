/*
=======================================================================================================================
Author       : Mamoun
Module       : Scheduler
File Name    : scheduler.c
Date Created : Oct 8, 2024
Description  : Source file for the MamOS Scheduler module.
=======================================================================================================================
*/


/*=====================================================================================================================
 * [Details]     : This module hosts the functionality of the MamOS Scheduler,
 *                 including task switching logic, blocked task management, and system tick handling.
 ====================================================================================================================*/

/*=====================================================================================================================
                                               < Includes >
=====================================================================================================================*/

#include "../../Others/std_types.h"
#include "../../Others/kernel_defs.h"
#include "../../System/INCLUDES/system.h"
#include "../../Queue/INCLUDES/queue.h"
#include "../INCLUDES/scheduler_prv.h"
#include "../INCLUDES/scheduler.h"

/*=====================================================================================================================
                                           < Global Variables >
=====================================================================================================================*/

/* Extern the Kernel Control Panel. */
extern MamOS_kernelControlPanelType G_kernelControlPanel;

/*=====================================================================================================================
                                          < Functions Definitions >
=====================================================================================================================*/

/*=====================================================================================================================
 * [Function Name] : MamOS_schedulerTick
 * [Description]   : Called every system tick to update the blocked queue, and make a context switch
 *                   if the system is preemptive and there is a higher priority task.
 * [Arguments]     : The function Takes no arguments.
 * [return]        : The function returns void.
 ====================================================================================================================*/
void MamOS_schedulerTick(void)
{
    /* Update the blocked queue if it's not empty. */
    if(G_kernelControlPanel.blockEmptyFlag == FALSE)
    {
        MamOS_updateBlockedQueue();
    }

    /* Check if the scheduler is preemptive. */
    #if (MAMOS_PREEMPRIVE_SCHEDULER == TRUE)
    /* Check if there is a higher priority task in the ready queue. */
    if(G_kernelControlPanel.readyQueue.ptr2headTask->priority <= G_kernelControlPanel.ptr2activeTask->priority)
    {
        /* Fetch the higher priority task from the ready queue. */
        G_kernelControlPanel.ptr2standbyTask = G_kernelControlPanel.readyQueue.ptr2headTask;
        MamOS_removeFromReadyQueue(G_kernelControlPanel.ptr2standbyTask);
        
        /* Move current task back to ready queue if it's not the idle task. */
        if(G_kernelControlPanel.ptr2activeTask->id != MAMOS_IDLE_TASK_ID)
        {
            MamOS_addToReadyQueue(G_kernelControlPanel.ptr2activeTask);
        }
        
        /* Trigger PendSV exception to perform context switch. */
        SYSTEM_setExceptionPending(SYSTEM_PENDSV_EXCEPTION);
    }
    #endif
}

/*=====================================================================================================================
 * [Function Name] : MamOS_forceTaskTransition
 * [Description]   : Initiates an immediate context switch.
 * [Arguments]     : The function Takes no arguments.
 * [return]        : The function returns void.
 ====================================================================================================================*/
void MamOS_forceTaskTransition(void)
{
    /* Fetch the higher priority task from the ready queue. */
    G_kernelControlPanel.ptr2standbyTask = G_kernelControlPanel.readyQueue.ptr2headTask;
    MamOS_removeFromReadyQueue(G_kernelControlPanel.ptr2standbyTask);

    /* Move the current task to the blocked queue [if it's not waiting or idle]. */
    if((G_kernelControlPanel.ptr2activeTask->state != MAMOS_WAITING_TASK) && (G_kernelControlPanel.ptr2activeTask->id != MAMOS_IDLE_TASK_ID))
    {
        MamOS_addToBlockedQueue(G_kernelControlPanel.ptr2activeTask);
    }

    /* Trigger PendSV exception to perform context switch. */
    SYSTEM_setExceptionPending(SYSTEM_PENDSV_EXCEPTION);
}

/*=====================================================================================================================
 * [Function Name] : MamOS_updateBlockedQueue
 * [Description]   : Updates the system tick counter and check if there are any expired delays.
 * [Arguments]     : The function Takes no arguments.
 * [return]        : The function returns void.
 ====================================================================================================================*/
static void MamOS_updateBlockedQueue(void)
{
    G_kernelControlPanel.ticksCounter++;

    /* Move the tasks with expired delays to the ready queue. */
    while(G_kernelControlPanel.ticksCounter == G_kernelControlPanel.blockedQueue.ptr2headTask->delayTicks)
    {
        MamOS_taskControlBlockType* LOC_ptr2currentTask = G_kernelControlPanel.blockedQueue.ptr2headTask;
        MamOS_removeFromBlockedQueue(LOC_ptr2currentTask);
        MamOS_addToReadyQueue(LOC_ptr2currentTask);
    }
}
