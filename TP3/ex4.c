#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/wait.h> 
#include <string.h>

int p = 0;
char* str = "hello world";

//adapted from og exercise
//father proccess forks each letter written (f-s-f-s-f-s...)
int main(void) {

    while(p < strlen(str)){
        char c = str[p++];
        write(STDOUT_FILENO,&c,1);

        if(fork() > 0){
            p++;
            wait(NULL);
        }
        else{
            if(p < strlen(str)){
                char c = str[p];
                write(STDOUT_FILENO,&c,1);
                exit(0);
            }
        }
    }

    printf("\n");

    return 0;
} 