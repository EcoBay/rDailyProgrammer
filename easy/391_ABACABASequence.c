#include <stdio.h>
#include <stdlib.h>

void abacaba(char i){
    if( i == 1 ) printf("a");
    else if(i < 27){
        abacaba(i - 1);
        putchar('a' + i - 1);
        abacaba(i - 1);
    }
}

int main(int argc, char **argv){
    if (argc < 2) return EXIT_FAILURE;
    abacaba(atoi(argv[1])); putchar('\n');
    return 0;
}
