#include <stdio.h>
#include <stdlib.h>
#include <gmp.h>
#include <math.h>
#include "function.h"


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
		
		mpz_ui_pow_ui(aux, 256, k);
		mpz_fdiv_q(aux, n1, aux);
		mpz_mod_ui(c, aux, 256);
		mpz_ui_pow_ui(aux, 256, k);
		mpz_mul(aux, c, aux);
		mpz_sub(n1, n1, aux);
		
		//Converte
		letra = mpz_get_ui (c);
		str[k] = (int) letra;
	}

	str[k]='\0';

	mpz_clears(c, n1, aux, NULL);

	return str;

}

void numero_aleatorio(mpz_t r, const mpz_t n, gmp_randstate_t rnd) {//Função dada
    mp_bitcnt_t num_bits = mpz_sizeinbase(n, 2);
    
    do {
            mpz_urandomb(r, rnd, num_bits);
        } while (!(mpz_cmp_ui(r, 1) >= 0 && mpz_cmp(r, n) <= 0));
    }

int talvez_primo(const mpz_t a, const mpz_t n, const mpz_t n1, unsigned int t, const mpz_t q){
    int k=0,i=0;
    mpz_t aux,aux1;
    mpz_inits (aux, aux1, NULL);
    mpz_div_ui (aux,n,2);
    mpz_div_ui (aux1,n,5);
    
    if (mpz_cmp_ui(aux,0) || mpz_cmp_ui(aux1,0)){//Para caso n seja par ou multiplo de cinco
        return 0;
    }
    for (int k=0;k<=n1;k++){// definindo (n-1) com fatores de q*2k
        t = pow(2,k);
        mpz_div_ui (aux1,n1,t);
        mpz_mod_ui (aux,aux1,2);
        if (!mpz_cmp_ui(aux,0)){
            break;
        }
    }
    mpz_set(q,aux1);//definindo o valor de q
    mpz_pow(aux,a,q);
    mpz_mod (aux,aux,n);
    if (!mpz_cmp(aux,1)){//caso valor seja diferente de um esse numero é composto
        return 0;
    }
    for (i = 1;i <= k;i++){//verificando se existe algum i tal que 2î*q seja congruente a 1 mod(p)
        t = pow(2,i);
        mpz_mul_ui(aux,q,t);
        mpz_mod (aux,aux,n);
        if (mpz_cmp_ui(aux,1) && i > 1){
            return 0;
        }
    }
    /*-----retorno da função composto ou pode ser primo -------*/
    if (mpz_cmp(aux,n1) || mpz_cmp_ui(aux,1)){
        return 1;
    }else{
        return 0;
    }
    mpz_clears (aux, aux1, NULL);
}

int provavelmente_primo(const mpz_t n, unsigned int iter, gmp_randstate_t rnd){
    int i = 0,x=0;
    mpz_t r,n1,t,q;
    mpz_inits (r,n1,t,q,NULL);
    mpz_sub_ui (n1,n,1);
    for(i=1;i<=iter;i++){//Loop verifica primo
        numero_aleatorio(r, n,NULL);//Gerador de possiveis "a"
        
        x = talvez_primo(r,n,n1,t,q);
        if(x == 0){
            return 0;
        }
    }
    mpz_clears(r,n1,t,q,NULL);
    return 1;
}

void primo_aleatorio(mpz_t r, unsigned int b, gmp_randstate_t rnd){
    int n = pow(2,b);
    int x = 0;
    do{
        numero_aleatorio (r,n,rnd);

        x = provavelmente_primo(r,n,rnd);
        
        if (x == 1){
            return 1;
        }
    }while(x == 0);
    return 0;
}

/** Questão 1 tp 4 */

void gera_primo_seguro(mpz_t p,unsigned int b,gmp_randstate_t rnd){

    for (int i = 1;i > 0;i++){
        primo_aleatorio(p,b,rnd);
        mpz_mul_ui(p,2,p);
        mpz_add_ui(p,p,1);
        provavelmente_primo(p,b,rnd);
        if(provavelmente_primo(p,b,rnd) == 1){
            break;
        }
    }
}

void encontra_gerador(mpz_t g,const mpz_t p,gmp_randstate_t rnd){

    mpz_t aux,aux1;
    mpz_inits(aux,aux1,NULL);

    do{
        numero_aleatorio(g,p,rnd);

        mpz_div_ui(aux,p,2);
        mpz_div(aux1,p,aux);

        mpz_pow(aux,g,aux);
        mpz_mod(aux,aux,p);

        mpz_pow(aux1,g,aux1);
        mpz_mod(aux1,aux1,p);
    }while(!(mpz_cmp_ui(aux,1)) && !(mpz_cmp_ui(aux1,1)));

    mpz_clears(aux,aux1,NULL);
}

void gera_chave_elgamal(mpz_t p,mpz_t g,mpz_t A,gmp_randstate_t rnd){
    
    mpz_t aux,a;
    mpz_inits(aux,a,NULL);
    mpz_sub_ui(aux,p,1);

    gera_primo_seguro(p,1024,rnd);
    numero_aleatorio(a,aux,rnd);
    encontra_gerador(g,p,rnd);

    mpz_pow(A,g,a);

}
void criptografa(mpz_t B,mpz_t C,const mpz_t M,const mpz_t p,const mpz_t g,const mpz_t A,gmp_randstate_t rnd){

    gera_chave_elgamal(p,g,B,rnd);

	exp_binaria(C, M, A, p);
}
void descriptografa(mpz_t M, const mpz_t B, const mpz_t C, const mpz_t p, const mpz_t g, const mpz_t a){

    exp_binaria(M, C, B, p);
    
    mpz_pow(M,M,a);
    mpz_mod(M,M,p);
}