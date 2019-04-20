#include <stdlib.h>
#include <stdio.h>
#include <gmp.h>
#include <assert.h>
#include "function.h"

int main(int argc, char * argv[]){
	mpz_t a;
	mpz_init (a);
	mpz_t b;
	mpz_init (b);
	mpz_t x;
	mpz_init (x);
	mpz_t y;
	mpz_init (y);
	mpz_t g;
	mpz_init (g);
	
	gmp_scanf("%Zd",&a);
	gmp_scanf("%Zd",&b);

	gmp_printf("A: %Zd \n\n",a);
	gmp_printf("B: %Zd \n\n",b);
	
	mpz_mdc(g,x,y,a,b);
	mpz_clear(a);
	mpz_clear(b);

	
	return 0;
}