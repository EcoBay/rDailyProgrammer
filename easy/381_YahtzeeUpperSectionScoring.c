#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define HASHSIZE 0x10000

struct nlist{
    struct nlist *next;
    int key;
    long long val;
};

int hash(int x){
    return x & (HASHSIZE - 1);
}

void score(struct nlist **dict, int key){
    struct nlist **p = &dict[hash(key)];
    while(*p && (*p) -> key != key){
        p = &((*p) -> next);
    }
    if(!*p){
        *p = malloc(sizeof(struct nlist));
        (*p) -> key = key;
        (*p) -> val = 0;
        (*p) -> next = NULL;
    } 
    (*p) -> val += key;
}

long long getMaxVal(struct nlist **dict){
    long long max = 0;
    for(int i = 0; i < HASHSIZE; i++){
        struct nlist *p = dict[i];
        while(p){
            max = p -> val > max ? p -> val : max;
            p = p -> next;
        }
    }
    return max;
}

void destroy(struct nlist **dict){
    for(int i =0; i < HASHSIZE; i++){
        struct nlist *p = dict[i];
        struct nlist *t = p;
        while(p){
            p = p -> next;
            free(t);
            t = p;
        }
    }
}

int yahtzee_upper(int roll[], int l){
    struct nlist **dict = malloc(HASHSIZE * sizeof(struct nlist*));
    memset(dict, 0, HASHSIZE * sizeof(struct nlist*));
    printf("yahtzee_upper([");
    for(int i = 0; i < l; i++){
        printf("%d", roll[i]);
        if(((i+1)%l)) printf(", ");
        score(dict, roll[i]);
    }
    printf("]) => %lld\n", getMaxVal(dict));
    destroy(dict);
}

int main(int argc, char **argv){
    if(argc == 2 && !strcmp(argv[1], "-")){
        struct nlist **dict = malloc(HASHSIZE * sizeof(struct nlist*));
        memset(dict, 0, HASHSIZE * sizeof(struct nlist*));
        int a;
        while(scanf("%d", &a) != EOF){
            score(dict, a);
        }

        printf("%lld\n", getMaxVal(dict));
    } else {
        int test1[5] = {2, 3, 5, 5, 6};
        yahtzee_upper(test1, 5);
        int test2[5] = {1, 1, 1, 1, 3};
        yahtzee_upper(test2, 5);
        int test3[5] = {1, 1, 1, 3, 3};
        yahtzee_upper(test3, 5);
        int test4[5] = {1, 2, 3, 4, 5};
        yahtzee_upper(test4, 5);
        int test5[5] = {6, 6, 6, 6, 6};
        yahtzee_upper(test5, 5);
        int test6[20] = {
            1654, 1654, 50995, 30864, 1654,
            50995, 22747, 1654, 1654, 1654,
            1654, 1654, 30864, 4868, 1654,
            4868, 1654, 30864, 4868, 30864
        };
        yahtzee_upper(test6, 20);
    }

    return 0;
}
