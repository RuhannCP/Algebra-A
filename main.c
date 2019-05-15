#include <stdlib.h>
#include <stdio.h>
#include <gmp.h>
#include <assert.h>
#include "function.h"


int main(int argc, char * argv[]){
	mpz_t a,b,x,y,g,r;
	mpz_inits (a,b,x,y,g,r,NULL);
	
	gmp_scanf("%Zd",&a);
	gmp_scanf("%Zd",&b);
	gmp_scanf("%Zd",&x);

	binary_exp(r,a,b,x);
	exp_binaria(g,a,b,x);
	
	gmp_printf("\n exp-bin r = %Zd\n",r);
	gmp_printf("\n exp-bin g = %Zd\n",g);

	mpz_clears (a,b,r,y,g,x,NULL);
	
	return 0;
}
