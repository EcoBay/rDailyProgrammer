#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

struct board{
    uint8_t l;
    uint8_t *buff;
};

struct board *createBoard(uint8_t l){
    struct board *b = malloc(2);
    b -> l = l;
    l = l * l + 8 - 1 >> 3;
    uint8_t *buff = malloc(l);
    memset(buff, 0, l);
    b -> buff = buff;
    return b;
}

void set(struct board *b, uint16_t loc){
    uint16_t invl = b -> l * b -> l - loc - 1;
    b->buff[loc >> 3] |= 1 << (loc & 7);
    b->buff[invl >> 3] |= 1 << (invl & 7);
}

_Bool get(struct board *b, uint16_t loc){
    return b->buff[loc >> 3] >> (loc & 7) & 1;
}

void printBoard(struct board *b){
    for(uint16_t loc = 0, l = b -> l; loc < l*l; loc++)
        printf(" %s%.*s",
            get(b, loc) ? "#" : ".",
            (loc + 1) % b -> l == 0, "\n"
        );
}

void dps(struct board *b, uint16_t loc, uint8_t l, uint8_t *notVisited){
    uint16_t invl = l * l - loc - 1;
    notVisited[loc >> 3] &= ~(1 << (loc & 7));
    notVisited[invl >> 3] &= ~(1 << (invl & 7));

#define check(x) notVisited[x >> 3] >> (x & 7) & 1 && !get(b, x)
    if(loc >= l          && check(loc - l)) dps(b, loc - l, l, notVisited);
    if(loc % l           && check(loc - 1)) dps(b, loc - 1, l, notVisited);
    if(loc < l * (l - 1) && check(loc + l)) dps(b, loc + l, l, notVisited);
    if((loc + 1) % l     && check(loc + 1)) dps(b, loc + 1, l, notVisited);
#undef check
}

_Bool isConnected(struct board *b){
    uint16_t loc;
    for(loc = 0; get(b, loc);loc++); 

    uint8_t l = b -> l * b -> l + 8 - 1 >> 3;
    uint8_t *buff = malloc(l);
    memset(buff, 0xFF, l);
    buff[l-1] &= (1 << (b -> l * b -> l & 7)) - 1;

    dps(b, loc, b -> l, buff);
    _Bool res = !memcmp(buff, b->buff,l);
    free(buff);

    return res;
}

uint16_t getNumbers(struct board *b, uint16_t **a, uint16_t **d){
    uint8_t an = 0, dn = 0, l = b -> l;
    uint16_t ll = l * l + 8 - 1 >> 3;
    uint8_t *numba = malloc(ll);
    uint8_t *numbd = malloc(ll);
    for(uint16_t i=0; i < l*l; i++){
        if(!get(b, i) && (!(i%l) || get(b, i-1))){
            an++;
            numba[i >> 3] |= 1 << (i & 7);
        }
        if(!get(b, i) && (!(i/l) || get(b, i-l))){
            dn++;
            numbd[i >> 3] |= 1 << (i & 7);
        }
    }

    *a = malloc(an);
    *d = malloc(dn);

    for(uint16_t i=0, ai=0, di=0, ctr=1, r=0; i < l*l; i++, r=0){
        if(numba[i >> 3] >> (i & 7) & 1){
            (*a)[ai++] = ctr;
            r = 1;
        }
        if(numbd[i >> 3] >> (i & 7) & 1){
            (*d)[di++] = ctr;
            r = 1;
        }
        if(r) ctr++;
    }

    return an << 8 | dn;
}

int main(int argc, char **argv){
    struct board *b = createBoard(7);
    set(b, 3);
    set(b,10);
    set(b,21);
    set(b,22);
    printBoard(b);

    int16_t *a, *d, n = getNumbers(b, &a, &d);

    for(int i=0; i < n >> 8; i++) printf("%d ", a[i]);
    printf("\n");
    for(int i=0; i < (n & (1 << 8) - 1); i++) printf("%d ", d[i]);

    return 0;
}
