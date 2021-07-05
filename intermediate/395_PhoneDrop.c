#include <stdio.h>
#include <stdlib.h>
#include <string.h>

unsigned int phoneDrop(const unsigned int n, const unsigned int h, unsigned int **mem){
    unsigned int r, a, b;

    if(!mem){
        mem = malloc(n * sizeof(unsigned int*));
        for(int i = 0; i < n; i++){
            mem[i] = malloc(h * sizeof(unsigned int));
            memset(mem[i], 0, h * sizeof(unsigned int));
            mem[i][0] = 1;
        }
        for(int i = 0; i < h; i++)
            mem[0][i] = i + 1;
    }

    if(r = mem[n-1][h-1]) return r;

    for(int i = 1; i < h; i++){
        #define min(x, y) (y ^ ((x ^ y) & -(x < y)))
        #define max(x, y) (x ^ ((x ^ y) & -(x < y)))
        a = phoneDrop(n - 1, i, mem);
        b = phoneDrop(n, h - i, mem);
        r = max(r, min(a, b) + 1);
    }

    return mem[n-1][h-1] = r;
}

unsigned int phoneDrop_inf(unsigned int h){
    int ctr;
    for(ctr = 0; h; h >>= 1, ctr++);
    return ctr;
}

int main(int argc, char **argv){
    printf("%u\n", phoneDrop(1,100, NULL));
    printf("%u\n", phoneDrop(2,100, NULL));
    printf("%u\n", phoneDrop(3,100, NULL));
    printf("%u\n", phoneDrop(1,1, NULL));
    printf("%u\n", phoneDrop(2,456, NULL));
    printf("%u\n", phoneDrop(3,456, NULL));
    printf("%u\n", phoneDrop(4,456, NULL));
    printf("%u\n", phoneDrop(2,789, NULL));
    printf("%u\n", phoneDrop(3,789, NULL));
    printf("%u\n", phoneDrop(4,789, NULL));
    return 0;
}
