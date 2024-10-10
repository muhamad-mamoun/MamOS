/*
=======================================================================================================================
Author       : Mamoun
Module       : Timer
File Name    : timer_prv.h
Date Created : Oct 6, 2024
Description  : Private file for the Timer module used in MamOS.
=======================================================================================================================
*/


#ifndef MAMOS_TIMER_INCLUDES_TIMER_PRV_H_
#define MAMOS_TIMER_INCLUDES_TIMER_PRV_H_

/*=====================================================================================================================
                                < Definitions and Static Configurations >
=====================================================================================================================*/

#define TIMER_MAX_TICKS                    (16777215UL)     /* The maximum number of ticks for timer.   */
#define TIMER_MILLIS_IN_SECOND             (1000.00)        /* The number milliseconds in one second.   */

/* Calculate the maximum time interval for timer according to the current frequency. */
#define TIMER_MAX_TIME_INTERVAL            ((TIMER_MAX_TICKS / MAMOS_CPU_CLOCK_FREQ) * TIMER_MILLIS_IN_SECOND)

/*=====================================================================================================================
                                       < User-defined Data Types >
=====================================================================================================================*/

typedef struct
{
    volatile uint32 CTRL;                    /* SysTick Control and Status Register. */
    volatile uint32 LOAD;                    /* SysTick Reload Value Register.       */
    volatile uint32 VAL;                     /* SysTick Current Value Register.      */
    volatile uint32 CALIB;                   /* SysTick Calibration Value Register.  */
}SYSTICK_registersType;

/*=====================================================================================================================
                                < Peripheral Registers and Bits Definitions >
=====================================================================================================================*/

/* SysTick registers base addresss. */
#define SYSTICK                              ((volatile SYSTICK_registersType*)0XE000E010)

/* SysTick bit definitions. */
#define SYSTICK_CTRL_ENABLE_BIT              (0)
#define SYSTICK_CTRL_TICKINT_BIT             (1)
#define SYSTICK_CTRL_CLKSOURCE_BIT           (2)
#define SYSTICK_CTRL_COUNTFLAG_BIT           (16)

/*=====================================================================================================================
                                         < Function-like Macros >
=====================================================================================================================*/

/* Macro used to calculate the total number of ticks needed for a specific time interval. */
#define TIMER_GET_TICKS_COUNT(INTERVAL) (((uint32)((INTERVAL / TIMER_MILLIS_IN_SECOND) * MAMOS_CPU_CLOCK_FREQ)) - 1)

#endif /* MAMOS_TIMER_INCLUDES_TIMER_PRV_H_ */
