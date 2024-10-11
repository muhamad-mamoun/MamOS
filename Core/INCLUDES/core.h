/*
=======================================================================================================================
Author       : Mamoun
Module       : Core
File Name    : core.h
Date Created : Oct 6, 2024
Description  : Interface file for the MamOS Core Module.
=======================================================================================================================
*/


#ifndef MAMOS_CORE_INCLUDES_CORE_H_
#define MAMOS_CORE_INCLUDES_CORE_H_

/*=====================================================================================================================
                                         < Functions Prototypes >
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

#endif /* MAMOS_CORE_INCLUDES_CORE_H_ */
