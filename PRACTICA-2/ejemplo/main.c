#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <errno.h>
#include <string.h>
#include <pthread.h>

void *saluda()
{
    printf("hola mundo \n");
    pthread_exit((void*)NULL);//
}

int main(){
   //creo la variable donde guardp el id del hilo
   pthread_t id_hilo;
   //Crear el hilo
   pthread_create(&id_hilo,NULL,(void*)saluda,NULL);
   //esperar al hilo
   pthread_join(id_hilo,(void**)NULL);
   //matar al a.out
   exit(EXIT_SUCCESS);



}