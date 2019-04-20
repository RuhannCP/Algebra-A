#include <stdio.h>
#include <stdlib.h>
#include <gmp.h>

void mpz_mdc(mpz_t g, mpz_t x, mpz_t y, const mpz_t a, const mpz_t b){
	
	 mpz_set (x, a);
	 mpz_set (y, b);

	while ( g != 0){
		mpz_mod(g,x,y);
		mpz_set (x, y);
		mpz_set (y,g);
	}

	gmp_printf("MDC = %zd", g);
}

int inverso_modular(mpz_t r, const mpz_t a, const mpz_t n){
    return 0;
}

void exp_binaria(mpz_t r,const mpz_t b,const mpz_t e,const mpz_t n){
    printf("Compilou\n");
}

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