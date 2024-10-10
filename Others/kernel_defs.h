/*
=======================================================================================================================
Author       : Mamoun
Module       : Kernel Definitions
File Name    : kernel_defs.h
Date Created : Oct 7, 2024
Description  : Private definitions for the MamOS kernel.
=======================================================================================================================
*/


/*=====================================================================================================================
 * [Details]     : This header file defines the core data structures and configurations used throughout MamOS.
 *                 It includes task management structures, synchronization primitives, and kernel control mechanisms.
 ====================================================================================================================*/

#ifndef MAMOS_OTHERS_KERNEL_DEFS_H_
#define MAMOS_OTHERS_KERNEL_DEFS_H_

/*=====================================================================================================================
                                               < Includes >
=====================================================================================================================*/

#include "std_types.h"
#include "../MamOSConfig.h"

/*=====================================================================================================================
                                < Definitions and Static Configurations >
=====================================================================================================================*/

#define MAMOS_IDLE_TASK_ID                    (0U)                    /* Reserved ID for the idle task.              */
#define MAMOS_MIN_STACK_SIZE                  (20U)                   /* Minimum allowed stack size [in words].      */
#define MAMOS_MAX_NUM_OF_MUTEX                (10U)                   /* Maximum number of mutex allowed the system. */

/* Total number of tasks in the system including idle task. */
#define MAMOS_TOTAL_NUM_OF_TASKS              (MAMOS_MAX_NUM_OF_TASKS + 1)

/* Total kernel stack size. */
#define MAMOS_KERNEL_STACK_SIZE               ((MAMOS_MAX_NUM_OF_TASKS * MAMOS_MAX_STACK_SIZE) + MAMOS_MIN_STACK_SIZE)

/*=====================================================================================================================
                                       < User-defined Data Types >
=====================================================================================================================*/

typedef enum
{
    MAMOS_READY_TASK,                                                      /* Task is available for scheduling.      */
    MAMOS_ACTIVE_TASK,                                                     /* Task is currently running.             */
    MAMOS_BLOCKED_TASK,                                                    /* Task is blocked on delay.              */
    MAMOS_WAITING_TASK,                                                    /* Task is waiting for a shared resource. */
    MAMOS_SUSPENDED_TASK,                                                  /* Task is suspended from scheduling.     */
}MamOS_taskStateType;

typedef enum
{
    MAMOS_MUTEX_UNLOCKED,                                                     /* Mutex is available for acquisition. */
    MAMOS_MUTEX_LOCKED,                                                       /* Mutex is currently held by a task.  */
}MamOS_mutexStateType;

struct TaskControlBlock
{
    uint8 id;                                                         /* Unique task identifier.                     */
    uint8 priority;                                                   /* Task scheduling priority.                   */
    uint16 periodicity;                                               /* Period for periodic tasks [in ticks].       */
    uint16 delayTicks;                                                /* Period for blocked tasks [in ticks].        */
    uint16 stackSize;                                                 /* Size of the task stack [in words].          */
    uint32* stackPointer;                                             /* Current position of the task stack pointer. */
    MamOS_taskStateType state;                                        /* Current task state.                         */
    void (*ptr2entryPoint)(void);                                     /* Task main function entry point.             */
    struct TaskControlBlock* ptr2nextTask;                            /* Next TCB in the queue.                      */
};

typedef struct TaskControlBlock MamOS_taskControlBlockType;

typedef struct
{
    uint8 queueSize;                                                          /* Current number of tasks in queue.   */
    MamOS_taskControlBlockType* ptr2headTask;                                 /* The first task in queue.            */
    MamOS_taskControlBlockType* ptr2rearTask;                                 /* The last task in queue.             */
}MamOS_QueueType;

typedef struct mutex
{
    MamOS_taskControlBlockType* ptr2ownerTask;              /* The task that currently holding the mutex.            */
    MamOS_mutexStateType mutexState;                        /* Current mutex state.                                  */
    MamOS_QueueType waitingQueue;                           /* Queue of tasks that waiting for the mutex.            */
}MamOS_mutexType;

typedef struct mutex* MamOS_mutexHandle;

typedef struct
{
    uint8 taskCounter;                                              /* Current number of tasks in the system.        */
    uint32* kernelStackPointer;                                     /* Current position of the kernel stack pointer. */
    MamOS_taskControlBlockType* ptr2activeTask;                     /* The currently executing task.                 */
    MamOS_taskControlBlockType* ptr2standbyTask;                    /* The next task selected to run.                */
    MamOS_QueueType blockedQueue;                                   /* Queue of the blocked tasks.                   */
    MamOS_QueueType readyQueue;                                     /* Queue of the ready tasks.                     */
    uint8 blockEmptyFlag;                                           /* Flag indicates if blocked queue is empty.     */
    uint64 ticksCounter;                                            /* System tick counter.                          */
    uint8 mutexCounter;                                             /* Current number of created mutex.              */
}MamOS_kernelControlPanelType;

/*=====================================================================================================================
                                         < Function-like Macros >
=====================================================================================================================*/

/* Macro to generate an SVC instruction to request an immediate task context switch. */
#define MAMOS_TASK_TRANS_REQUEST()            __asm__ volatile ("SVC %[immediate]" :: [immediate] "I" (MAMOS_TASK_TRANS_REQUEST_SVC));

#endif /* MAMOS_OTHERS_KERNEL_DEFS_H_ */
