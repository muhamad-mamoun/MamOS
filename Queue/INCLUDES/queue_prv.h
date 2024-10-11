/*
=======================================================================================================================
Author       : Mamoun
Module       : Queue
File Name    : queue_prv.h
Date Created : Oct 9, 2024
Description  : Private file for the MamOS Queue moduler.
=======================================================================================================================
*/


#ifndef MAMOS_QUEUE_INCLUDES_QUEUE_PRV_H_
#define MAMOS_QUEUE_INCLUDES_QUEUE_PRV_H_

/*=====================================================================================================================
                                < Definitions and Static Configurations >
=====================================================================================================================*/

#define MAMOS_PRIORITY_COMPARATOR_ID    (0U)                               /* Used for priority-based queue ordering */
#define MAMOS_DELAY_COMPARATOR_ID       (1U)                                  /* Used for delay-based queue ordering */

/*=====================================================================================================================
                                         < Function-like Macros >
=====================================================================================================================*/

/* Extracts the delay value from a specific task control block. */
#define MAMOS_GET_DELAY(TASK)                                                  ((*((uint32*)TASK + 1) & 0x0000FFFF))

/* Extracts the priority value from a specific task control block. */
#define MAMOS_GET_PRIORITY(TASK)                                              ((*((uint32*)TASK) & 0x0000FF00) >> 8)

/* Gets either priority or delay value based on comparator type. */
#define MAMOS_GET_COMPARATOR_VALUE(TASK, COMPARATOR) (COMPARATOR ? MAMOS_GET_DELAY(TASK) : MAMOS_GET_PRIORITY(TASK))

/*=====================================================================================================================
                                         < Functions Prototypes >
=====================================================================================================================*/

/*=====================================================================================================================
 * [Function Name] : MamOS_addToQueue
 * [Description]   : Adds a specific task to a specific queue.
 * [Arguments]     : <a_ptr2queue>            -> Pointer to the required queue.
 *                   <a_comparator>           -> Type of comparison when adding the task (priority or delay).
 *                   <a_ptr2taskControlBlock> -> Pointer to the task to be added to the queue.
 * [return]        : The function returns void.
 ====================================================================================================================*/
static void MamOS_addToQueue(MamOS_QueueType* a_ptr2queue, uint8 a_comparator, MamOS_taskControlBlockType* a_ptr2taskControlBlock);

/*=====================================================================================================================
 * [Function Name] : MamOS_removeFromQueue
 * [Description]   : Removes a specific task from a specific queue.
 * [Arguments]     : <a_ptr2queue>            -> Pointer to the required queue.
 *                   <a_ptr2taskControlBlock> -> Pointer to the task to be removed from the queue.
 * [return]        : The function returns void.
 ====================================================================================================================*/
static void MamOS_removeFromQueue(MamOS_QueueType* a_ptr2queue, MamOS_taskControlBlockType* a_ptr2taskControlBlock);

#endif /* MAMOS_QUEUE_INCLUDES_QUEUE_PRV_H_ */
