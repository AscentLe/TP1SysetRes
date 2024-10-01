#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

typedef struct myBlock {
    int nb;
    struct myBlock *ptr_next;
}MYBLOCK;

MYBLOCK* create_node(int num){
    MYBLOCK* new_node = (MYBLOCK*) malloc(sizeof(MYBLOCK));
    new_node->nb = num;
    new_node->ptr_next = NULL;
    return new_node;
}

MYBLOCK* create_list(int n){
    MYBLOCK* head = create_node(0);
    MYBLOCK* current = head;
    for(int i = 1; i < n; i++){
        current->ptr_next = create_node(i);
        current = current->ptr_next;
    }
    return head;
}

int lListSize(MYBLOCK* listHead){
    MYBLOCK* current = listHead;
    int size =0;
    while(current!=NULL){
        size++;
        current = current->ptr_next;
    }
    return size;
}

void displayListFields(MYBLOCK* listHead){
    MYBLOCK* current = listHead;
    while(current!=NULL){
        printf("<%p> %d - ", current, current->nb);
        current = current->ptr_next;
    }
}

//sucre syntaxique

int main(){
    MYBLOCK* myList = create_list(10);
    int myListSize = lListSize(myList);

    printf("myListSize : %d \n", myListSize);
    displayListFields(myList);

    return 0;
}