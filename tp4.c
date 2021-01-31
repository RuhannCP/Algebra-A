#include <stdio.h>
#include <stdlib.h>
#include <gmp.h>
#include <string.h>


void exp_binaria(mpz_t r, const mpz_t b, const mpz_t e, const mpz_t n)
{
	
	mpz_t aux;
	mpz_init(aux);

	if(mpz_cmp_ui (e, 0) == 0)
	{
		mpz_set_ui(r, 1);
		return;
	}

	else 
	{
		mpz_fdiv_q_ui(aux, e, 2);
		exp_binaria(r, b, aux, n);

		mpz_mul(aux, r, r);
		mpz_mod(aux, aux, n);
		mpz_set(r, aux);

		mpz_mod_ui(aux, e, 2);
		if(mpz_cmp_ui (aux, 1) == 0)
		{
			mpz_mul(aux, r, b);
			mpz_mod(aux, aux, n);
			mpz_set(r, aux);
		}

  	}

	mpz_clear(aux);
}

void mdc_estendido(mpz_t g, mpz_t x, mpz_t y, const mpz_t a, const mpz_t b)
{

	mpz_t resto, auxX, auxY, quociente, aux;
	mpz_inits(resto, auxX, auxY, quociente, aux, NULL);
	mpz_set(auxX , x);
	mpz_set(auxY , y);
	
	if(mpz_cmp_ui(b, 0)==0)
	{
		mpz_set_ui(x, 1);
		mpz_set_ui(y, 0);
		mpz_set(g,a);
		return;
	}

	mpz_fdiv_qr(quociente, resto, a, b);
	mdc_estendido(g, auxX, auxY, b, resto);
	
	mpz_set(x, auxY);
	mpz_mul(aux, quociente, auxY);
	mpz_sub(y, auxX, aux);

	mpz_clears(resto, auxX, auxY, quociente, aux, NULL);
}

int inverso_modular(mpz_t r, const mpz_t a, const mpz_t n)
{
	mpz_t g, x, y;
	mpz_inits(g, x, y, NULL);

	mdc_estendido(g, x, y, n, a);

	if (mpz_cmp_ui(g, 1)==0)
	{
		mpz_mod(r, y, n);
		return 1;
	}
	
	mpz_clears(g, x, y, NULL);	

	return 0;
}


void calcula_tqn(const mpz_t n, mpz_t n1, unsigned int *t, mpz_t q)
{

	*t=0;
	mpz_t aux, auxN1;
	mpz_inits(aux, auxN1, NULL);
	mpz_sub_ui(aux, n, 1);
	mpz_set(n1, aux);
	mpz_set(auxN1, n1);
	
	mpz_mod_ui(aux, auxN1,2);
	while(mpz_cmp_ui(aux,0)==0)
	{
		mpz_fdiv_q_ui(auxN1, auxN1, 2);
		*t += 1;
		mpz_mod_ui(aux, auxN1,2);
	}

	mpz_set(q, auxN1);
	
	mpz_clears(aux, auxN1, NULL);
}

int talvez_primo(const mpz_t a,	const mpz_t n, const mpz_t n1, unsigned int t, const mpz_t q)
{

	unsigned int i;
	mpz_t aux, e;
	mpz_inits(aux, e, NULL);
	
	if (mpz_cmp_ui(n,1)==0 || mpz_cmp_ui(n,2)==0)
		return 1;
	
	mpz_mod_ui(aux, n, 2);
	if (mpz_cmp_ui(aux,0)==0)
		return 0;

	
	else
	{	
		exp_binaria(aux, a, q, n);
		if(mpz_cmp_ui(aux,1)==0 || mpz_cmp(aux, n1)==0)
			return 1;

		for(i=1; i<t; i++){
			
			mpz_ui_pow_ui(aux, 2, i);
			mpz_mul(aux, aux, q);
			mpz_set(e, aux);

			exp_binaria(aux, a, e, n);
	
			if(mpz_cmp(aux, n1)==0)
				return 1;
		}
	}

	mpz_clears(aux, e, NULL);
}

void numero_aleatorio(mpz_t r, const mpz_t n, gmp_randstate_t rnd) 
{
	
	mp_bitcnt_t num_bits = mpz_sizeinbase(n, 2);
	do 
	{
		mpz_urandomb(r, rnd, num_bits);
	} while (!(mpz_cmp_ui(r, 1) >= 0 && mpz_cmp(r, n) <= 0));
}

