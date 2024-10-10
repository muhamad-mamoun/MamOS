/*
=======================================================================================================================
Author       : Mamoun
Module       : Timer
File Name    : timer.c
Date Created : Oct 6, 2024
Description  : Source file for the Timer module used in MamOS.
=======================================================================================================================
*/


/*=====================================================================================================================
 * [Details]     : This module handles all timing and scheduling-related operations in MamOS.
 ====================================================================================================================*/

/*=====================================================================================================================
                                               < Includes >
=====================================================================================================================*/

#include "../../MamOSConfig.h"
#include "../../Others/std_types.h"
#include "../../Others/common_macros.h"
#include "../INCLUDES/timer_prv.h"
#include "../INCLUDES/timer.h"

/*=====================================================================================================================
                                           < Global Variables >
=====================================================================================================================*/

static void (*G_ptr2callBackFunction)(void) = NULL_PTR;                  /* Pointer to the call-back function. */

/*=====================================================================================================================
                                          < Functions Definitions >
=====================================================================================================================*/

/*=====================================================================================================================
 * [Function Name] : TIMER_setPeriodicInterval
 * [Description]   : Set a periodic non-blocking delay with a specific time interval.
 * [Arguments]     : <a_timeInterval>      -> Indicates to the required time interval value [in milliseconds].
 * [return]        : The function returns the error status: - No Errors.
 *                                                          - Busy Error.
 *                                                          - Overflow Error.
 ====================================================================================================================*/
TIMER_errorStatusType TIMER_setPeriodicInterval(uint16 a_timeInterval)
{
    TIMER_errorStatusType LOC_errorStatus = TIMER_NO_ERRORS;

    if(a_timeInterval > TIMER_MAX_TIME_INTERVAL)
    {
        LOC_errorStatus = TIMER_OVERFLOW_ERROR;
    }

    else
    {
        SET_BIT(SYSTICK->CTRL,SYSTICK_CTRL_CLKSOURCE_BIT);           /* Set SysTick clock as the CPU clock.    */
        SYSTICK->LOAD = TIMER_GET_TICKS_COUNT(a_timeInterval);       /* Calculate and Set the number of ticks. */
        SYSTICK->VAL = 0;                                            /* Reset the Current Value Register.      */
        SET_BIT(SYSTICK->CTRL,SYSTICK_CTRL_TICKINT_BIT);             /* Enable SysTick interrupt.              */
        SET_BIT(SYSTICK->CTRL,SYSTICK_CTRL_ENABLE_BIT);              /* Enable SysTick counter.                */
    }

    return LOC_errorStatus;
}

/*=====================================================================================================================
 * [Function Name] : TIMER_setCallBackFunction
 * [Description]   : Set the address of the call-back function.
 * [Arguments]     : <a_ptr2callBackFunction>      -> Pointer to the call-back function.
 * [return]        : The function returns the error status: - No Errors.
 *                                                          - Null Pointer Error.
 ====================================================================================================================*/
TIMER_errorStatusType TIMER_setCallBackFunction(void (*a_ptr2callBackFunction)(void))
{
    TIMER_errorStatusType LOC_errorStatus = TIMER_NO_ERRORS;

    if(a_ptr2callBackFunction == NULL_PTR)
    {
        LOC_errorStatus = TIMER_NULL_PTR_ERROR;
    }

    else
    {
        /* Store the address of the call-back function in the global variable. */
        G_ptr2callBackFunction = a_ptr2callBackFunction;
    }

    return LOC_errorStatus;
}

/*=====================================================================================================================
 * [Function Name] : SysTick_Handler
 * [Description]   : The interrupt service routine for SysTick .
 * [Arguments]     : The function Takes no arguments.
 * [return]        : The function returns void.
 ====================================================================================================================*/
void SysTick_Handler(void)
{
    if(G_ptr2callBackFunction != NULL_PTR)
    {
        G_ptr2callBackFunction();                                              /* Call the call-back function. */
    }
}
