/*********************************************************/
//  PAR : H. Saulnier,  F. Henri, E. Thé

/*********************************************************/

/*********************************************************/

/* implementation of the functions offered in op_bits.h         */
/* all are simple and based on the C bitwise operators */

#include "op_bits.h"

/*********************************************************/


/*********************************************************/
/*                DEFINITIONS DES FONCTIONS              */
/*********************************************************/



/*****************************************************/
int get_bit(unsigned int nombre, unsigned int ordre) {
	// STRATEGIE :
	// test valid order
	// if so, a bitwise and && with a bit stream
	// that a 1 judiciously placed in good order
	// if not return 0

	if (ordre < NB_BITS){
		return  (nombre & (1 << ordre)) != 0;
	}

	return 0;
}

/*****************************************************/
unsigned int set_bit(unsigned int nombre, unsigned int ordre) {
	// STRATEGIE :
	// test valid order
	// IF YES a bitwise or with a bit stream with only 1
	// judiciously placed in good order
	// if not return value collected

	if (ordre < NB_BITS){
		return  nombre | (1 << ordre);
	}

	return nombre;
}

/*****************************************************/
unsigned int clear_bit(unsigned int nombre, unsigned int ordre){
	// STRATEGIE :
	// test valid order
	// IF YES a bitwise and with the complement of a bit stream
	// who has a single 0 judiciously placed at the correct order
	// if not return value collected

	if (ordre < NB_BITS){
		return nombre & ~(1 << ordre);
	}

	return nombre;
}

/*****************************************************/
unsigned int flip_bit(unsigned int nombre, unsigned int ordre){
	// STRATEGIE :
	// test valid order
	// SI OUI si le bit ordre est à 1, on le clear sinon on le set
	// if not return value collected

	if (ordre < NB_BITS){
		if (get_bit(nombre, ordre)) {
			return clear_bit(nombre, ordre);
		}
		return set_bit(nombre, ordre);
	}

	return nombre;
}

/*****************************************************/
const char * bits2string(unsigned int nombre) {
	// a size buffer of 200 tanks is more than enough
	// buffer [] is a static local variable whose position is permanent
	static char buffer[200] = { 0 };
	int i;      // iterator

	// make sure the end of chain indicator
	buffer[NB_BITS] = 0;

	// assignment loop of each bit obtained
	// from get_bit in the string (but in reverse order)
	for (i = 0; i< NB_BITS; i += 1) {
		buffer[NB_BITS - 1 - i] = get_bit(nombre, i) ? '1' : '0';
	}

	// return string
	return buffer;
}
/*****************************************************/

