/*
=======================================================================================================================
Author       : Mamoun
Module       : Task
File Name    : task.h
Date Created : Oct 7, 2024
Description  : Interface file for the MamOS Task module.
=======================================================================================================================
*/


#ifndef MAMOS_TASK_INCLUDES_TASK_H_
#define MAMOS_TASK_INCLUDES_TASK_H_

/*=====================================================================================================================
                                         < Functions Prototypes >
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

#endif /* MAMOS_TASK_INCLUDES_TASK_H_ */
