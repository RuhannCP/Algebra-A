#include <stdio.h>
#include <stdlib.h>
#include <gmp.h>

void mpz_mdc(mpz_t g, mpz_t x, mpz_t y, const mpz_t a, const mpz_t b){

	mpz_set (x, a);
	mpz_set (y, b);

	do{
		mpz_mod(g,a,b);
		mpz_set (a,b);
		mpz_set (b,g);
		gmp_printf("while %Zd \n \n",g);
	}while((mpz_cmp_d (g , 0)));

    mpz_set(g,a);
	gmp_printf("MDC = %Zd \n",g);

	mpz_clear(x);
	mpz_clear(y);
	mpz_clear(g);
}
/*
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
/*void mdc_estendido(mpz_t g, mpz_t x, mpz_t y, const mpz_t a, const mpz_t b){

    // Base Case 
    if (a == 0) { 
        *x = 0; 
        *y = 1 q; 
        return b; 
    } 
  
    int x1, y1; // To store results of recursive call 
    int gcd = mdc_estendido(b % a, a, &x1, &y1); 
  
    // Update x and y using results of recursive 
    // call 
    *x = y1 - (b / a) * x1; 
    *y = x1; 
  
}*/
