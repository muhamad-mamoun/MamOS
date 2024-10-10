/*
=======================================================================================================================
Author       : Mamoun
Module       : Timer
File Name    : timer.h
Date Created : Oct 6, 2024
Description  : Interface file for the Timer module used in MamOS.
=======================================================================================================================
*/


#ifndef MAMOS_TIMER_INCLUDES_TIMER_H_
#define MAMOS_TIMER_INCLUDES_TIMER_H_

/*=====================================================================================================================
                                < Definitions and Static Configurations >
=====================================================================================================================*/

typedef enum
{
    TIMER_NO_ERRORS,          /* All Good.                                     */
    TIMER_NULL_PTR_ERROR,     /* Null Pointer Error.                           */
    TIMER_OVERFLOW_ERROR,     /* The time interval exceedes the timer limit.   */
}TIMER_errorStatusType;

/*=====================================================================================================================
                                         < Functions Prototypes >
=====================================================================================================================*/

/*=====================================================================================================================
 * [Function Name] : TIMER_setPeriodicInterval
 * [Description]   : Set a periodic non-blocking delay with a specific time interval.
 * [Arguments]     : <a_timeInterval>      -> Indicates to the required time interval value [in milliseconds].
 * [return]        : The function returns the error status: - No Errors.
 *                                                          - Busy Error.
 *                                                          - Overflow Error.
 ====================================================================================================================*/
TIMER_errorStatusType TIMER_setPeriodicInterval(uint16 a_timeInterval);

/*=====================================================================================================================
 * [Function Name] : TIMER_setCallBackFunction
 * [Description]   : Set the address of the call-back function.
 * [Arguments]     : <a_ptr2callBackFunction>      -> Pointer to the call-back function.
 * [return]        : The function returns the error status: - No Errors.
 *                                                          - Null Pointer Error.
 ====================================================================================================================*/
TIMER_errorStatusType TIMER_setCallBackFunction(void (*a_ptr2callBackFunction)(void));

#endif /* MAMOS_TIMER_INCLUDES_TIMER_H_ */