int provavelmente_primo(const mpz_t n, unsigned int iter, gmp_randstate_t rnd)
{
	mpz_t a, aux, q, n1;
	unsigned int t, miller;
	mpz_inits(a, aux, q, n1, NULL);
	unsigned int i;

	if (mpz_cmp_ui(n,1)==0 || mpz_cmp_ui(n,2)==0)
		return 1;
	
	mpz_mod_ui(aux, n, 2);
	if (mpz_cmp_ui(aux,0)==0)
		return 0;

	calcula_tqn(n, n1, &t, q);	

	for(i=0; i<iter; i++)
	{
		mpz_sub_ui(aux, n, 2);
		numero_aleatorio(a, aux, rnd);
		mpz_add_ui(a, a, 1);

		miller = talvez_primo(a, n, n1, t, q);

		if(miller == 0)
			return 0;

	}

	mpz_clears(a, aux, q, n1, NULL);
	return 1;
}

void primo_aleatorio(mpz_t r,unsigned int b,gmp_randstate_t rnd)
{

	int provPrimo=0;
	unsigned int iter = 20;

	while(!provPrimo)
	{
		mpz_urandomb(r, rnd, b);
		provPrimo = provavelmente_primo(r, iter, rnd);
	}
}

void gera_chaves(mpz_t n, mpz_t e, mpz_t d, gmp_randstate_t rnd)
{
	
	mpz_t p, q, g, x, y;
	mpz_inits(p, q, g, x, y, NULL);

	unsigned int exp=2048;
	primo_aleatorio(p, exp, rnd);
	primo_aleatorio(q, exp, rnd);
	mpz_mul(n, p, q);

	mpz_set_ui(e, 65537);
	mdc_estendido(g, x, y, n, e);
	
	while(mpz_cmp_ui(g,1)!=0)
	{
		mdc_estendido(g, x, y, n, e);
		mpz_add_ui(e, e, 1);
	}

	mpz_t phi, aux;
	mpz_inits(phi, aux, NULL);
	mpz_sub_ui(aux, p, 1);
	mpz_set(phi, aux);
	mpz_sub_ui(aux, q, 1);
	mpz_mul(phi, phi, aux);

	inverso_modular(d, e, phi);


	mpz_clears(p, q, g, x, y, phi, aux, NULL);
}

void gera_primo_seguro(mpz_t p,unsigned int b,gmp_randstate_t rnd)
{

        for (int i = 1;i > 0;i++)
		{//Gera um primo na forma 2p+1
            primo_aleatorio(p,b-1,rnd);
            mpz_mul_ui(p,p,2);
            mpz_add_ui(p,p,1);
            
			if(provavelmente_primo(p,b,rnd))
			{
                break;
            }
        }
    return;
}

void encontra_gerador(mpz_t g,const mpz_t p,gmp_randstate_t rnd)
{

    mpz_t aux,aux1;
    mpz_inits(aux,aux1,NULL);

    do
	{
        numero_aleatorio(g,p,rnd);

        mpz_div_ui(aux,p,2);
        mpz_div(aux1,p,aux);

        mpz_powm(aux,g,aux,p);

        mpz_powm(aux1,g,aux1,p);
    }while(!(mpz_cmp_ui(aux,1)));

    mpz_clears(aux,aux1,NULL);
}

void gera_chave_elgamal(mpz_t p,mpz_t g,mpz_t A,gmp_randstate_t rnd)
{    
    mpz_t aux,a;
    mpz_inits(aux,a,NULL);
    mpz_sub_ui(aux,p,1);

    numero_aleatorio(a,aux,rnd);

    mpz_set_ui(aux,1);
    exp_binaria(A, g, a, p);
	mpz_clears(aux,a,NULL);

}

void criptografa(mpz_t B, mpz_t C, const mpz_t M, const mpz_t p, const mpz_t g, const mpz_t A, gmp_randstate_t rnd)
{
    mpz_t a, aux;
    mpz_inits(a, aux, NULL);
    mpz_set(aux, p);
    mpz_sub_ui(aux,aux,1);
    
    numero_aleatorio(a, aux, rnd);
    
    exp_binaria(aux, A, a, p);
    mpz_mul(C, M, aux);

    exp_binaria(B, g, a, p);
	mpz_clears(a, aux, NULL);
}

void descriptografa(mpz_t M, const mpz_t B, const mpz_t C, const mpz_t p, const mpz_t g, const mpz_t a)
{
    
    mpz_t aux;
    mpz_init(aux);
    mpz_sub(aux,p,a);
    mpz_sub_ui(aux,aux,1);
    exp_binaria(M,B,aux,p);
    mpz_mul(M,C,M);
    mpz_mod(M,M,p);
    mpz_clear(aux);
   
}