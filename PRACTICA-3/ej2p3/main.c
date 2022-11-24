#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <errno.h>
#include <string.h>
#include <pthread.h>

 int par=0;
 int impar=0;
pthread_mutex_t semaforo1;
pthread_mutex_t semaforo2;
 void* funcionhilo(int *num){
    int suma=0;
    for(int i=0;i<5;i++){
        suma+=rand()%10;
    }
    if ((*num)%2==0){
         if(pthread_mutex_lock(&semaforo1)!=0){
            printf("error\n");
            exit(EXIT_FAILURE);
        }
        
        par+=suma;
         if(pthread_mutex_unlock(&semaforo1)!=0){
            printf("error\n");
             exit(EXIT_FAILURE);
        }
    }
    else{
         if(pthread_mutex_lock(&semaforo2)!=0){
            printf("error\n");
            exit(EXIT_FAILURE);
        }
        impar+=suma;
         if(pthread_mutex_unlock(&semaforo2)!=0){
            printf("error\n");
             exit(EXIT_FAILURE);
        }
    }
        int *retorno=(int*)malloc(sizeof(int));
    (*retorno)=suma;
    pthread_exit((void*)retorno);

 }

 int main(int argc,char ** argv){
    if(argc!=2){
        printf("error en linea de argumentos\n");
        exit(EXIT_FAILURE);
    }
    srand(time(NULL));

     if(pthread_mutex_init(&semaforo1,NULL)!=0){
            printf("error\n");
              exit(EXIT_FAILURE);
        }
         if(pthread_mutex_init(&semaforo2,NULL)!=0){
            printf("error\n");
              exit(EXIT_FAILURE);
        }
    int n=atoi(argv[1]);
    int v[n];
    pthread_t hilo[n];
    for(int i=0;i<n;i++){
         v[i]=i+1;
        if(pthread_create(&hilo[i],NULL,(void*)funcionhilo,(void*)&v[i])!=0){
            printf("error al crear un hilo\n");
            exit(EXIT_FAILURE);
        }
    }
    int sumapar=0,sumaimpar=0;
    int *valorRecogido;
        for(int j=0;j<n;j++){
           if(pthread_join(hilo[j],(void**)&valorRecogido)!=0)
           {
            printf("error\n");
            exit(EXIT_FAILURE);
           }
           printf("el valor recogido del hilo %i es %i\n ",j+1,(*valorRecogido));
           if((j+1)%2==0){
            sumapar+=*valorRecogido;
           }
           else{
            sumaimpar+=*valorRecogido;
           }
           free(valorRecogido);
        }
          if(pthread_mutex_destroy(&semaforo1)!=0){
            printf("error\n");
             exit(EXIT_FAILURE);
        }
          if(pthread_mutex_destroy(&semaforo2)!=0){
            printf("error\n");
             exit(EXIT_FAILURE);
        }
        printf("el valor de variable recogida par es: %i\n",sumapar);
         printf("el valor de variable recogida impar es: %i\n",sumaimpar);
        printf("el valor de la variable global par es: %i \n",par);
         printf("el valor de la variable global impar es: %i \n",impar);

 }


