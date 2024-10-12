/*
=======================================================================================================================
Author       : Mamoun
Module       : Scheduler
File Name    : scheduler.h
Date Created : Oct 8, 2024
Description  : Interface file for the MamOS Scheduler module.
=======================================================================================================================
*/


#ifndef MAMOS_SCHEDULER_INCLUDES_SCHEDULER_H_
#define MAMOS_SCHEDULER_INCLUDES_SCHEDULER_H_

/*=====================================================================================================================
                                         < Functions Prototypes >
=====================================================================================================================*/

/*=====================================================================================================================
 * [Function Name] : MamOS_schedulerTick
 * [Description]   : Called every system tick to update the blocked queue, and make a context switch
 *                   if the system is preemptive and there is a higher priority task.
 * [Arguments]     : The function Takes no arguments.
 * [return]        : The function returns void.
 ====================================================================================================================*/
void MamOS_schedulerTick(void);

/*=====================================================================================================================
 * [Function Name] : MamOS_forceTaskTransition
 * [Description]   : Initiates an immediate context switch.
 * [Arguments]     : The function Takes no arguments.
 * [return]        : The function returns void.
 ====================================================================================================================*/
void MamOS_forceTaskTransition(void);

#endif /* MAMOS_SCHEDULER_INCLUDES_SCHEDULER_H_ */
