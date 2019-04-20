#include <stdio.h>
#include <gmp.h>
#include <assert.h>
#include "function.h"

int main(int argc, char * argv[]){
	int n = 0;
	mpz_t a,b,x,y,g;

	mpz_init(a);
	mpz_init(b);
	mpz_init(x); 
	mpz_init(y); 
	mpz_init(g); 
	
	gmp_scanf("%Z %Z %Z %Z",&a,&b,&x,&y);

	gmp_printf("%Z",a);

	//mpz_mdc(g,x,y,a,b);
	
	mpz_clear(a);
	mpz_clear(b);
	mpz_clear(x); 
	mpz_clear(y); 
	mpz_clear(g); 

	return 1;
}