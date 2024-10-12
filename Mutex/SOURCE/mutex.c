/*
=======================================================================================================================
Author       : Mamoun
Module       : Mutex
File Name    : mutex.c
Date Created : Oct 7, 2024
Description  : Source file for the MamOS Mutex module.
=======================================================================================================================
*/


/*=====================================================================================================================
 * [Details]     : This module hosts the functionality of the MamOS Mutex system, including mutex creation,
 *                 acquisition, and release operations. Mutexes are used for task synchronization
 *                 and protecting shared resources in the MamOS.
 * [Future Work] : Support priority inheritance to solve the priority inversion problem.
 ====================================================================================================================*/

/*=====================================================================================================================
                                               < Includes >
=====================================================================================================================*/

#include "../../Others/std_types.h"
#include "../../Others/kernel_defs.h"
#include "../../Queue/INCLUDES/queue.h"
#include "../INCLUDES/mutex_prv.h"
#include "../INCLUDES/mutex.h"

/*=====================================================================================================================
                                           < Global Variables >
=====================================================================================================================*/

/* Array of mutex that available in the system. */
volatile MamOS_mutexType G_mutexHeap[MAMOS_MAX_NUM_OF_MUTEX] = {0};

/* Extern the Kernel Control Panel. */
extern MamOS_kernelControlPanelType G_kernelControlPanel;

/*=====================================================================================================================
                                          < Functions Definitions >
=====================================================================================================================*/

/*=====================================================================================================================
 * [Function Name] : MamOS_createMutex
 * [Description]   : reates a new mutex in the MamOS.
 * [Arguments]     : The function Takes no arguments.
 * [return]        : The function returns the handle to the created mutex [or Null Pointer if creation fails].
 ====================================================================================================================*/
MamOS_mutexHandle MamOS_createMutex(void)
{
    MamOS_mutexHandle LOC_createdMutexHandle = NULL_PTR;

    if(G_kernelControlPanel.mutexCounter < MAMOS_MAX_NUM_OF_MUTEX)
    {
        /* Get the handle of the created mutex and increment the mutex counter. */
        LOC_createdMutexHandle = &G_mutexHeap[G_kernelControlPanel.mutexCounter];
        G_kernelControlPanel.mutexCounter++;

        /* Initialize the new mutex. */
        LOC_createdMutexHandle->waitingQueue.ptr2headTask = NULL_PTR;
        LOC_createdMutexHandle->waitingQueue.ptr2rearTask = NULL_PTR;
        LOC_createdMutexHandle->mutexState = MAMOS_MUTEX_UNLOCKED;
        LOC_createdMutexHandle->ptr2ownerTask = NULL_PTR;
    }

    else
    {
        /* Invalid Operation. */
    }

    return LOC_createdMutexHandle;
}

/*=====================================================================================================================
 * [Function Name] : MamOS_acquireMutex
 * [Description]   : Handles the acquisition of a specific mutex.
 * [Arguments]     : <a_ptr2mutex>      -> Pointer to the mutex to be acquired.
 * [return]        : The function returns void.
 ====================================================================================================================*/
void MamOS_acquireMutex(MamOS_mutexHandle a_ptr2mutex)
{
    /* check if the mutex is available or locked by another task. */
    if(a_ptr2mutex->mutexState == MAMOS_MUTEX_UNLOCKED)
    {
        /* If available, Lock it and change the ownership of the mutex the calling task. */
        a_ptr2mutex->ptr2ownerTask = G_kernelControlPanel.ptr2activeTask;
        a_ptr2mutex->mutexState = MAMOS_MUTEX_LOCKED;
    }

    else
    {
        /* If locked, Add the current task to this mutex waiting queue and request a context switch. */
        MamOS_addToWaitingQueue(a_ptr2mutex, G_kernelControlPanel.ptr2activeTask);
        MAMOS_TASK_TRANS_REQUEST();
    }
}

/*=====================================================================================================================
 * [Function Name] : MamOS_releaseMutex
 * [Description]   : Handles the release operation of a specific mutex.
 * [Arguments]     : <a_ptr2mutex>      -> Pointer to the mutex to be released.
 * [return]        : The function returns void.
 ====================================================================================================================*/
void MamOS_releaseMutex(MamOS_mutexHandle a_ptr2mutex)
{
    /* Check if the calling task is the owner of the mutex or not. */
    if(a_ptr2mutex->ptr2ownerTask == G_kernelControlPanel.ptr2activeTask)
    {
        /* Fetch the highest priority task in the mutex waiting queue and make it the owner. */
        a_ptr2mutex->ptr2ownerTask = a_ptr2mutex->waitingQueue.ptr2headTask;

        if(a_ptr2mutex->ptr2ownerTask != NULL_PTR)
        {
            MamOS_removeFromWaitingQueue(a_ptr2mutex, a_ptr2mutex->ptr2ownerTask);
            MamOS_addToReadyQueue(a_ptr2mutex->ptr2ownerTask);
        }

        else
        {
            /* If there is no tasks in the mutex waiting queue, Unlock the mutex. */
            a_ptr2mutex->mutexState = MAMOS_MUTEX_UNLOCKED;
        }
    }

    else
    {
        /* Invalid Operation. */
    }
}
