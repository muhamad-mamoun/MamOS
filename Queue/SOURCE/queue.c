/*
=======================================================================================================================
Author       : Mamoun
Module       : Queue
File Name    : queue.c
Date Created : Oct 9, 2024
Description  : Source file for the MamOS Queue moduler.
=======================================================================================================================
*/


/*=====================================================================================================================
 * [Details]     : This module manages all the queues in MamOS [Ready, Blocked, and Waiting].
 ====================================================================================================================*/

/*=====================================================================================================================
                                               < Includes >
=====================================================================================================================*/

#include "../../Others/std_types.h"
#include "../../Others/kernel_defs.h"
#include "../INCLUDES/queue_prv.h"
#include "../INCLUDES/queue.h"

/*=====================================================================================================================
                                           < Global Variables >
=====================================================================================================================*/

/* Extern the Kernel Control Panel. */
extern MamOS_kernelControlPanelType G_kernelControlPanel;

/*=====================================================================================================================
                                          < Functions Definitions >
=====================================================================================================================*/

/*=====================================================================================================================
 * [Function Name] : MamOS_addToReadyQueue
 * [Description]   : Adds a specific task to the ready queue and change its state.
 * [Arguments]     : <a_ptr2taskControlBlock>    -> Pointer to the task to be added to the ready queue.
 * [return]        : The function returns void.
 ====================================================================================================================*/
void MamOS_addToReadyQueue(MamOS_taskControlBlockType* a_ptr2taskControlBlock)
{
    a_ptr2taskControlBlock->state = MAMOS_READY_TASK;
    MamOS_addToQueue(&G_kernelControlPanel.readyQueue, MAMOS_PRIORITY_COMPARATOR_ID, a_ptr2taskControlBlock);
}

/*=====================================================================================================================
 * [Function Name] : MamOS_removeFromReadyQueue
 * [Description]   : Removes a specific task from the ready queue.
 * [Arguments]     : <a_ptr2taskControlBlock>    -> Pointer to the task to be removed from the ready queue.
 * [return]        : The function returns void.
 ====================================================================================================================*/
void MamOS_removeFromReadyQueue(MamOS_taskControlBlockType* a_ptr2taskControlBlock)
{
    if(a_ptr2taskControlBlock->id == MAMOS_IDLE_TASK_ID)
    {
        /* Invalid Operation [system idle task can not be removed from the ready queue]. */
    }
    
    else
    {
        MamOS_removeFromQueue(&G_kernelControlPanel.readyQueue, a_ptr2taskControlBlock);
    }
}

/*=====================================================================================================================
 * [Function Name] : MamOS_addToBlockedQueue
 * [Description]   : Adds a specific task to the blocked queue and change its state.
 * [Arguments]     : <a_ptr2taskControlBlock>    -> Pointer to the task to be added to the blocked queue.
 * [return]        : The function returns void.
 ====================================================================================================================*/
void MamOS_addToBlockedQueue(MamOS_taskControlBlockType* a_ptr2taskControlBlock)
{
    G_kernelControlPanel.blockEmptyFlag = FALSE;
    a_ptr2taskControlBlock->state = MAMOS_BLOCKED_TASK;
    a_ptr2taskControlBlock->delayTicks += G_kernelControlPanel.ticksCounter;
    MamOS_addToQueue(&G_kernelControlPanel.blockedQueue, MAMOS_DELAY_COMPARATOR_ID, a_ptr2taskControlBlock);
}

/*=====================================================================================================================
 * [Function Name] : MamOS_removeFromBlockedQueue
 * [Description]   : Removes a specific task from the blocked queue.
 * [Arguments]     : <a_ptr2taskControlBlock>    -> Pointer to the task to be removed from the blocked queue.
 * [return]        : The function returns void.
 ====================================================================================================================*/
void MamOS_removeFromBlockedQueue(MamOS_taskControlBlockType* a_ptr2taskControlBlock)
{
    MamOS_removeFromQueue(&G_kernelControlPanel.blockedQueue, a_ptr2taskControlBlock);

    /* If the blocked queue is empty after removing the task, set the flag and reset the tick counter. */
    if(G_kernelControlPanel.blockedQueue.ptr2headTask == NULL_PTR)
    {
        G_kernelControlPanel.blockEmptyFlag = TRUE;
        G_kernelControlPanel.ticksCounter = 0;
    }
}

/*=====================================================================================================================
 * [Function Name] : MamOS_addToWaitingQueue
 * [Description]   : Adds a specific task to the waiting queue of a specific mutex and change its state.
 * [Arguments]     : <a_ptr2mutex>            -> Pointer to the mutex.
 *                   <a_ptr2taskControlBlock> -> Pointer to the task to be added to the waiting queue.
 * [return]        : The function returns void.
 ====================================================================================================================*/
void MamOS_addToWaitingQueue(MamOS_mutexHandle a_ptr2mutex, MamOS_taskControlBlockType* a_ptr2taskControlBlock)
{
    a_ptr2taskControlBlock->state = MAMOS_WAITING_TASK;
    MamOS_addToQueue(&a_ptr2mutex->waitingQueue, MAMOS_PRIORITY_COMPARATOR_ID, a_ptr2taskControlBlock);
}

