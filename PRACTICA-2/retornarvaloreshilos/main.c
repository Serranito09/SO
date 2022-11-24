//implementar un programa que reciba por linea de argumentos el numero de hilos a crear.cada hilo debera generar un  numero aleatorio modulo 10 e imprimir 
//soy el hilo y el numeor aleatorio generado es tal y ademas cada hilo debera retornar al proceso principal el numero aletorio generado
//por el ultimo el proceso principal ,debera no solo immprimir el numero que recgoe cada hilo si no que ademas imprimira la suma de cada ellos


#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <errno.h>
#include <string.h>
#include <pthread.h>


void *funcionhilo(){
    int n=rand()%10;
    printf("soy el hilo %ld y he generado un %d\n",pthread_self(),n);
    //retorno 
    int *retorno=(int*)malloc(sizeof(int));
    (*retorno)=n;
    pthread_exit((void*)retorno);
}

int main(int argc,char **argv){
    if(argc!=2){
        printf("error en linea de argumentos\n");
        exit(EXIT_FAILURE);
    }
    srand(time(NULL));
    int n=atoi(argv[1]);
    pthread_t idhilos[n];
    for(int i=0;i<n;i++){
        if(pthread_create(&idhilos[i],NULL,(void*)funcionhilo,NULL)!=0){
            printf("erroh al crear un hilo\n");
            exit(EXIT_FAILURE);
        }
    }
    int *valorRecogido;
    int suma=0;
    for(int i=0;i<n;i++){
        if(pthread_join(idhilos[i],(void**)&valorRecogido)!=0){
            printf("error...\n");
            exit(EXIT_FAILURE);
        }
        printf("he recogido un %d\n",(*valorRecogido));
        suma+=(*valorRecogido);
        free(valorRecogido);
    }
    printf("la suma es %d\n",suma);
    exit(EXIT_SUCCESS);
}
