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


	mpz_clear (x1);
	mpz_clear (x2);
	mpz_clear(y1);
	mpz_clear(y2);
	mpz_clear(q);
	mpz_clear(q1);
	mpz_clear(a1);
}

int inverso_modular(mpz_t r, const mpz_t a, const mpz_t n){
	mpz_t mdc,x,y;
	mpz_inits(mdc,x,y,NULL);
	
	mdc_estendido(mdc,x,y,n,a);

	if( mpz_cmp_ui(mdc,1) == 0 ){
		mpz_mod (r,y,n);
		return 1;
	}

	mpz_clear(mdc);
	mpz_clear(x);
	mpz_clear(y);
	
	return 0;
}

void exp_binaria(mpz_t r,const mpz_t b,const mpz_t e,const mpz_t n){

    mpz_t r1;//variavel auxiliar
	mpz_init (r1);

	//parada caso expoente 0
	if (mpz_cmp_ui(e,0) == 0){
		mpz_set_ui (r,1);
		return;
	}else{
	
		//caso expoente maior que 1
			mpz_fdiv_q_ui(r1, e, 2);
			exp_binaria(r, b, r1, n);

			mpz_mul(r1, r, r);
			mpz_mod(r1, r1, n);
			mpz_set(r, r1);

		//Tratamento caso expoente impar

			mpz_mod_ui(r1, e, 2);
			
			if((mpz_cmp_ui(r1,1) == 0) ){
				mpz_mul(r1, r, b);
				mpz_mod(r1, r1, n);
				mpz_set(r, r1);
			}
	}
	mpz_clear (r1);
}