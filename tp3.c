#include <stdio.h>
#include <stdlib.h>
#include <gmp.h>
#include <math.h>
#include "function.h"

void gera_chaves(mpz_t n, mpz_t e, mpz_t d, gmp_randstate_t rnd){
    mpz_t p,q,tp,tq,fi,g,y;

    mpz_inits(p,tp,tq,g,y,q,NULL);

    //Generating prime numbers...
    primo_aleatorio(p,2048,rnd);
    primo_aleatorio(q,2048,rnd);

    mpz_mul (n,p,q);

    //Calculate phi(n)....
    mpz_sub_ui(tp,p,1);
    mpz_sub_ui(tq,q,1);
    mpz_mul(fi,tp,tq);

    mpz_set_ui(e,65537);

    //calculate keys primary and secondary...
    do{
        mpz_add_ui(e,e,1);
        mdc_estendido( g, d, y, e, fi);
    }
    while (mpz_cmp_ui(g,1)!=1);

    mpz_clears(p,tp,tq,g,y,q,NULL);
}

void codifica(mpz_t r, const char *str){
    int i, n = strlen(str);
    mpz_t r1;
    mpz_init (r1);

    //Encodes the message
    for (i=0;i<=n;i++){
        mpz_pow_ui (r1,256,i);
        mpz_mul_ui(r1,r1,str[i]);
        mpz_add(r,r,r1);
    }
    mpz_clear(r1);

}

char *decodifica(const mpz_t n){
    char *str = (char*) malloc(501*sizeof(char));
	unsigned int k, letra;

	mpz_t c, n1, aux;
	mpz_inits(c, n1, aux, NULL);
	
	mpz_set(n1, n);

 	for(k=0; k<500; k++){
		
		if(mpz_cmp_ui(n1,0)==0)
			break;
		
		mpz_ui_pow_ui(aux, 256, i);
		mpz_fdiv_q(aux, n1, aux);
		mpz_mod_ui(c, aux, 256);
		mpz_ui_pow_ui(aux, 256, i);
		mpz_mul(aux, c, aux);
		mpz_sub(n1, n1, aux);
		
		//Converte
		letra = mpz_get_ui (c);
		str[i] = (int) letra;
	}

	str[i]='\0';

	mpz_clears(c, n1, aux, NULL);

	return str;

}

void criptografa(mpz_t C,const mpz_t M,const mpz_t n,const mpz_t e){
	binary_exp(C, M, e, n);
}

void descriptografa(mpz_t M,const mpz_t C,const mpz_t n,const mpz_t d){
	binary_exp(M, C, d, n);
}