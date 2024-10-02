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

typedef struct myDoubleBlock {
    int nb;
    struct myDoubleBlock* ptr_next; 
    struct myDoubleBlock* ptr_prev; 
}DOUBLEB;

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

MYBLOCK* remove_first(MYBLOCK* head) {
    if (head == NULL) {
        return NULL;
    }
    MYBLOCK* temp = head;
    head = head->ptr_next;
    free(temp);
    return head;
}

MYBLOCK* remove_last(MYBLOCK* head) {
    if (head == NULL) {
        return NULL;
    }
    if (head->ptr_next == NULL) {
        free(head);
        return NULL;
    }
    MYBLOCK* current = head;
    while (current->ptr_next->ptr_next != NULL) {
        current = current->ptr_next;
    }
    free(current->ptr_next);
    current->ptr_next = NULL;
    return head;
}

MYBLOCK* add_last(MYBLOCK* head, int value) {
    MYBLOCK* new_node = create_node(value);
    if (head == NULL) return new_node;

    MYBLOCK* current = head;
    while (current->ptr_next != NULL) {
        current = current->ptr_next;
    }
    current->ptr_next = new_node;
    return head;
}

MYBLOCK* add_first(MYBLOCK* head, int value) {
    MYBLOCK* new_node = create_node(value);
    new_node->ptr_next = head;
    return new_node;
}

MYBLOCK* concatenate_lists(MYBLOCK* list1, MYBLOCK* list2) {
    if (list1 == NULL) return list2;
    if (list2 == NULL) return list1;

    MYBLOCK* current = list1;
    while (current->ptr_next != NULL) {
        current = current->ptr_next;
    }
    current->ptr_next = list2;
    return list1;
}

MYBLOCK* applyfunc(MYBLOCK* head, int (*func)(int)) {
    MYBLOCK* new_list = NULL;
    MYBLOCK* current = head;

    while (current != NULL) {
        new_list = add_last(new_list, func(current->nb));
        current = current->ptr_next;
    }
    return new_list;
}

DOUBLEB* create_double_node(int value) {
    DOUBLEB* new_node = (DOUBLEB*)malloc(sizeof(DOUBLEB));
    new_node->nb = value;
    new_node->ptr_next = NULL;
    new_node->ptr_prev = NULL;
    return new_node;
}

DOUBLEB* convert_to_doubly_linked_list(MYBLOCK* head) {
    if (head == NULL) {
        return NULL;
    }
    DOUBLEB* double_head = create_double_node(head->nb);
    DOUBLEB* current = double_head;
    head = head->ptr_next;
    while (head != NULL) {
        DOUBLEB* new_node = create_double_node(head->nb);
        current->ptr_next = new_node;
        new_node->ptr_prev = current;
        current = new_node;
        head = head->ptr_next;
    }
    return double_head;
}

DOUBLEB* create_circular_doubly_list(int n) {
    if (n <= 0) {
        return NULL;
    }
    DOUBLEB* head = create_double_node(1);
    DOUBLEB* current = head;
    for (int i = 2; i <= n; i++) {
        DOUBLEB* new_node = create_double_node(i);
        current->ptr_next = new_node;
        new_node->ptr_prev = current;
        current = new_node;
    }
    current->ptr_next = head;
    head->ptr_prev = current;
    return head;
}

int main(){
    MYBLOCK* myList = create_list(10);
    int myListSize = lListSize(myList);
    printf("myListSize : %d \n", myListSize);
    displayListFields(myList);

    myList = add_first(myList, 0);
    myList = add_last(myList, 6);
    printf("myListSize : %d \n", myListSize);
    displayListFields(myList);

    myList = remove_first(myList);
    myList = remove_last(myList);
    printf("myListSize : %d \n", myListSize);
    displayListFields(myList);
    
    return 0;
}