/*
 * CC_Rand48.h
 *
 *  Created on: Feb 4, 2014
 *      Author: jqnorris
 */

#ifndef CC_RAND48_H_
#define CC_RAND48_H_

/* Because the "standard" library is not standard, this file provides
 * rand48() functionality that is cross-platform compatible.*/

/* For cross-platform compatibility we use the boost random number generator
 * library. */
#include <boost/random.hpp>
#include <boost/random/linear_congruential.hpp>

/* We seed the random number generator using the time stamp counter via the
RDTSC instruction. We create a function that returns the time stamp counter
that we use to see the random */

// For Windows systems, we use the specialized rdtsc routine
#ifdef _WIN32
#define rdtsc  __rdtsc

//  For everything else we use assembly code instructions
#else
unsigned long long rdtsc(){
	unsigned int lo,hi;
	__asm__ __volatile__ ("rdtsc" : "=a" (lo), "=d" (hi));
	return ((unsigned long long)hi << 32) | lo;
}
#endif

// We seed the random number generator using our function.
boost::rand48 rng(static_cast<unsigned int>(rdtsc()));

// If the situation demands, we can use a static seed.
//boost::rand48 rng(static_cast<unsigned int>(12));

// We define a function that can be used just like "standard" library std::rand48()
// but on other platoforms.
boost::uniform_01<boost::rand48> cc_drand48(rng);


#endif /* CC_RAND48_H_ */
