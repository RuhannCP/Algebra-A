#include <stdio.h>
#include <stdlib.h>
#include <gmp.h>

mpz_t *mpz_gcd(mpz_t g, mpz_t a, mpz_t b){
    mpz_t *m;
    return m;
}

long mod(long a, long b)
{
    long r = a % b;

    /* Uma correçã é necessária se r e b não forem do mesmo sinal */

    /* se r for negativo e b positivo, precisa corrigir */
    if ((r < 0) && (b > 0))
   return (b + r);

    /* Se ra for positivo e b negativo, nova correcao */
    if ((r > 0) && (b < 0))
   return (b + r);

    return (r);
}

long euclides_ext(long a, long b, long c)
{
    long r;

    r = mod(b, a);

    if (r == 0) {
   return (mod((c / a), (b / a)));   // retorna (c/a) % (b/a)
    }

    return ((euclides_ext(r, a, -c) * b + c) / (mod(a, b)));
}

int inverso_modular(mpz_t r, const mpz_t a, const mpz_t n){
    return 0;
}

void exp_binaria(mpz_t r,const mpz_t b,const mpz_t e,const mpz_t n){
    printf("Compilou\n");
}