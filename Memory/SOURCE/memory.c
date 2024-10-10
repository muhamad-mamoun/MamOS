/*
=======================================================================================================================
Author       : Mamoun
Module       : Memory
File Name    : memory.c
Date Created : Oct 8, 2024
Description  : Source file for the MamOS Memory module.
=======================================================================================================================
*/


/*=====================================================================================================================
 * [Details]     : This module handles memory management operations in MamOS RTOS,
 *                 including kernel stack initialization and memory space allocation.
 * [Future Work] : Support memory protection to prevent any task from overwriting the memory space of another.
 ====================================================================================================================*/

/*=====================================================================================================================
                                               < Includes >
=====================================================================================================================*/

#include "../../Others/std_types.h"
#include "../../Others/kernel_defs.h"
#include "../INCLUDES/memory_prv.h"
#include "../INCLUDES/memory.h"

/*=====================================================================================================================
                                           < Global Variables >
=====================================================================================================================*/

/* Static array that serves as the kernel's dedicated stack space. */
volatile static uint32 G_kernelStack[MAMOS_KERNEL_STACK_SIZE] = {0};

/*=====================================================================================================================
                                          < Functions Definitions >
=====================================================================================================================*/

/*=====================================================================================================================
 * [Function Name] : MamOS_initMemory
 * [Description]   : Sets up the kernel stack by configuring the stack pointer to point to the kernel stack.
 * [Arguments]     : <a_ptr2kernelStackPointer>    -> Pointer to the kernel stack pointer that needs to be initialized.
 * [return]        : The function returns void.
 ====================================================================================================================*/
void MamOS_initMemory(uint32** a_ptr2kernelStackPointer)
{
    *a_ptr2kernelStackPointer = G_kernelStack + MAMOS_KERNEL_STACK_SIZE;
}
