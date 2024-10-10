/*
=======================================================================================================================
Author       : Mamoun
Module       : System
File Name    : system.h
Date Created : Oct 6, 2024
Description  : Interface file for the System module used in MamOS.
=======================================================================================================================
*/


#ifndef MAMOS_SYSTEM_INCLUDES_SYSTEM_H_
#define MAMOS_SYSTEM_INCLUDES_SYSTEM_H_

/*=====================================================================================================================
                                       < User-defined Data Types >
=====================================================================================================================*/

typedef enum
{
    SYSTEM_NO_ERRORS,                   /* All Good.                       */
    SYSTEM_EXC_NUM_ERROR,               /* Invalid Exception Number Error. */
    SYSTEM_NULL_PTR_ERROR,              /* Null Pointer Error.             */
}SYSTEM_errorStatusType;

typedef enum
{
    SYSTEM_PENDSV_EXCEPTION,            /* PendSV Exception.               */
    SYSTEM_SYSTICK_EXCEPTION,           /* SysTick Exception.              */
}SYSTEM_exceptionType;

/*=====================================================================================================================
                                         < Functions Prototypes >
=====================================================================================================================*/

/*=====================================================================================================================
 * [Function Name] : SYSTEM_setExceptionPriority
 * [Description]   : Set the priority value for a specific Exception.
 * [Arguments]     : <a_exceptionNumber>  -> Indicates to the required Exception.
 *                   <a_priority>         -> Indicates to the required priority.
 * [return]        : The function returns the error status: - No Errors.
 *                                                          - Exception Number Error.
 ====================================================================================================================*/
SYSTEM_errorStatusType SYSTEM_setExceptionPriority(SYSTEM_exceptionType a_exceptionNumber, uint8 a_priority);

/*=====================================================================================================================
 * [Function Name] : SYSTEM_getExceptionPriority
 * [Description]   : Get the priority value for a specific Exception.
 * [Arguments]     : <a_exceptionNumber>  -> Indicates to the required Exception.
 *                   <a_ptr2priority>     -> Pointer to a variable to store the exception priority.
 * [return]        : The function returns the error status: - No Errors.
 *                                                          - Null Pointer Error.
 *                                                          - Exception Number Error.
 ====================================================================================================================*/
SYSTEM_errorStatusType SYSTEM_getExceptionPriority(SYSTEM_exceptionType a_exceptionNumber, uint8* a_ptr2priority);

/*=====================================================================================================================
 * [Function Name] : SYSTEM_setExceptionPending
 * [Description]   : Set the pending status for a specific Exception.
 * [Arguments]     : <a_exceptionNumber>      -> Indicates to the required Exception.
 * [return]        : The function returns the error status: - No Errors.
 *                                                          - Exception Number Error.
 ====================================================================================================================*/
SYSTEM_errorStatusType SYSTEM_setExceptionPending(SYSTEM_exceptionType a_exceptionNumber);

/*=====================================================================================================================
 * [Function Name] : SYSTEM_clearExceptionPending
 * [Description]   : Clear the pending status for a specific Exception.
 * [Arguments]     : <a_exceptionNumber>      -> Indicates to the required Exception.
 * [return]        : The function returns the error status: - No Errors.
 *                                                          - Exception Number Error.
 ====================================================================================================================*/
SYSTEM_errorStatusType SYSTEM_clearExceptionPending(SYSTEM_exceptionType a_exceptionNumber);

#endif /* MAMOS_SYSTEM_INCLUDES_SYSTEM_H_ */
