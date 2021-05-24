#include <stdio.h>
#include <stdlib.h>

int one(int a, int b) {return 0;}
int rd3(int a, int b) {return rand() % 3;}
int chg(int a, int b) {return 3 - a - b;}
int rnd(int a, int b) {return rand() % 2 ? a : chg(a, b);} 
int stk(int a, int b) {return a;}
int frk(int a, int b) {return b == 1 ? 0 : 1;}

float rungame(int n, int (*str1)(int, int), int (*str2)(int, int)){
    double score = 0.0;
    for ( int i = 0; i < n; i++){
        int c = rand() % 3;
        int a = str1(0, 0);
        int b = c == a ?
            (a + (rand() % 2) + 1) % 3:
            chg(a, c);
        int d = str2(a, b);
        if (c == d) score += 1.0 / n;
    }
    return score;
}

float gna(int n){
    double score = 0.0;
    _Bool ali = 0;
    for ( int i = 0; i < n; i++ ){
        double s = ali ?
            rungame(1, &one, &one):
            rungame(1, &one, &chg);
        ali = s > 0.99 ? ali : ali ^ 1;
        score += s / n;
    }
    return score;
}

int main(int argc, char** argv){
    printf("Alice: %.2f%\n", rungame(1000, &one, &one) * 100);
    printf("  Bob: %.2f%\n", rungame(1000, &one, &chg) * 100);
    printf("Carol: %.2f%\n", rungame(1000, &rd3, &rnd) * 100);
    printf(" Dave: %.2f%\n", rungame(1000, &rd3, &stk) * 100);
    printf(" Erin: %.2f%\n", rungame(1000, &rd3, &chg) * 100);
    printf("Frank: %.2f%\n", rungame(1000, &one, &frk) * 100);
    printf(" Gina: %.2f%\n", gna(1000) * 100);
    return 0;
}
