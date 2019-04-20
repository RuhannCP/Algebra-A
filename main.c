#include <stdlib.h>
#include <stdio.h>
#include <gmp.h>
#include <assert.h>
#include "function.h"

int main(int argc, char * argv[]){
	int n = 0;
	mpz_t a,b;
	mpz_t x,y;

	mpz_init(a); 
	mpz_init(b); 
	
	mpz_init(x); 
	mpz_init(y); 
	
	gmp_scanf("%Zd",&a);
	gmp_scanf("%Zd",&b);

	gmp_printf("A: %Zd \n\n",a);
	gmp_printf("B: %Zd \n\n",b);
	
	//mpz_mdc(g,x,y,a,b);
	
	mpz_clear(a); 
	mpz_clear(b); 
	
	return 0;
}