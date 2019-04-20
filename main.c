#include <stdio.h>
#include <gmp.h>
#include <assert.h>
#include "function.h"

int main(int argc, char * argv[]){
	int n = 0;
	mpz_t a,b,x,y,g;
	gmp_scanf(a,b,x,y);
	mpz_inits ( g,x,y,a,b);

	mpz_mdc(g,x,y,a,b);
	
	return 1;
}