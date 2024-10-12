/*
=======================================================================================================================
Author       : Mamoun
Module       : Mutex
File Name    : mutex_prv.h
Date Created : Oct 7, 2024
Description  : Private file for the MamOS Mutex module.
=======================================================================================================================
*/


#ifndef MAMOS_MUTEX_INCLUDES_MUTEX_PRV_H_
#define MAMOS_MUTEX_INCLUDES_MUTEX_PRV_H_

/*=====================================================================================================================
                                         < Functions Prototypes >
=====================================================================================================================*/

/*=====================================================================================================================
 * [Function Name] : 
 * [Description]   : 
 * [Arguments]     : <>      -> 
 *                   <>      -> 
 * [return]        : The function returns void.
 ====================================================================================================================*/
static void MamOS_addToWaitingQueue(MamOS_mutexHandle a_ptr2mutex, MamOS_taskControlBlockType* a_ptr2taskControlBlock);

/*=====================================================================================================================
 * [Function Name] : 
 * [Description]   : 
 * [Arguments]     : <>      -> 
 *                   <>      -> 
 * [return]        : The function returns void.
 ====================================================================================================================*/
static void MamOS_removeFromWaitingQueue(MamOS_mutexHandle a_ptr2mutex, MamOS_taskControlBlockType* a_ptr2taskControlBlock);

#endif /* MAMOS_MUTEX_INCLUDES_MUTEX_PRV_H_ */
