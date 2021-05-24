#include <stdio.h>
#include <stdlib.h>
#include <string.h>

_Bool same_necklace(char *a, char *b){
    char l = strlen(a), r = 0;
    if(l != strlen(b)) return 0;

    char *t = malloc(2 * l + 1);
    strcpy(t, a); strcpy(&t[l], a);
    t[2 * l] = 0;

    if(strstr(t, b)) r = 1; else r = 0;

    free(t);
    return r;
}

char repeats(char *a){
    char l = strlen(a), r = 0;
    if (!l) return 1;

    char *t = malloc(2 * l + 1);
    strcpy(t, a); strcpy(&t[l], a);

    for(int i = l; i; i--){
        t[i + l] = 0;
        if(!strcmp(a, &t[i])) r++;
    }

    free(t);
    return r;
}

_Bool exist(char a[200000][30], char *b, int n){
    int l = 0, r = n - 1;
    while(l <= r){
        int m = l + (r - l) / 2, t = strcmp(b, a[m]);

        if(t > 0) l = m + 1;
        else if (t < 0) r = m - 1;
        else return 1;
    }
    return 0;
}

char **match(){
    int l = 0;
    char a[200000][30];

    char **r = malloc(4);
    for(int i = 0; i < 4; i++) r[i] = malloc(31);

    char t[30];
    while(scanf("%s", t) != EOF){
        if(strlen(t) - repeats(t) + 1 >= 4) strcpy(a[l++], t);
    }

    for(int i = 0; i < l; i++){
        char ll = strlen(a[i]), *tt = malloc(2 * ll + 1), k = 1;
        tt[2 * ll] = 0;
        strcpy(tt, a[i]); strcpy(&tt[ll], a[i]);

        strcpy(r[0], a[i]);

        for(int j = ll - 1; j; j--){
            tt[j + ll] = 0;
            if(exist(a, &tt[j], l) && k++ < 4) strcpy(r[k - 1], &tt[j]);
        }

        if(k == 4) break;
    }

    return r;
}


int main(int argc, char **argv){
    // printf("%d\n", same_necklace("aa", "aaa"));
    // printf("%d\n", repeats("abcabcabc"));
    char **a = match();
    for(int i = 0; i < 4; i++){
        printf("%s\n", a[i]);
    }
    return 0;
}
