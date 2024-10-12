/*
=======================================================================================================================
Author       : Mamoun
File Name    : MamOS.h
Date Created : Oct 12, 2024
Description  : Interface file for all MamOS public APIs.
=======================================================================================================================
*/


#ifndef MAMOS_MAMOS_H_
#define MAMOS_MAMOS_H_

/*=====================================================================================================================
                                               < Includes >
=====================================================================================================================*/

#include "Others/std_types.h"

/*=====================================================================================================================
                                       < User-defined Data Types >
=====================================================================================================================*/

typedef struct mutex* MamOS_mutexHandle;

/*=====================================================================================================================
                                      < Public Functions Prototypes >
=====================================================================================================================*/

/*=====================================================================================================================
 * [Function Name] : MamOS_init
 * [Description]   : Initializes the MamOS kernel and its core components.
 * [Arguments]     : The function Takes no arguments.
 * [return]        : The function returns void.
 ====================================================================================================================*/
void MamOS_init(void);

/*=====================================================================================================================
 * [Function Name] : MamOS_launch
 * [Description]   : Launches the MamOS kernel and starts the first task execution.
 * [Arguments]     : The function Takes no arguments.
 * [return]        : The function returns void.
 ====================================================================================================================*/
void MamOS_launch(void);

/*=====================================================================================================================
 * [Function Name] : MamOS_createTask
 * [Description]   : Creates a new task, sets up its stack, and adds it to the ready queue.
 * [Arguments]     : <a_ptr2taskEntryPoint> -> Pointer to the task entry point.
 *                   <a_taskStackSize>      -> Indicates to the task stack size [in words].
 *                   <a_priority>           -> Indicates to the task priority [0 ~ 255].
 *                   <a_periodicity>        -> Indicates to the periodic task periodicity [in system ticks].
 * [return]        : The function returns void.
 ====================================================================================================================*/
void MamOS_createTask(void (*a_ptr2taskEntryPoint)(void), uint16 a_taskStackSize, uint8 a_priority, uint16 a_periodicity);

/*=====================================================================================================================
 * [Function Name] : MamOS_suspendTask
 * [Description]   : Suspends a specified task from scheduling.
 * [Arguments]     : <a_ptr2taskEntryPoint> -> Indicates to the required task to be suspended.
 * [return]        : The function returns void.
 ====================================================================================================================*/
void MamOS_suspendTask(void (*a_ptr2taskEntryPoint)(void));

/*=====================================================================================================================
 * [Function Name] : MamOS_resumeTask
 * [Description]   : Resumes a suspended task.
 * [Arguments]     : <a_ptr2taskEntryPoint> -> Indicates to the required task to be resumed.
 * [return]        : The function returns void.
 ====================================================================================================================*/
void MamOS_resumeTask(void (*a_ptr2taskEntryPoint)(void));

/*=====================================================================================================================
 * [Function Name] : MamOS_taskDelay
 * [Description]   : Delays the current task for a specified number of ticks.
 * [Arguments]     : <a_delayTicks> -> Indicates to the number of ticks to delay the task.
 * [return]        : The function returns void.
 ====================================================================================================================*/
void MamOS_taskDelay(uint16 a_delayTicks);

/*=====================================================================================================================
 * [Function Name] : MamOS_taskYield
 * [Description]   : Yields the current task after finishing its function allowing other tasks to run.
 * [Arguments]     : The function Takes no arguments.
 * [return]        : The function returns void.
 ====================================================================================================================*/
void MamOS_taskYield(void);

/*=====================================================================================================================
 * [Function Name] : MamOS_createMutex
 * [Description]   : reates a new mutex in the MamOS.
 * [Arguments]     : The function Takes no arguments.
 * [return]        : The function returns the handle to the created mutex [or Null Pointer if creation fails].
 ====================================================================================================================*/
MamOS_mutexHandle MamOS_createMutex(void);

/*=====================================================================================================================
 * [Function Name] : MamOS_acquireMutex
 * [Description]   : Handles the acquisition of a specific mutex.
 * [Arguments]     : <a_ptr2mutex>      -> Pointer to the mutex to be acquired.
 * [return]        : The function returns void.
 ====================================================================================================================*/
void MamOS_acquireMutex(MamOS_mutexHandle a_ptr2mutex);

/*=====================================================================================================================
 * [Function Name] : MamOS_releaseMutex
 * [Description]   : Handles the release operation of a specific mutex.
 * [Arguments]     : <a_ptr2mutex>      -> Pointer to the mutex to be released.
 * [return]        : The function returns void.
 ====================================================================================================================*/
void MamOS_releaseMutex(MamOS_mutexHandle a_ptr2mutex);

#endif /* MAMOS_MAMOS_H_ */
