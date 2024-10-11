/*
=======================================================================================================================
Author       : Mamoun
Module       : Queue
File Name    : queue.h
Date Created : Oct 9, 2024
Description  : Interface file for the MamOS Queue moduler.
=======================================================================================================================
*/


#ifndef MAMOS_QUEUE_INCLUDES_QUEUE_H_
#define MAMOS_QUEUE_INCLUDES_QUEUE_H_

/*=====================================================================================================================
                                         < Functions Prototypes >
=====================================================================================================================*/

/*=====================================================================================================================
 * [Function Name] : MamOS_addToReadyQueue
 * [Description]   : Adds a specific task to the ready queue and change its state.
 * [Arguments]     : <a_ptr2taskControlBlock>    -> Pointer to the task to be added to the ready queue.
 * [return]        : The function returns void.
 ====================================================================================================================*/
void MamOS_addToReadyQueue(MamOS_taskControlBlockType* a_ptr2taskControlBlock);

/*=====================================================================================================================
 * [Function Name] : MamOS_removeFromReadyQueue
 * [Description]   : Removes a specific task from the ready queue.
 * [Arguments]     : <a_ptr2taskControlBlock>    -> Pointer to the task to be removed from the ready queue.
 * [return]        : The function returns void.
 ====================================================================================================================*/
void MamOS_removeFromReadyQueue(MamOS_taskControlBlockType* a_ptr2taskControlBlock);

/*=====================================================================================================================
 * [Function Name] : MamOS_addToBlockedQueue
 * [Description]   : Adds a specific task to the blocked queue and change its state.
 * [Arguments]     : <a_ptr2taskControlBlock>    -> Pointer to the task to be added to the blocked queue.
 * [return]        : The function returns void.
 ====================================================================================================================*/
void MamOS_addToBlockedQueue(MamOS_taskControlBlockType* a_ptr2taskControlBlock);

/*=====================================================================================================================
 * [Function Name] : MamOS_removeFromBlockedQueue
 * [Description]   : Removes a specific task from the blocked queue.
 * [Arguments]     : <a_ptr2taskControlBlock>    -> Pointer to the task to be removed from the blocked queue.
 * [return]        : The function returns void.
 ====================================================================================================================*/
void MamOS_removeFromBlockedQueue(MamOS_taskControlBlockType* a_ptr2taskControlBlock);

/*=====================================================================================================================
 * [Function Name] : MamOS_addToWaitingQueue
 * [Description]   : Adds a specific task to the waiting queue of a specific mutex and change its state.
 * [Arguments]     : <a_ptr2mutex>            -> Pointer to the mutex.
 *                   <a_ptr2taskControlBlock> -> Pointer to the task to be added to the waiting queue.
 * [return]        : The function returns void.
 ====================================================================================================================*/
void MamOS_addToWaitingQueue(MamOS_mutexHandle a_ptr2mutex, MamOS_taskControlBlockType* a_ptr2taskControlBlock);

/*=====================================================================================================================
 * [Function Name] : MamOS_removeFromWaitingQueue
 * [Description]   : Removes a specific task from the waiting queue of a specific mutex.
 * [Arguments]     : <a_ptr2mutex>            -> Pointer to the mutex.
 *                   <a_ptr2taskControlBlock> -> Pointer to the task to be removed from the waiting queue.
 * [return]        : The function returns void.
 ====================================================================================================================*/
void MamOS_removeFromWaitingQueue(MamOS_mutexHandle a_ptr2mutex, MamOS_taskControlBlockType* a_ptr2taskControlBlock);

#endif /* MAMOS_QUEUE_INCLUDES_QUEUE_H_ */
