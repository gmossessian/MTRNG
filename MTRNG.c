/*
 * MTRNG.c
 *
 *  Created on: Nov 27, 2015
 *      Author: gmoss
 *
 *      Made from the Wikipedia psuedocode at https://en.wikipedia.org/wiki/Mersenne_Twister
 */

#include "MTRNG.h"

void twist(void);

#define __MTRNG_N 624

uint32_t MT[__MTRNG_N];
uint32_t indexMT=__MTRNG_N+1; //"index" is a global var used in string.h apparently...

uint32_t MTRNGNumber(void){
	uint32_t y;

	if (indexMT >= __MTRNG_N){
		if (indexMT > __MTRNG_N){
			MTRNGSeed(5489);
		}
		twist();
	}

	y=MT[indexMT];

	y ^= y>>11;
	y ^= (y<<7) & 0x9D2C5680UL;
	y ^= (y<<15) & 0xEFC60000UL;
	y ^= (y>>18);

	++indexMT;
	return 0xFFFFFFFF & y;
}

void MTRNGSeed(uint32_t seed){
	int i;
	indexMT=__MTRNG_N;
	MT[0]=seed;
	for(i=1; i<__MTRNG_N; i++){
		MT[i]= 0xFFFFFFFF & (1812433253*(MT[i-1]^(MT[i-1]>>(30)))+i);
	}
}

void twist(void){
	uint32_t i;
	uint32_t x;
	uint32_t xA;

	for(i=0; i<__MTRNG_N; i++){
		x =(MT[i] & 0x80000000) + (MT[(i+1)%__MTRNG_N] & 0x7fffffff);
		xA = x>>1;
		if (0x1 & x){
			xA^= 0x9908B0DF;
		}
		MT[i]=MT[(i+397) % __MTRNG_N] ^ xA;
	}
	indexMT = 0;
}

