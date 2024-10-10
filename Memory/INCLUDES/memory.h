/*
=======================================================================================================================
Author       : Mamoun
Module       : Memory
File Name    : memory.h
Date Created : Oct 8, 2024
Description  : Interface file for the MamOS Memory module.
=======================================================================================================================
*/


#ifndef MAMOS_MEMORY_INCLUDES_MEMORY_H_
#define MAMOS_MEMORY_INCLUDES_MEMORY_H_

/*=====================================================================================================================
                                         < Functions Prototypes >
=====================================================================================================================*/

/*=====================================================================================================================
 * [Function Name] : MamOS_initMemory
 * [Description]   : Sets up the kernel stack by configuring the stack pointer to point to the kernel stack.
 * [Arguments]     : <a_ptr2kernelStackPointer>    -> Pointer to the kernel stack pointer that needs to be initialized.
 * [return]        : The function returns void.
 ====================================================================================================================*/
void MamOS_initMemory(uint32** a_ptr2kernelStackPointer);

#endif /* MAMOS_MEMORY_INCLUDES_MEMORY_H_ */
