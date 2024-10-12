/*
=======================================================================================================================
Author       : Mamoun
Module       : Task
File Name    : task_prv.h
Date Created : Oct 7, 2024
Description  : Private file for the MamOS Task module.
=======================================================================================================================
*/


#ifndef MAMOS_TASK_INCLUDES_TASK_PRV_H_
#define MAMOS_TASK_INCLUDES_TASK_PRV_H_

/*=====================================================================================================================
                                         < Functions Prototypes >
=====================================================================================================================*/

/*=====================================================================================================================
 * [Function Name] : MamOS_initTaskStack
 * [Description]   : Sets up the initial stack frame for a task.
 * [Arguments]     : <a_ptr2taskEntryPoint>   -> Pointer to the task entry point.
 *                   <a_ptr2taskStackPointer> -> Pointer to the task stack pointer.
 * [return]        : The function returns void.
 ====================================================================================================================*/
static void MamOS_initTaskStack(void (*a_ptr2taskEntryPoint)(void), uint32** a_ptr2taskStackPointer);

#endif /* MAMOS_TASK_INCLUDES_TASK_PRV_H_ */
