#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

int main(){
    int fd = open("test.txt", O_RDWR);
    
    if (fd==-1){
        perror("error myfd");
        return 1;
    }

    struct stat mystat;

    if (fstat(fd, &mystat)==-1){
        perror("error mystat");
        return 1;
    }

    size_t myfilesize = mystat.st_size;
    printf("myfilesize : %ld \n", myfilesize);

    char *Mmap = mmap(NULL, myfilesize, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);

    if (Mmap==MAP_FAILED){
        perror("error mymapping");
        close(fd);
        return 1;
    }

    for(size_t i = 0; i < myfilesize/2; i++){
        char temp = Mmap[i];
        Mmap[i] = Mmap[myfilesize - i - 1];
        Mmap[myfilesize - i - 1] = temp;
    }

    if(munmap(Mmap, myfilesize) == -1){
        perror("error myunmap");
        close(fd);
        return 1;
    }

    close(fd);

    return 0;
}