#include "header.h"

int hash(int k){
    int h = k % MaxSize;
    return h;
}

int search(Table *ptab, int k){
    int j = hash(k);
    int p = 1;          //Шаг перемешивание
    int n = 0;
    while (ptab->item[j].busy != 0 && n < ptab->msize) {
        if(ptab->item[j].busy == 1 && ptab->item[j].key == k)
            return j;
        j = (j + p) % ptab->msize;
        n = n + 1;
    }
    return -1;
}

int insert(Table *ptab, int k, char *info){
    int j = hash(k);
    int p = 1;          //Шаг перемешивание
    int n = 0;
    int res = search(ptab, k);

    if (res >= 0)
        return 1;
    while (ptab->item[j].busy == 1 && n < ptab->msize) {
        j = (j + p) % ptab->msize;
        n = n + 1;
    }
    
    if (n < ptab->msize) {
        ptab->item[j].key = k;
        ptab->item[j].busy = 1;
        ptab->item[j].info = strdup(info);
        return 0;
    }
    return 2;
}

int delete(Table *ptab, int k){
    int res = search(ptab, k);
    if (res < 0)
        return 1;
    else{
        ptab->item[res].busy = -1;
        ptab->item[res].info = NULL;
        return 0;
    }
}

int find(Table *ptab, int k){
    int res = search(ptab, k);
    if(res < 0)
        return 1;
    return 0;
}

int getInt(int *a){
    int n;
    do{
        n = scanf("%d", a);
        if(n<0)
            return 0;
        else if(n==0){
            puts("Error input, repeat please!");
            scanf("%*c");
        }
    }while(n == 0);
    return 1;
}

char *getStr(){
    char *ptr = (char *) malloc(1);
    char buf[81];
    int n, len = 0;
    *ptr = '\0';
    do {
        n = scanf(" %80[^\n]", buf);
        if (n == 0)
            scanf("%*c");
        else {
            len += strlen(buf);
            ptr = (char *) realloc(ptr, len + 1);
            strcat(ptr, buf);
        }
    } while (n < 1);
    return ptr;
}


void delTable(Table *ptab){
    for(int j = 0; j < ptab->msize; ++j)
        free(ptab->item);
    ptab->csize = 0;
}
