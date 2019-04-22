#include <stdio.h>
#include <stdlib.h>
#include <gmp.h>

void mdc_estendido(mpz_t g, mpz_t x, mpz_t y, const mpz_t a, const mpz_t b);
int inverso_modular(mpz_t r, const mpz_t a, const mpz_t n);
//void exp_binaria(mpz_t r,const mpz_t b,const mpz_t e,const mpz_t n);
//void fact(int n);