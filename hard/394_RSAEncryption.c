#include <stdio.h>
#include <stdlib.h>
#include <gmp.h>

static gmp_randstate_t randstate;
typedef unsigned long long ull;

struct key{
    mpz_t exponent;
    mpz_t modulos;
};

void generateKey(unsigned int width, struct key *pub, struct key *priv){
    mpz_t p, q;
    mpz_init(p);
    mpz_init(q);

    mpz_urandomb(p, randstate, width >> 1);
    mpz_urandomb(q, randstate, width >> 1);

    mpz_setbit(p, (width >> 1) - 1);
    mpz_setbit(p, (width >> 1) - 2);
    mpz_setbit(q, (width >> 1) - 1);
    mpz_setbit(q, (width >> 1) - 2);

    mpz_nextprime(p, p);
    mpz_nextprime(q, q);

    mpz_t n; mpz_init(n);
    mpz_mul(n, p, q);

    mpz_set_ui(pub -> exponent, 65537ul);
    mpz_set(pub -> modulos, n);
    mpz_set(priv -> modulos, n);
    
    mpz_sub_ui(p, p, 1ul);
    mpz_sub_ui(q, q, 1ul);

    mpz_lcm(p, p, q);
    mpz_invert(priv -> exponent, pub -> exponent, p);

    mpz_clear(p); mpz_clear(q);
}

void encrypt(mpz_t C, const mpz_t M, const struct key k){ 
    mpz_powm(C, M, k.exponent, k.modulos);
}

void decrypt(mpz_t M, const mpz_t C, const struct key k){
    mpz_powm(M, C, k.exponent, k.modulos);
}

int main(int argc, char **argv){
    gmp_randinit_mt(randstate);
    gmp_randseed_ui(randstate, 19);

    struct key pub, priv;

    mpz_init(pub.modulos); mpz_init(pub.exponent);
    mpz_init(priv.modulos); mpz_init(priv.exponent);
    generateKey(1024, &pub, &priv);

    mpz_t M; mpz_init_set_ui(M, 123456ul);
    mpz_t C; mpz_init(C);

    encrypt(C, M, pub);
    decrypt(M, C, priv);

    printf("%llu\n", mpz_get_ui(M));

    return 0;
}
