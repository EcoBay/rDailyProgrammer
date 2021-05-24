#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <math.h>

#define countDigits(x) ((int) (log10(x) + 1))

char *reverse(char *a, int n){
    char *rev = malloc(n + 1);
    strcpy(rev, a);
    rev[n] = '\0';

    char *end = rev + strlen(rev) - 1;
    char *str = rev;

    while (str < end){
        *str ^= *end;
        *end ^= *str;
        *str ^= *end;

        str++;
        end--;
    }

    return rev;
}

uint64_t nextPal(uint64_t x){
    int len = countDigits(x);
    int mid = ceil(len / 2.0);

    char val[len + 1];
    sprintf(val, "%llu", x);
    val[len] = '\0';


    char *head = malloc(mid + 1), *tail = malloc(mid + 1);
    memcpy(head, val, mid);
    head[mid] = '\0';
    memcpy(tail, &val[len - mid], mid);
    tail[mid] = '\0';

    char *rev = reverse(head, mid);

    if(strcmp(rev, tail) <= 0){
        uint64_t t = atoll(head) + 1;
        int l = countDigits(t);

        free(head);
        head = malloc(l + 1);
        sprintf(head, "%llu", t);
        head[l] = '\0';

        len += l > mid;

        free(rev);
        rev = reverse(head,l);
    }

    int left = ceil(len / 2.0), right = len / 2;
    sprintf(head, "%.*s%.*s\n", left, head, right, &rev[strlen(rev) - right]);

    uint64_t ret = atoll(head);

    free(tail);
    free(rev);
    free(head);

    return ret;
}

int main(int argc, char** argv){
    int c;
    uint64_t *i;

    if (argc < 2) {
        c = 1;
        uint64_t t[1] = {pow(3, 39)};
        i = t;
    } else {
        c = argc - 1;
        uint64_t t[argc - 1];
        for(int i = 1; i < argc; i++) t[i - 1] = atoll(argv[i]);
        i = t;
    }

    for(int j = 0; j < c; j++) printf("%llu\n", nextPal(i[j]));
    return 0;
}
