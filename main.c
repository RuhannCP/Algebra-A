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
	mpz_t r;
	mpz_init(r);
	
	gmp_scanf("%Zd",&a);
	gmp_scanf("%Zd",&b);

	gmp_printf("A: %Zd \n\n",a);
	gmp_printf("B: %Zd \n\n",b);
	
	mdc_estendido(g,x,y,a,b);	
	gmp_printf("MDC: %Zd \n\n",g);

	inverso_modular(r,a,b);
	gmp_printf("\ninverso = %Zd\n",r);
	mpz_clears (a,b,r,NULL);
	
	return 0;
}