#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <time.h>

void clear(){
    #if defined(__linux__) || defined(__unix__) || defined(__APPLE__)
        system("clear");
    #endif

    #if defined(_WIN32) || defined(_WIN64)
        system("cls");
    #endif
}

//obrigatorio numero no fim se houver args
void ex4(int argc, char** argv){
    char * nome = calloc(50, sizeof(char));
    int numero;

    for(int i = 1; i < argc - 1; i++){
        nome = strcat(nome, " ");
        nome = strcat(nome, argv[i]);
    }

    if(argc > 2) numero = atoi(argv[argc-1]);

    if(numero < 1) numero = 1;

    for(int n = 0; n < numero; n++) printf("Hello%s !\n", nome);
}

void ex5(char** envp){
    for(int i = 0; envp[i] != NULL; i++){
        printf("%s\n", envp[i]);
    }
}

void ex5b(char** envp){
    char* user = NULL;

    for(int i = 0; envp[i] != NULL; i++){
        if(!strncmp("USER=", envp[i], 5)){
            user = envp[i] + 5;
            break;
        }
    }

    printf("Hello %s !\n", user);
}

void ex5c(){
    char* user = getenv("USER");

    printf("Hello %s !\n", user);
}

void ex6(int argc, char** argv){
    #define BUF_LENGTH 256 

    FILE *src, *dst;
    char buf[BUF_LENGTH];

    if(argc != 3){
        perror("usage: nome_do_executável file1 file2");
        exit(3);
    }
    
    if ( ( src = fopen( argv[1], "r" ) ) == NULL ){
        printf("Error: %s\n", strerror(errno));
        exit(1);
    }
    
    if ( ( dst = fopen( argv[2], "w" ) ) == NULL ){
        printf("Error: %s\n", strerror(errno));
        exit(2);
    }

    while( ( fgets( buf, BUF_LENGTH, src ) ) != NULL ){
        fputs( buf, dst );
    }

    fclose( src );
    fclose( dst );
    exit(0); // zero é geralmente indicativo de "sucesso" 
}

void ex7a1(){ printf("this is handler 1\n"); }
void ex7a2(){ printf("this is handler 2\n"); }
void ex7(){
    atexit(ex7a1);
    atexit(ex7a2);
    
    printf("main done\n");

    return;
}

void ex8(int argc, char** argv){
    if(argc != 3) exit(1);

    int max = atoi(argv[1]), obj = atoi(argv[2]);

    srand(time(NULL));
    long int it = 0;
    int n;

    struct timespec start, finish;
    clock_gettime(CLOCK_MONOTONIC, &start);
    clock_t begin = clock();


    //try to get num
    while(n != obj){
        n = rand() % max;

        clear();
        
        printf("It: %ld\n", it++);
        printf("rand: %d\n", n);
        printf("Goal: %d\n", obj);

    }

    clock_gettime(CLOCK_MONOTONIC, &finish);
    clock_t end = clock();

    double cpu_time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
    double real_time_spent = (finish.tv_sec - start.tv_sec); // seconds
    real_time_spent += (finish.tv_nsec - start.tv_nsec) * 1e-9; // adds nanoseconds

    printf("\n***** CPU took %f seconds *****\n", cpu_time_spent);
    printf("***** Real time %f seconds *****\n", real_time_spent);
}

int main(int argc, char** argv, char** envp)
{   
    ex8(argc, argv);

    return 0;
} 
