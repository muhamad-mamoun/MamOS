/*
=======================================================================================================================
Author       : Mamoun
Module       : Common Macros
File Name    : common_macros.h
Date Created : Oct 14, 2023
Description  : The most common macros used in Embedded C.
=======================================================================================================================
*/


#ifndef COMMON_MACROS_H_
#define COMMON_MACROS_H_

/*=====================================================================================================================
                                         < Function-like Macros >
=====================================================================================================================*/

/* Set a specific register */
#define SET_REG(REG) (REG = ~(0))

/* Clear a specific register */
#define CLEAR_REG(REG) (REG = 0)

/* Toggle a specific register */
#define TOGGLE_REG(REG) (REG = (REG) ^ ~(0))

/* Set the MS 4-bits in a specific register */
#define SET_H_NIB(REG) (REG = (REG) | (0XF0))

/* Set the LS 4-bits in a specific register */
#define SET_L_NIB(REG) (REG = (REG) | (0X0F))

/* Clear the MS 4-bits in a specific register */
#define CLEAR_H_NIB(REG) (REG = (REG) & (0X0F))

/* Clear the LS 4-bits in a specific register */
#define CLEAR_L_NIB(REG) (REG = (REG) & (0XF0))

/* Get the value of the MS 4-bits in a specific register */
#define GET_H_NIB(REG) (((REG) >> (4)) & 0X0F)

/* Get the value of the LS 4-bits in a specific register */
#define GET_L_NIB(REG) ((REG) & (0X0F))

/* Set a certain bit in any register */
#define SET_BIT(REG,BIT) (REG = (REG) | (1 << BIT))

/* Clear a certain bit in any register */
#define CLEAR_BIT(REG,BIT) (REG = (REG) & (~(1 << BIT)))

/* Write a value [1 or 0] in a certain bit in any register */
#define WRITE_BIT(REG,BIT,VAL) (REG = ((REG & (~(1 << BIT))) | ((VAL & 0X01) << BIT)))

/* Toggle a certain bit in any register */
#define TOGGLE_BIT(REG,BIT) (REG = (REG) ^ (1 << BIT))

/* Check if a specific bit is set in any register and return non-zero if yes */
#define BIT_IS_SET(REG,BIT) ((REG) & (1 << BIT))

/* Check if a specific bit is cleared in any register and return one if yes */
#define BIT_IS_CLEAR(REG,BIT) (!((REG) & (1 << BIT)))

/* Get the value of a certain bit (1 or 0) in any register */
#define GET_BIT(REG,BIT) (((REG) & (1 << BIT)) >> BIT)

/* Shift right any register with a specific number of bits */
#define RSHIFT(REG,VAL) ((REG) >> (VAL))

/* Shift left any register with a specific number of bits */
#define LSHIFT(REG,VAL) ((REG) << (VAL))

/* Rotate right any register with a specific number of rotates */
#define ROTATE_R(REG,VAL) ((REG >> VAL) | (REG << ((sizeof(REG) * 8) - VAL)))

/* Rotate left any register with a specific number of rotates */
#define ROTATE_L(REG,VAL) ((REG << VAL) | (REG >> ((sizeof(REG) * 8) - VAL)))

/* Rotate right any register with any size of bits with a specific number of rotates */
#define ROTATE_R_ANY(REG,VAL,BITS) ((REG >> VAL) | (REG << (BITS - VAL)))

/* Rotate left any register with any size of bits with a specific number of rotates */
#define ROTATE_L_ANY(REG,VAL,BITS) ((REG << VAL) | (REG >> (BITS - VAL)))

/* Concatonate 8 bits with each other to create a 8-bit register value. */
#define CONCAT_8_BITS(BIT7,BIT6,BIT5,BIT4,BIT3,BIT2,BIT1,BIT0) CONCAT_8_HELPER(BIT7,BIT6,BIT5,BIT4,BIT3,BIT2,BIT1,BIT0)

/* Used in the CONCAT_8_BITS macro to prevent doing macros replacement before object replacement. */
#define CONCAT_8_HELPER(BIT7,BIT6,BIT5,BIT4,BIT3,BIT2,BIT1,BIT0) (0b##BIT7##BIT6##BIT5##BIT4##BIT3##BIT2##BIT1##BIT0)

/* Concatonate 16 bits with each other to create a 16-bit register value. */
#define CONCAT_16_BITS(BIT15,BIT14,BIT13,BIT12,BIT11,BIT10,BIT9,BIT8,BIT7,BIT6,BIT5,BIT4,BIT3,BIT2,BIT1,BIT0) CONCAT_16_HELPER(BIT15,BIT14,BIT13,BIT12,BIT11,BIT10,BIT9,BIT8,BIT7,BIT6,BIT5,BIT4,BIT3,BIT2,BIT1,BIT0)

/* Used in the CONCAT_16_BITS macro to prevent doing macros replacement before object replacement. */
#define CONCAT_16_HELPER(BIT15,BIT14,BIT13,BIT12,BIT11,BIT10,BIT9,BIT8,BIT7,BIT6,BIT5,BIT4,BIT3,BIT2,BIT1,BIT0) (0b##BIT15##BIT14##BIT13##BIT12##BIT11##BIT10##BIT9##BIT8##BIT7##BIT6##BIT5##BIT4##BIT3##BIT2##BIT1##BIT0)

/* Concatonate 32 bits with each other to create a 32-bit register value. */
#define CONCAT_32_BITS(BIT31,BIT30,BIT29,BIT28,BIT27,BIT26,BIT25,BIT24,BIT23,BIT22,BIT21,BIT20,BIT19,BIT18,BIT17,BIT16,BIT15,BIT14,BIT13,BIT12,BIT11,BIT10,BIT9,BIT8,BIT7,BIT6,BIT5,BIT4,BIT3,BIT2,BIT1,BIT0) CONCAT_32_HELPER(BIT31,BIT30,BIT29,BIT28,BIT27,BIT26,BIT25,BIT24,BIT23,BIT22,BIT21,BIT20,BIT19,BIT18,BIT17,BIT16,BIT15,BIT14,BIT13,BIT12,BIT11,BIT10,BIT9,BIT8,BIT7,BIT6,BIT5,BIT4,BIT3,BIT2,BIT1,BIT0)

/* Used in the CONCAT_32_BITS macro to prevent doing macros replacement before object replacement. */
#define CONCAT_32_HELPER(BIT31,BIT30,BIT29,BIT28,BIT27,BIT26,BIT25,BIT24,BIT23,BIT22,BIT21,BIT20,BIT19,BIT18,BIT17,BIT16,BIT15,BIT14,BIT13,BIT12,BIT11,BIT10,BIT9,BIT8,BIT7,BIT6,BIT5,BIT4,BIT3,BIT2,BIT1,BIT0) (0b##BIT31##BIT30##BIT29##BIT28##BIT27##BIT26##BIT25##BIT24##BIT23##BIT22##BIT21##BIT20##BIT19##BIT18##BIT17##BIT16##BIT15##BIT14##BIT13##BIT12##BIT11##BIT10##BIT9##BIT8##BIT7##BIT6##BIT5##BIT4##BIT3##BIT2##BIT1##BIT0)

#endif /* COMMON_MACROS_H_ */
