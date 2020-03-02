//FOLHA 2 - p2b.c
//FILE COPY
//USAGE: copy source destination

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>

#define BUFFER_SIZE 512

int main(int argc, char *argv[])
{
	int fd1, fd2 = -1, nr;
	unsigned char buffer[BUFFER_SIZE];
    int newFile;

	if (argc != 2 && argc != 3) {
		printf("Usage: %s <source>\n", argv[0]);
		return 1;
	}
    else newFile = argc - 2;

    fd1 = open(argv[1], O_RDONLY);

    if (fd1 == -1) {
        perror(argv[1]);
        return 2;
    }

    if(newFile){
        fd2 = open(argv[2], O_WRONLY | O_CREAT | O_EXCL, 0644);
        if (fd2 == -1) {
            perror(argv[2]);
            return 3;
        }
     
        dup2(fd2, STDOUT_FILENO);
    }
    

    while((nr = read(fd1, buffer, BUFFER_SIZE)) > 0){
        write(STDOUT_FILENO, buffer, nr);
    }
    
    close(fd1);
	
	return 0;
}

