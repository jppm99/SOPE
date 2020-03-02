#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>

#define BUFFER_SIZE 256

int main(int argc, char** argv){
    if(argc != 2){
        printf("arg error: %s <output file>\n", argv[0]);
        return -1;
    }

    int fd = open(argv[1], O_WRONLY | O_CREAT | O_EXCL, 0644);

    void* buf = malloc(BUFFER_SIZE);
    int rb;
    printf("Input wtv u want m8, end with ctrl+z\n");
    while(rb = read(STDIN_FILENO, buf, BUFFER_SIZE)){
        write(fd, buf, rb);
    }

    free(buf);
    close(fd);

    return 0;
}
