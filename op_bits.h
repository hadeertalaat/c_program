/**********************************************************/
//
/**********************************************************/

/*
	This module offers to act or to inform from the bits
of a positive integer.

the basic type "int" on our small machines normally have a
4-byte (32-bit) representation for signed or unsigned integers.

The order of bits in an integer starts at 0 according to tradition
we start from the least significant bit, that of order 0 (right)
to that of (total number of bits - 1).
    With 32 bits, the order can range from 0 to 31 inclusive.

Parameters in the functions offered below
are all positive integers of type "unsigned int"

The module offers to obtain:

the value of a specific bit (0, 1) with the function: get_bit (number, order)

the value by forcing a specific bit to 1 in an integer
with the function: set_bit (number, order)

the value by forcing a specific bit to 0 in
an integer with the function: clear_bit (number, order)

the value by forcing the inversion of a specific bit
in an integer with the function: flip_bit (number, order)

access to a representation of the bits of an integer in a string
of characters with the function: bits2string (number)

*/

/**********************************************************/
/*   AN INTRODUCTION TO MACOS FUNCTIONS

Four functions (get, set, clear and flip) also have a given MACRO version.
This alternative to classical factorization is important in engineering.
The programming of control modules is often subject to
severe performance requirements in execution speed
the use of macros that avoids functional overheads
can sometimes seriously speed up a program.

WARNING
There are rules and a natural order of development
since the function will always be much safer
his behavior is much easier to follow in stripping.
The macro has the name of the function all in CAPS.

*/


/**********************************************************/
#ifndef  __MODULE_OP_BITS0255__
#define  __MODULE_OP_BITS0255__

/**********************************************************/

#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<time.h>

/**********************************************************/


/**********************************************************/
/*                       CONSTANT                        */
/**********************************************************/

/*  The symbol for the number of bits in an integer
on the compilation platform.
*/
int NB_BITS=(sizeof(unsigned int) * 8);

/*  the acceptable order interval given as parameter
    will go from 0 to NB_BITS-1
*/

/**********************************************************/

/************************ GET_BIT *************************/
/*
	gives the value of the specified order bit.
PARAMETERS: number, an unsigned integer
order, specify the desired bit in number.
BACK: 0 or 1

SPECIFICATIONS:
If order is not in the correct range
the function returns 0
*/

int get_bit(unsigned int  nombre, unsigned int ordre);

// MACRO version
//#define GET_BIT(nombre, ordre)  (((ordre) < NB_BITS) ? (((nombre) & (1 << (ordre))) != 0) : 0)
/**********************************************************/

/*********************** SET_BIT **************************/
/*
	gives the value of the number with the specified order bit set to 1
    PARAMETERS: number, any integer
                 order, specifies the bit set in number.
RETURN: the value obtained from the parameter with this bit at 1

SPECIFICATIONS:
If order is not in the correct range
the function returns the value received
*/

unsigned int set_bit(unsigned  int nombre, unsigned int ordre);

// MACRO version
//#define SET_BIT(nombre, ordre)  (((ordre) < NB_BITS) ? ((nombre) | (1 << (ordre))) : (nombre))
/**********************************************************/

/******************** CLEAR_BIT ***************************/
/*
	gives the value of the number with the specified order bit set to 0
PARAMETERS: number, any integer
order, specifies the bit set to 0 in number
RETURN: the value obtained from the parameter with this bit at 0

SPECIFICATIONS:
If order is not in the correct range
the function returns the value received
*/

unsigned int clear_bit(unsigned int  nombre, unsigned int ordre);

//  MACRO version
//#define CLEAR_BIT(nombre, ordre)  (((ordre) < NB_BITS) ? (((nombre) & ~(1 << (ordre)))) : (nombre))
/**********************************************************/

/********************** FLIP_BIT **************************/
/*
	gives the value of the number received with the inverted bit
specified order
Enter: number: a positive integer
order: Specifies the bit to invert in number.
RETURN: the value obtained from the parameter with this inverted bit
SPECIFICATIONS:
If order is not in the correct range
the function returns the value received
*/
unsigned int flip_bit(unsigned int  nombre, unsigned int ordre);

// Notice the dual use of the conditional operator
//#define FLIP_BIT(nombre, ordre)  (((ordre) < NB_BITS)  ? GET_BIT(nombre, ordre) ? CLEAR_BIT(nombre, ordre) : SET_BIT(nombre, ordre) : (nombre))
/**********************************************************/

/***************** BITS2STRING ****************************/
/*
	gives a string representation (string of constant character) to
bits of the received number.
PARAMETER: number, an unsigned integer
RETURN: a constant chain
SPECIFICATIONS:
The bits are given in the string from least significant to most
significant, regardless of the sign of the actual parameter
*/
const char* bits2string(unsigned int nombre);

/**********************************************************/

#endif
/**********************************************************/

