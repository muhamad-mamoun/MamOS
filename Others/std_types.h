/*
=======================================================================================================================
Author       : Mamoun
Module       : Standard Types
File Name    : std_types.h
Date Created : Oct 14, 2023
Description  : The most common standard types used in Embedded C.
=======================================================================================================================
*/


#ifndef STD_TYPES_H_
#define STD_TYPES_H_

/*=====================================================================================================================
                                            < Definitions >
=====================================================================================================================*/

#ifndef NULL_PTR
#define NULL_PTR                   ((void*)(0))
#endif

#ifndef NULL_CHAR
#define NULL_CHAR                  ('\0')
#endif

#ifndef TRUE
#define TRUE                       (1U)
#endif

#ifndef FALSE
#define FALSE                      (0U)
#endif

#ifndef HIGH
#define HIGH                       (1U)
#endif

#ifndef LOW
#define LOW                        (0U)
#endif

/*=====================================================================================================================
                                       < User-defined Data Types >
=====================================================================================================================*/

typedef signed char                sint8;   /* Stores integer numbers with range: [-128 ~ 127].                      */
typedef unsigned char              uint8;   /* Stores integer numbers with range: [0 ~ 255].                         */
typedef signed short               sint16;  /* Stores integer numbers with range: [-32,768 ~ 32,767].                */
typedef unsigned short             uint16;  /* Stores integer numbers with range: [0 ~ 65535].                       */
typedef signed long                sint32;  /* Stores integer numbers with range: [-2,147,483,648 ~ -2,147,483,647]. */
typedef unsigned long              uint32;  /* Stores integer numbers with range: [0 ~ 4,294,967,295].               */
typedef signed long long           sint64;  /* Stores integer numbers.                                               */
typedef unsigned long long         uint64;  /* Stores integer numbers.                                               */
typedef float                      float32; /* Stores float numbers.                                                 */
typedef double                     float64; /* Stores float numbers.                                                 */

typedef struct
{
    uint8 bit0  : 1;
    uint8 bit1  : 1;
    uint8 bit2  : 1;
    uint8 bit3  : 1;
    uint8 bit4  : 1;
    uint8 bit5  : 1;
    uint8 bit6  : 1;
    uint8 bit7  : 1;
}ubit8;                                     /* Structure used for bit access [8-bit size].                           */

typedef union
{
    uint8 byte;                             /* Used for unsigned byte access.                                        */
    ubit8 bits;                             /* Used for unsigned bit access.                                         */
}uint8RegisterType;                         /* Union used to define 8-bit register with word and bit access.         */

typedef struct
{
    uint32 bit0  : 1;
    uint32 bit1  : 1;
    uint32 bit2  : 1;
    uint32 bit3  : 1;
    uint32 bit4  : 1;
    uint32 bit5  : 1;
    uint32 bit6  : 1;
    uint32 bit7  : 1;
    uint32 bit8  : 1;
    uint32 bit9  : 1;
    uint32 bit10 : 1;
    uint32 bit11 : 1;
    uint32 bit12 : 1;
    uint32 bit13 : 1;
    uint32 bit14 : 1;
    uint32 bit15 : 1;
    uint32 bit16 : 1;
    uint32 bit17 : 1;
    uint32 bit18 : 1;
    uint32 bit19 : 1;
    uint32 bit20 : 1;
    uint32 bit21 : 1;
    uint32 bit22 : 1;
    uint32 bit23 : 1;
    uint32 bit24 : 1;
    uint32 bit25 : 1;
    uint32 bit26 : 1;
    uint32 bit27 : 1;
    uint32 bit28 : 1;
    uint32 bit29 : 1;
    uint32 bit30 : 1;
    uint32 bit31 : 1;
}ubit32;                                    /* Structure used for bit access [32-bit size].                          */

typedef union
{
    uint32 word;                            /* Used for unsigned word access.                                        */
    ubit32 bits;                            /* Used for unsigned bit access.                                         */
}uint32RegisterType;                        /* Union used to define 32-bit register with word and bit access.        */

#endif /* STD_TYPES_H_ */
