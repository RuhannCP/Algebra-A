#include <stdio.h>
#include <stdlib.h>
#include <gmp.h>

void mdc_estendido(mpz_t g, mpz_t x, mpz_t y, const mpz_t a, const mpz_t b){
	mpz_t a1,y1,y2,q1,q,x1,x2;//variaveis de auxilio ....

	mpz_inits (a1,q1,y2,q,x1,x2,y1,NULL);
	
	mpz_set(g,a);
	mpz_set(a1,b);
	mpz_set_ui(x,1);
	mpz_set_ui(y1,1);

	
	/*____Operação algoritmo estendido ____*/
	do{

		mpz_div(q,g,a1);
		
		mpz_set(q1,g);
		mpz_set(x2,x);
		mpz_set(y2,y);
		
		mpz_set(g,a1);
		mpz_set(x,x1);
		mpz_set(y,y1);
		
		mpz_mul(a1,q,a1);
		mpz_sub(a1,q1,a1);
		
		mpz_mul(x1,x,q);
		mpz_sub(x1,x2,x1);
		
		mpz_mul(y1,y,q);
		mpz_sub(y1,y2,y1);

	}while((mpz_cmp_d (a1 , 0)));

	mpz_clears (x,x1,x2,y,y1,y2,g,q,q1,a1,NULL);
}

int inverso_modular(mpz_t r, const mpz_t a, const mpz_t n){
	mpz_t mdc,x,y;
	mpz_inits(mdc,x,y,NULL);
	
	mdc_estendido(mdc,x,y,n,a);

	if( mpz_cmp_ui(mdc,1) == 0 ){
		mpz_mod (r,y,n);
		return 1;
	}

	mpz_clears(mdc,x,y,r,NULL);
	
	return 0;
}
/*
void exp_binaria(mpz_t r,const mpz_t b,const mpz_t e,const mpz_t n){
    printf("Compilou\n");
}
*/