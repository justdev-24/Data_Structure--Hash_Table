#include "header.h"

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
