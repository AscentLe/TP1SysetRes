#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/wait.h>

const int data = 1;
int dataInit0 = 0;
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

    printf("Memory address DATA : %p\n", (void*)&data);
    printf("Memory address BSS : %p\n", (void*)&dataInit0);
    printf("Memory address STR : %p\n", (void*)str);
    printf("Memory address Heap : %p\n", (void*)heap);
    printf("Memory address Stack : %p\n", (void*)&stack);
    printf("Memory address Main Function: %p\n", (void*)main);
    printf("Memory address LibC Function %p\n", (void*)printf);
    printf("Memory address MMap: %p\n", (void*)Mmap);
    printf("command used : pmap -X %d\n", pid);
    pid = fork();
    if (pid==0){
        execv("/usr/bin/pmap", args);
    }
    else if (pid>0){
        waitpid(pid, &status, 0);
    }

}