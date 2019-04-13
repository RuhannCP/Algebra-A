#include "gmp.h"
#include <stdio.h>
#include <assert.h>

int main(int argc, char *argv){
	mpz_t a;
	mpz_t b;
	
	mpz_t init;
	mpz_init(a);
	mpz_init(b);
	
	mpz_set_ui(a,8);
	mpz_set_ui(b,10);
	
	mpz_add(a,a,b);
	
	gmp_printf("%Zd resultado",a);
	
	mpz_clear(a);
	mpz_clear(b);


	return 0;
	
}
