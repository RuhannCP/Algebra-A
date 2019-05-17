#include <stdio.h>
#include <stdlib.h>
#include <gmp.h>
#include <math.h>
#include "function.h"

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
