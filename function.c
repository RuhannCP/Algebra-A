#include <stdio.h>
#include <stdlib.h>
#include <gmp.h>

void mpz_mdc(mpz_t g, mpz_t x, mpz_t y, const mpz_t a, const mpz_t b){
	mpz_t a1,y1,y2,q1,q,x1,x2;//variaveis de auxilio ....

	mpz_init(a1);
	mpz_init(q1);
	mpz_init(y2);
	mpz_init(q);
	mpz_init(x1);
	mpz_init(x2);
	mpz_init(y1);
	
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
		
		gmp_printf("while %Zd \n \n",g);
		//Print de teste1 vendo a operação do mdc...

	}while((mpz_cmp_d (a1 , 0)));

    gmp_printf("MDC = %Zd \n",g);//valor do mdc
	gmp_printf("X = %Zd \n",x);//valor de x da combinação linear
	gmp_printf("Y = %Zd \n",y);//valor de y da combinação linear

	mpz_clear(x);
	mpz_clear(x1);
	mpz_clear(x2);
	mpz_clear(y);
	mpz_clear(y2);
	mpz_clear(y1);
	mpz_clear(g);
	mpz_clear(q);
	mpz_clear(q1);
	mpz_clear(a1);
}

int inverso_modular(mpz_t r, const mpz_t a, const mpz_t n){
    return 0;
}
/*
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
