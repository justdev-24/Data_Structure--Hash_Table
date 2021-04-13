#include "header.h"

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
