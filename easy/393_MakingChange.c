#include <stdio.h>

int denom[] = {500, 100, 25, 10, 5, 1};

int change(int x, int *c){
    int t = c[0];
    if(t == 1) return x;
    else return x / t + change(x % t, &c[1]);
}

int main(int argc, char **argv){
    printf("change(0) => %d\n", change(0, denom));
    printf("change(12) => %d\n", change(12, denom));
    printf("change(468) => %d\n", change(468, denom));
    printf("change(123456) => %d\n", change(123456, denom));
}
