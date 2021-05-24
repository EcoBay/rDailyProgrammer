#include <stdio.h>
#include <stdlib.h>

void flip(_Bool **S, char X){ (*S)[X % 64] ^= 1; }

_Bool *createTable(){
    _Bool *a = malloc(64);
    for(int i = 0; i < 64; i++) a[i] = rand() % 2;
    return a;
}

char prisoner1(_Bool *S, char X){
    for(int i = 0 ; i < 64; i++) X ^= i * S[i];
    return X;
}

char prisoner2(_Bool *S){ return prisoner1(S, 0); }

_Bool solve(_Bool *S, char X){
    flip(&S, prisoner1(S, X));
    return prisoner2(S) == X;
}

int main(int argc, char **argv){
    for(int i = 0; i < 10; i++){
        _Bool *table = createTable();
        char X = rand() % 64;
        printf("%d\n", solve(table, X));

        free(table);
    }
}
