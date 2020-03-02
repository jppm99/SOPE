#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUF_SIZE 256

FILE* source_fp;
FILE* destination_fp;

void close_files(){
    fclose(source_fp);
    fclose(destination_fp);
}

int main(int argc, char** argv){

    if(argc != 3){
        printf("wrong arg count");
        return -1;
    }

    if(!strcmp(argv[1], "copy")){
        printf("wrong operation");
        return -1;
    }

    source_fp = fopen(argv[2], "r");
    destination_fp = fopen(argv[3], "w");
    atexit(close_files);

    void * buf = malloc(BUF_SIZE);
    int size;

    while((size = fread(buf, 1, BUF_SIZE, source_fp))){
        fwrite(buf, 1, size, destination_fp);
    }

    free(buf);

    return 0;
}
