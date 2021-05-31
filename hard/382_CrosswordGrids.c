#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#define bytesLength(x) (x * x + 8 - 1 >> 3)

void tgl(uint8_t *b, uint8_t l, uint16_t loc){
    uint16_t mlc = l * l - loc - 1;
    b[loc >> 3] ^= 1 << (loc & 7);
    if(loc != mlc) b[mlc >> 3] ^= 1 << (mlc & 7);
}

_Bool get(uint8_t *b, uint16_t loc){
    return b[loc >> 3] >> (loc & 7) & 1;
}

void printBoard(uint8_t *b, uint8_t l){
    for(uint16_t loc = 0; loc < l*l; loc++)
        printf(" %s%.*s",
            get(b, loc) ? "#" : ".",
            (loc + 1) % l == 0, "\n"
        );
}

void dps(uint8_t *b, uint8_t l, uint16_t loc, uint8_t *notVisited){
    tgl(notVisited, l, loc);
    
#define check(x) get(notVisited, x) && !get(b, x)
    if(loc >= l          && check(loc - l)) dps(b, l, loc - l, notVisited);
    if(loc % l           && check(loc - 1)) dps(b, l, loc - 1, notVisited);
    if(loc < l * (l - 1) && check(loc + l)) dps(b, l, loc + l, notVisited);
    if((loc + 1) % l     && check(loc + 1)) dps(b, l, loc + 1, notVisited);
#undef check
}

_Bool isConnected(uint8_t *b, uint8_t l){
    uint16_t loc;
    for(loc = 0; get(b, loc); loc++);

    uint8_t ll = bytesLength(l);
    uint8_t *notVisited = malloc(ll);
    memset(notVisited, 0xFF, ll);
    notVisited[ll - 1] &= (1 << (l * l & 7)) - 1;

    dps(b, l, loc, notVisited);
    _Bool res = !memcmp(notVisited, b, ll);
    free(notVisited);

    return res;
}

_Bool finished(uint8_t *b, uint8_t l, uint8_t *a, uint8_t al, uint8_t *d, uint8_t dl){
    int ctr = 1, ai = 0, di = 0, r = 0;
    for(uint16_t i=0; i < l*l; i++, r=0){
        if(!get(b, i) && (!(i%l) || get(b, i-1))){
            if(ai >= al || a[ai++] != ctr) return 0;
            r = 1;
        }
        if(!get(b, i) && (!(i/l) || get(b, i-l))){
            if(di >= dl || d[di++] != ctr) return 0;
            r = 1;
        }
        if(r) ctr++;
    }

    return ai == al && di == dl;
}

void solve(uint8_t l, uint8_t *a, uint8_t al, uint8_t *d, uint8_t dl){
    uint8_t *stack[l * l + 1], ll = bytesLength(l);
    uint16_t loc[l * l + 1];
    int16_t ctr = 0;
    stack[0] = malloc(ll);
    loc[0] = 0;

    memset(stack[0], 0, ll);
    while(ctr + 1){
        uint16_t i = loc[ctr];
        uint8_t *b = stack[ctr--];

        if(i > l*l + 1 >> 1) continue;

        if(finished(b, l, a, al, d, dl)){
            printBoard(b,l);
            return;
        }

        tgl(b, l, i);
        if((
            !(i % l) ||
            get(b, i-1) ||
            i % l > 2 && !get(b, i-2) && !get(b, i-3))
            &&
            (i < l ||
            get(b, i-l) ||
            i >= 2*l && !get(b, i-2*l))
            &&
            isConnected(b, l)
        ){
            stack[++ctr] = malloc(ll);
            loc[ctr] = i + 1;
            memcpy(stack[ctr], b, ll);
        }

        tgl(b, l, i);
        if((
            i%l < l-2 ||
            !((i+2)%l) && !get(b, i-1) ||
            !((i+1)%l) && !get(b, i-1) && !get(b, i-2))
            &&
            (!get(b, i+l) && !get(b, i+2*l) ||
            !get(b, i-l) && !get(b, i+l) ||
            !get(b, i-l) && !get(b, i-2*l)
        )){
            stack[++ctr] = malloc(ll);
            loc[ctr] = i + 1;
            memcpy(stack[ctr], b, ll);
        }

        free(b);
    }
}

int main(int argc, char **argv){
    uint8_t a[11] = {1,4,7,8,9,11,12,16,17,18,19};
    uint8_t d[11] = {1,2,3,4,5,6,10,12,13,14,15};
    solve(7, a, 11, d, 11);

    return 0;
}
