#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <errno.h>
#include <string.h>
#include <pthread.h>

void* mostrarHilo(char *nf){
    FILE* fich=fopen(nf,"r");
    if(fich==NULL){
        printf("error al abrir el fichero\n");
        exit(EXIT_FAILURE);
    }
    int cont=0;
    char cadena[200];
    while(fgets(cadena,200,fich)){
        cont++;
    }
    printf("soy el fichero:%s, y tengo:%i lineas\n",nf,cont);
    fclose(fich);
    int *retorno=(int*)malloc(sizeof(int));
    (*retorno)=cont;
    pthread_exit((void*)retorno);
}


int main(int argc,char **argv){
    if(argc<1){
        printf("error en linea de argumentos\n");
        exit(EXIT_FAILURE);
    }
        pthread_t id_hilo[argc-1];

        for(int i=0;i<argc-1;i++){
             if(pthread_create(&id_hilo[i],NULL,(void*)mostrarHilo,(void*)argv[i+1])!=0){
                printf("error\n");
                exit(EXIT_FAILURE);
             }
             
        }
        int *valorRecogido;
        int suma=0;
        for(int j=0;j<argc-1;j++){
           if(pthread_join(id_hilo[j],(void**)&valorRecogido)!=0)
           {
            printf("error\n");
            exit(EXIT_FAILURE);
           }
              suma+=(*valorRecogido);
           printf("he recogido %d lineas y la suma total  es de:%d \n",(*valorRecogido),suma);
            free(valorRecogido);
        }
        
           exit(EXIT_SUCCESS);


}