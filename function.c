#include <stdio.h>
#include <stdlib.h>
#include <gmp.h>

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
