#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>
#define MaxSize 10

const char *msgs[] = {"0. Quit", "1. Add", "2. Find", "3. Delete", "4. Show"};
const int NMsgs = sizeof(msgs) / sizeof(msgs[0]);

typedef struct Data{
    char *info;
    int busy;
    int key;
}Data;

typedef struct Table{
    int msize;
    int csize;
    Data *item;
}Table;

int getInt(int *);
void setValues(Table *);
int dialog(const char **, int);
int search(Table *, int);
int find(Table *, int);
int insert(Table *, int, char *);
int delete(Table *, int);
int D_Add(Table *);
int D_Find(Table *);
int D_Delete(Table *);
int D_Show(Table *);
int hash(int );
char *getStr();
void delTable(Table *);

int main(){
    Table table = {MaxSize, 0, (Data *) calloc (MaxSize, sizeof(Data))};
    int (*fptr[])(Table *) = {NULL, D_Add, D_Find, D_Delete, D_Show};

    int rc;
    setValues(&table);
    while(rc = dialog(msgs, NMsgs)){
        if(!fptr[rc](&table))
            break;
    }
    printf("That is all bye!\n");
    delTable(&table);
    return 0;
}

int dialog(const char *msgs[], int N){
    char *errmsg = "";
    int rc;
    int i, n;
    do{
        puts(errmsg);
        errmsg = "You are wrong, repeat please!";
        for(i = 0; i < N; ++i)
            puts(msgs[i]);
        puts("Make your choice: --> ");

        n = getInt(&rc);
        if(n==0)
            rc == 0;        
    }while(rc < 0 || rc >= N); 
    return rc;
}

void setValues(Table *ptab){
    if(ptab->csize == 0){
        for(int i = 0; i < MaxSize; ++i){
            ptab->item[i].busy = 0;
            ptab->item[i].key = 0;
            ptab->item[i].info = NULL;
        }
    }
}

int D_Add(Table *ptab){
    int key, n, rc;
    char *info;
    const char *errmsgs[] = {"Ok", "Duplicate key", "Table overflow"};

    printf("Enter key: --> ");
    n = getInt(&key);
    if (n == 0)
        return 0;
    
    printf("Enter info: ");
    info = getStr();

    rc = insert(ptab, key, info);
    printf("rc = %d\n", rc);
    free(info);

    printf("%s:\tkey: %d\n", errmsgs[rc], key);
    return 1;
}

int D_Find(Table *ptab){
    int key, n, rc;
    const char *errmsgs[] = {"Found key", "Not found key"};

    printf("Enter key: --> ");
    n = getInt(&key);
    if (n == 0)
        return 0;

    rc = find(ptab, key);

    printf("%s:\tkey: %d\n", errmsgs[rc], key);
    return 1;
}

int D_Delete(Table *ptab){
    int key, n, rc;
    const char *errmsgs[] = {"Successfully removed", "Not found key"};

    printf("Enter key: --> ");
    n = getInt(&key);
    if (n == 0)
        return 0;

    rc = delete(ptab, key);

    printf("%s:\tkey: %d\n", errmsgs[rc], key);
    return 1;
}

int D_Show(Table *ptab){
    printf("======= TABLE =======\n");
    printf("index| busy | key | information\n------------------------\n");
    for(int i = 0; i < ptab->msize; ++i){
        printf("%-5d|%-5d|%-5d| %s\n", i, ptab->item[i].busy, ptab->item[i].key, ptab->item[i].info);
    }
    return 1;
}

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
