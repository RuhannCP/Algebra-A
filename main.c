#include <stdio.h>
#include <gmp.h>
#include <assert.h>
#include "function.h"

void fact(int n){
	int i = 0;
	mpz_t p ;

	mpz_init_set_ui(p,1); 

	for (i=1; i <= n ; ++i)
		mpz_mul_ui(p,p,i);
	
	printf ("%d!  =  \n", n);
	mpz_out_str(stdout,10,p);
	mpz_clear(p);

}

int main(int argc, char * argv[]){
	int n = 0;

	if (argc <= 1){
		printf ("Usage: %s <number> \n", argv[0]);
		return 2;
	}

	n = atoi(argv[1]);
	assert( n >= 0);
	fact(n);

	return 1;
}