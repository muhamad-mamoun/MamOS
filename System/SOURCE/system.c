/*
=======================================================================================================================
Author       : Mamoun
Module       : System
File Name    : system.c
Date Created : Oct 6, 2024
Description  : Source file for the System module used in MamOS.
=======================================================================================================================
*/


/*=====================================================================================================================
 * [Details]     : This module provides low-level exception and interrupt management for MamOS RTOS.
 *                 It handles exception configuration, priority management, and system-level interrupts.
 ====================================================================================================================*/

/*=====================================================================================================================
                                               < Includes >
=====================================================================================================================*/

#include "../../Others/std_types.h"
#include "../../Others/common_macros.h"
#include "../INCLUDES/system_prv.h"
#include "../INCLUDES/system.h"

/*=====================================================================================================================
                                          < Functions Definitions >
=====================================================================================================================*/

/*=====================================================================================================================
 * [Function Name] : SYSTEM_setExceptionPriority
 * [Description]   : Set the priority value for a specific Exception.
 * [Arguments]     : <a_exceptionNumber>  -> Indicates to the required Exception.
 *                   <a_priority>         -> Indicates to the required priority.
 * [return]        : The function returns the error status: - No Errors.
 *                                                          - Exception Number Error.
 ====================================================================================================================*/
SYSTEM_errorStatusType SYSTEM_setExceptionPriority(SYSTEM_exceptionType a_exceptionNumber, uint8 a_priority)
{
    SYSTEM_errorStatusType LOC_errorStatus = SYSTEM_NO_ERRORS;

    if((a_exceptionNumber != SYSTEM_PENDSV_EXCEPTION) && (a_exceptionNumber != SYSTEM_SYSTICK_EXCEPTION))
    {
        LOC_errorStatus = SYSTEM_EXC_NUM_ERROR;
    }

    else
    {
        /* Set the priority value for the required exception. */
        if(a_exceptionNumber == SYSTEM_PENDSV_EXCEPTION) SCB->SHPR3 |= (a_priority << SCB_SHPR3_PENDSV_FIELD);
        else if(a_exceptionNumber == SYSTEM_SYSTICK_EXCEPTION) SCB->SHPR3 |= (a_priority << SCB_SHPR3_SYSTICK_FIELD);
    }

    return LOC_errorStatus;
}

/*=====================================================================================================================
 * [Function Name] : SYSTEM_getExceptionPriority
 * [Description]   : Get the priority value for a specific Exception.
 * [Arguments]     : <a_exceptionNumber>  -> Indicates to the required Exception.
 *                   <a_ptr2priority>     -> Pointer to a variable to store the exception priority.
 * [return]        : The function returns the error status: - No Errors.
 *                                                          - Null Pointer Error.
 *                                                          - Exception Number Error.
 ====================================================================================================================*/
SYSTEM_errorStatusType SYSTEM_getExceptionPriority(SYSTEM_exceptionType a_exceptionNumber, uint8* a_ptr2priority)
{
    SYSTEM_errorStatusType LOC_errorStatus = SYSTEM_NO_ERRORS;

    if(a_ptr2priority == NULL_PTR)
    {
        LOC_errorStatus = SYSTEM_NULL_PTR_ERROR;
    }

    else if((a_exceptionNumber != SYSTEM_PENDSV_EXCEPTION) && (a_exceptionNumber != SYSTEM_SYSTICK_EXCEPTION))
    {
        LOC_errorStatus = SYSTEM_EXC_NUM_ERROR;
    }

    else
    {
        /* Get the priority value for the required exception. */
        if(a_exceptionNumber == SYSTEM_PENDSV_EXCEPTION) *a_ptr2priority = ((SCB->SHPR3 >> SCB_SHPR3_PENDSV_FIELD) & 0X000000FF);
        else if(a_exceptionNumber == SYSTEM_SYSTICK_EXCEPTION) *a_ptr2priority = ((SCB->SHPR3 >> SCB_SHPR3_SYSTICK_FIELD) & 0X000000FF);
    }

    return LOC_errorStatus;
}

/*=====================================================================================================================
 * [Function Name] : SYSTEM_setExceptionPending
 * [Description]   : Set the pending status for a specific Exception.
 * [Arguments]     : <a_exceptionNumber>      -> Indicates to the required Exception.
 * [return]        : The function returns the error status: - No Errors.
 *                                                          - Exception Number Error.
 ====================================================================================================================*/
SYSTEM_errorStatusType SYSTEM_setExceptionPending(SYSTEM_exceptionType a_exceptionNumber)
{
    SYSTEM_errorStatusType LOC_errorStatus = SYSTEM_NO_ERRORS;

    if((a_exceptionNumber != SYSTEM_PENDSV_EXCEPTION) && (a_exceptionNumber != SYSTEM_SYSTICK_EXCEPTION))
    {
        LOC_errorStatus = SYSTEM_EXC_NUM_ERROR;
    }

    else
    {
        /* Set the pending status for the required exception. */
        if(a_exceptionNumber == SYSTEM_PENDSV_EXCEPTION) SET_BIT(SCB->ICSR, SCB_ICSR_PENDSVSET_BIT);
        else if(a_exceptionNumber == SYSTEM_SYSTICK_EXCEPTION) SET_BIT(SCB->ICSR, SCB_ICSR_PENDSTSET_BIT);
    }

    return LOC_errorStatus;
}

/*=====================================================================================================================
 * [Function Name] : SYSTEM_clearExceptionPending
 * [Description]   : Clear the pending status for a specific Exception.
 * [Arguments]     : <a_exceptionNumber>      -> Indicates to the required Exception.
 * [return]        : The function returns the error status: - No Errors.
 *                                                          - Exception Number Error.
 ====================================================================================================================*/
SYSTEM_errorStatusType SYSTEM_clearExceptionPending(SYSTEM_exceptionType a_exceptionNumber)
{
    SYSTEM_errorStatusType LOC_errorStatus = SYSTEM_NO_ERRORS;

    if((a_exceptionNumber != SYSTEM_PENDSV_EXCEPTION) && (a_exceptionNumber != SYSTEM_SYSTICK_EXCEPTION))
    {
        LOC_errorStatus = SYSTEM_EXC_NUM_ERROR;
    }

    else
    {
        /* Clear the pending status for the required exception. */
        if(a_exceptionNumber == SYSTEM_PENDSV_EXCEPTION) SET_BIT(SCB->ICSR, SCB_ICSR_PENDSVCLR_BIT);
        else if(a_exceptionNumber == SYSTEM_SYSTICK_EXCEPTION) SET_BIT(SCB->ICSR, SCB_ICSR_PENDSTCLR_BIT);
    }

    return LOC_errorStatus;
}
