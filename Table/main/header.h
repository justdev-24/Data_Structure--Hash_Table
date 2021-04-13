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
