#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/wait.h>

int data = 1;
int dataNotInit;
int main(){
    int status;
    __pid_t pid = getpid();
    char pid_str[10];
    sprintf(pid_str, "%d", pid);
    char *args[] = {"/usr/bin/pmap", "-X", pid_str, NULL};
    printf("Hello World!\n");
    char *str = "Hello World"; 
    int *heap = (int*) malloc(sizeof(int));
    int stack = 2;
    void *Mmap = mmap(NULL, sizeof(int), PROT_READ | PROT_WRITE, MAP_ANONYMOUS | MAP_PRIVATE, -1, 0 );

    printf("Adresse mémoire DATA : %p\n", (void*)&data);
    printf("Adresse mémoire BSS : %p\n", (void*)&dataNotInit);
    printf("Adressse mémoire STR : %p\n", (void*)str);
    printf("Adressse mémoire Heap : %p\n", (void*)heap);
    printf("Adresse mémoire Stack : %p\n", (void*)&stack);
    printf("Adresse mémoire Main Function: %p\n", (void*)main);
    printf("Adresse mémoire LibC Function %p\n", (void*)printf);
    printf("Adresse mémoire MMap: %p\n", (void*)Mmap);
    printf("Commande à utiliser : pmap -X %d\n", pid);
    pid = fork();
    if (pid==0){
        execv("/usr/bin/pmap", args);
    }
    else if (pid>0){
        waitpid(pid, &status, 0);
    }

}