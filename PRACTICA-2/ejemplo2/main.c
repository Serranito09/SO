#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <errno.h>
#include <string.h>
#include <pthread.h>

void *saluda(char *cadena)
{
    for(int i=0;i<strlen(cadena);i++){
        printf("%c\n",cadena[i]);
        sleep(1);
    }
    pthread_exit((void*)NULL);//
}

int main(){
    char cadena[]="HOLA",cadena2[]="MUNDO";
   //creo la variable donde guardp el id del hilo
   pthread_t id_hilo,id_hilo2;
   //Crear el hilo
   pthread_create(&id_hilo,NULL,(void*)saluda,(void*)cadena);
     pthread_create(&id_hilo2,NULL,(void*)saluda,(void*)cadena2);
   //esperar al hilo
   pthread_join(id_hilo,(void**)NULL);
   pthread_join(id_hilo2,(void**)NULL);
   //matar al a.out
   exit(EXIT_SUCCESS);



}