/*=====================================================================================================================
 * [Function Name] : MamOS_removeFromWaitingQueue
 * [Description]   : Removes a specific task from the waiting queue of a specific mutex.
 * [Arguments]     : <a_ptr2mutex>            -> Pointer to the mutex.
 *                   <a_ptr2taskControlBlock> -> Pointer to the task to be removed from the waiting queue.
 * [return]        : The function returns void.
 ====================================================================================================================*/
void MamOS_removeFromWaitingQueue(MamOS_mutexHandle a_ptr2mutex, MamOS_taskControlBlockType* a_ptr2taskControlBlock)
{
    MamOS_removeFromQueue(&a_ptr2mutex->waitingQueue, a_ptr2taskControlBlock);
}

/*=====================================================================================================================
 * [Function Name] : MamOS_addToQueue
 * [Description]   : Adds a specific task to a specific queue.
 * [Arguments]     : <a_ptr2queue>            -> Pointer to the required queue.
 *                   <a_comparator>           -> Type of comparison when adding the task (priority or delay).
 *                   <a_ptr2taskControlBlock> -> Pointer to the task to be added to the queue.
 * [return]        : The function returns void.
 ====================================================================================================================*/
static void MamOS_addToQueue(MamOS_QueueType* a_ptr2queue, uint8 a_comparator, MamOS_taskControlBlockType* a_ptr2taskControlBlock)
{
    /* Handle empty queue case. */
    if(a_ptr2queue->ptr2headTask == NULL_PTR)
    {
        a_ptr2taskControlBlock->ptr2nextTask = NULL_PTR;
        a_ptr2queue->ptr2headTask = a_ptr2taskControlBlock;
        a_ptr2queue->ptr2rearTask = a_ptr2taskControlBlock;
    }

    /* Handle insertion at head if new task has higher priority/earlier deadline. */
    else if(MAMOS_GET_COMPARATOR_VALUE(a_ptr2queue->ptr2headTask, a_comparator) > MAMOS_GET_COMPARATOR_VALUE(a_ptr2taskControlBlock, a_comparator))
    {
        a_ptr2taskControlBlock->ptr2nextTask = a_ptr2queue->ptr2headTask;
        a_ptr2queue->ptr2headTask = a_ptr2taskControlBlock;
    }

    /* Handle single element queue case. */
    else if(a_ptr2queue->ptr2headTask->ptr2nextTask == NULL_PTR)
    {
        a_ptr2taskControlBlock->ptr2nextTask = NULL_PTR;
        a_ptr2queue->ptr2headTask->ptr2nextTask = a_ptr2taskControlBlock;
    }

    /* Handle general case [insert in middle or end]. */
    else
    {
        MamOS_taskControlBlockType* LOC_currentTask = a_ptr2queue->ptr2headTask;

        /* Find insertion point. */
        while(LOC_currentTask->ptr2nextTask != NULL_PTR)
        {
            if(MAMOS_GET_COMPARATOR_VALUE(LOC_currentTask->ptr2nextTask, a_comparator) > MAMOS_GET_COMPARATOR_VALUE(a_ptr2taskControlBlock, a_comparator))
            {
                a_ptr2taskControlBlock->ptr2nextTask = LOC_currentTask->ptr2nextTask;
                LOC_currentTask->ptr2nextTask = a_ptr2taskControlBlock;
                break;
            }

            else
            {
                LOC_currentTask = LOC_currentTask->ptr2nextTask;
            }
        }
        
        /* Insert at end if no suitable position found. */
        if(LOC_currentTask->ptr2nextTask == NULL_PTR)
        {
            a_ptr2taskControlBlock->ptr2nextTask = NULL_PTR;
            LOC_currentTask->ptr2nextTask = a_ptr2taskControlBlock;
        }
    }
}

/*=====================================================================================================================
 * [Function Name] : MamOS_removeFromQueue
 * [Description]   : Removes a specific task from a specific queue.
 * [Arguments]     : <a_ptr2queue>            -> Pointer to the required queue.
 *                   <a_ptr2taskControlBlock> -> Pointer to the task to be removed from the queue.
 * [return]        : The function returns void.
 ====================================================================================================================*/
static void MamOS_removeFromQueue(MamOS_QueueType* a_ptr2queue, MamOS_taskControlBlockType* a_ptr2taskControlBlock)
{
    /* Handle empty queue case. */
    if(a_ptr2queue->ptr2headTask == NULL_PTR)
    {
        /* Invalid Operation. */
    }

    /* Handle removing head case. */
    else if(a_ptr2queue->ptr2headTask == a_ptr2taskControlBlock)
    {
        a_ptr2queue->ptr2headTask = a_ptr2queue->ptr2headTask->ptr2nextTask;
        a_ptr2taskControlBlock->ptr2nextTask = NULL_PTR;
    }

    /* Handle removing from middle/end. */
    else
    {
        MamOS_taskControlBlockType* LOC_currentTask = a_ptr2queue->ptr2headTask;

        while(LOC_currentTask->ptr2nextTask != NULL_PTR)
        {
            if(LOC_currentTask->ptr2nextTask == a_ptr2taskControlBlock)
            {
                /* Remove task by updating links. */
                LOC_currentTask->ptr2nextTask = LOC_currentTask->ptr2nextTask->ptr2nextTask;
                a_ptr2taskControlBlock->ptr2nextTask = NULL_PTR;
                break;
            }

            else
            {
                LOC_currentTask = LOC_currentTask->ptr2nextTask;
            }
        }
    }
}
