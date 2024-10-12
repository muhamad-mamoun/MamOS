/*
=======================================================================================================================
Author       : Mamoun
Module       : Scheduler
File Name    : scheduler_prv.h
Date Created : Oct 8, 2024
Description  : Private file for the MamOS Scheduler module.
=======================================================================================================================
*/


#ifndef MAMOS_SCHEDULER_INCLUDES_SCHEDULER_PRV_H_
#define MAMOS_SCHEDULER_INCLUDES_SCHEDULER_PRV_H_

/*=====================================================================================================================
                                         < Functions Prototypes >
=====================================================================================================================*/

/*=====================================================================================================================
 * [Function Name] : MamOS_updateBlockedQueue
 * [Description]   : Updates the system tick counter and check if there are any expired delays.
 * [Arguments]     : The function Takes no arguments.
 * [return]        : The function returns void.
 ====================================================================================================================*/
static void MamOS_updateBlockedQueue(void);

#endif /* MAMOS_SCHEDULER_INCLUDES_SCHEDULER_PRV_H_ */
