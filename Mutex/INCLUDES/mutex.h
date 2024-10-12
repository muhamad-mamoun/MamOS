/*
=======================================================================================================================
Author       : Mamoun
Module       : Mutex
File Name    : mutex.h
Date Created : Oct 7, 2024
Description  : Interface file for the MamOS Mutex module.
=======================================================================================================================
*/


#ifndef MAMOS_MUTEX_INCLUDES_MUTEX_H_
#define MAMOS_MUTEX_INCLUDES_MUTEX_H_

/*=====================================================================================================================
                                         < Functions Prototypes >
=====================================================================================================================*/

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

#endif /* MAMOS_MUTEX_INCLUDES_MUTEX_H_ */
