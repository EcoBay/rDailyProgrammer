#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char warmup(char c, int a){
    if ( c >= 'a' && c <= 'z')
        return ( c - 'a' + a) % 26 + 'a';
    else if ( c >= 'A' && c <= 'Z' )
        return ( c - 'A' + a ) % 26 + 'A';
    else
        return c;
}

void ceasar(char **plain, char **cipher, int a){
    int l = strlen(*plain);

    *cipher = malloc(l + 1);
    strcpy(*cipher, *plain);
    (*cipher)[l] = '\0';

    for (int i = 0; i < l; i++)
        (*cipher)[i] = warmup((*cipher)[i], a);
}

void decode(char **cipher, char **plain){
    int max = 0;
    int frq[26] = {
        3,-1,1,1,4,
        0,0,2,2,-5,
        -2,1,0,2,3,
        0,-6,2,2,3,
        1,-1,0,-5,0,
        -7
    };

    for (int i = 0; i < 26; i++){
        int score = 0;
        char *res;
        ceasar(cipher, &res, i);

        for (int j = 0; j < strlen(res); j++){
            char c;

            if ( res[j] >= 'A' && res[j] <= 'Z')
                c = res[j] - 'A'; 
            else if ( res[j] >= 'a' && res[j] <= 'z')
                c = res[j] - 'a'; 
            else continue;

            score += frq[c];
        }

        if (score > max){
            (*plain) = res;
            max = score;
        } else free(res);
    }
}

int main(int argc, char** argv){
    char *plain = "jgorevxumxgsskx";
    char *cipher;

    // ceasar(&plain, &cipher, 20);
    decode(&plain, &cipher);
    printf("%s\n", cipher);

    return 0;
}
