/*
=======================================================================================================================
Author       : Mamoun
Module       : System
File Name    : system_prv.h
Date Created : Oct 6, 2024
Description  : Private file for the System module used in MamOS.
=======================================================================================================================
*/


#ifndef MAMOS_SYSTEM_INCLUDES_SYSTEM_PRV_H_
#define MAMOS_SYSTEM_INCLUDES_SYSTEM_PRV_H_

/*=====================================================================================================================
                                < Definitions and Static Configurations >
=====================================================================================================================*/

#define SCB_AIRCR_WRITE_VECTKEY                     (0X05FAUL)     /* The key value to write in AIRCR register. */

/*=====================================================================================================================
                                       < User-defined Data Types >
=====================================================================================================================*/

typedef struct
{
    volatile uint32 CPUID;     /* CPUID Base Register.                              */
    volatile uint32 ICSR;      /* Interrupt Control and State Register.             */
    volatile uint32 VTOR;      /* Vector Table Offset Register.                     */
    volatile uint32 AIRCR;     /* Application Interrupt and Reset Control Register. */
    volatile uint32 SCR;       /* System Control Register.                          */
    volatile uint32 CCR;       /* Configuration and Control Register.               */
    volatile uint32 SHPR1;     /* System Handler Priority Register 1.               */
    volatile uint32 SHPR2;     /* System Handler Priority Register 2.               */
    volatile uint32 SHPR3;     /* System Handler Priority Register 3.               */
    volatile uint32 SHCRS;     /* System Handler Control and State Register.        */
    volatile uint32 CFSR;      /* Configurable Fault Status Register.               */
}SCB_registersType;

/*=====================================================================================================================
                                < Peripheral Registers and Bits Definitions >
=====================================================================================================================*/

/* The System Control Block (SCB) peripheral registers base addresss. */
#define SCB                    ((volatile SCB_registersType*)0XE000ED00)

#define SCB_SHPR3_PENDSV_FIELD                      (16UL)     /* PendSV Priority field base bit number.   */
#define SCB_SHPR3_SYSTICK_FIELD                     (24UL)     /* SysTick Priority field base bit number.  */

#define SCB_ICSR_PENDSTCLR_BIT                      (25UL)     /* SysTick Clear Pending bit number.        */
#define SCB_ICSR_PENDSTSET_BIT                      (26UL)     /* SysTick Set Pending bit number.          */
#define SCB_ICSR_PENDSVCLR_BIT                      (27UL)     /* PendSV Clear Pending bit number.         */
#define SCB_ICSR_PENDSVSET_BIT                      (28UL)     /* PendSV Set Pending bit number.           */

#endif /* MAMOS_SYSTEM_INCLUDES_SYSTEM_PRV_H_ */
