/*
=======================================================================================================================
Author       : Mamoun
File Name    : MamOSConfig.h
Date Created : Oct 7, 2024
Description  : Configuration file for MamOS kernel.
=======================================================================================================================
*/


/*=====================================================================================================================
 * [Details]     : This file contains all the configurations for the MamOS to allow the user to customize the kernel.
 ====================================================================================================================*/

#ifndef MAMOS_CONFIG_H_
#define MAMOS_CONFIG_H_

/*=====================================================================================================================
                                < Definitions and Static Configurations >
=====================================================================================================================*/

#define MAMOS_SCHEDULER_TICK_TIME           (1U)         /* Time interval between scheduler ticks [in milliseconds]. */
#define MAMOS_MAX_NUM_OF_TASKS              (3U)       /* Maximum number of tasks that can be created in the system. */
#define MAMOS_MAX_STACK_SIZE                (80U)       /* Maximum stack size [in words] for any task in the system. */
#define MAMOS_PREEMPRIVE_SCHEDULER          (TRUE)                  /* Enables or disables the preemptive scheduler. */
#define MAMOS_CPU_CLOCK_FREQ                (16000000UL)                               /* CPU clock frequency in Hz. */

#endif /* MAMOS_CONFIG_H_ */
