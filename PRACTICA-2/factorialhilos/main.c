#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <errno.h>
#include <string.h>
#include <pthread.h>

void *factorial(char *num){
    int n=atoi(num);
    int fact=1;
    for(int i=1;i<=n;i++){
        fact=fact*i;
    }
    printf("el factorial de:%i es:%i\n",n,fact);
}

int main(int argc,char **argv){
    if(argc<=1){
        printf("error en la linea de argumentos\n");
        exit(EXIT_FAILURE);
    }
    pthread_t id_hilo[argc-1];
    for(int i=0;i<argc-1;i++){
        pthread_create(&id_hilo[i],NULL,(void*)factorial,(void *)argv[i+1]);
    }
    for(int j=0;j<argc-1;j++){
        pthread_join(id_hilo[j],NULL);
    }
    exit(EXIT_SUCCESS);
}