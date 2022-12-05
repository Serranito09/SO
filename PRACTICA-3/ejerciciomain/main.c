#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <errno.h>
#include <string.h>
#include <signal.h>
#include <pthread.h>
#include <semaphore.h>

int global;
sem_t a;
sem_t b;


void *sumador(){
	sem_wait(&a);
	global ++;
	printf("global vale %d\n",global);
	sem_post(&b);
}

void *restador(){
	sem_wait(&b);
	global --;
	printf("global vale %d\n",global);
	sem_post(&a);
	
}

void main(int argc, char **argv){
	if(argc!=2){
		printf("Error al recibir argumentos");
		exit(EXIT_FAILURE);
	}
	srand(time(NULL));
	sem_init(&a, 0, 1);
	sem_init(&b, 0, 0);
	pthread_t idhilo1;
	pthread_t idhilo2;
	for(int i=0; i<atoi(argv[1]);i++){
		if(pthread_create(&idhilo1,NULL,(void*)sumador,NULL)!=0){
		printf("ERROR 1...\n");
		exit(EXIT_FAILURE);
		}
		if(pthread_create(&idhilo2,NULL,(void*)restador,NULL)!=0){
			printf("ERROR 2...\n");
			exit(EXIT_FAILURE);
		}
		if(pthread_join(idhilo1,(void**)NULL)!=0){
				printf("ERROR 3...\n");
				exit(EXIT_FAILURE);
		}
		if(pthread_join(idhilo2,(void**)NULL)!=0){
				printf("ERROR 4...\n");
				exit(EXIT_FAILURE);
		}
	}
	sem_destroy(&a);
	sem_destroy(&b);

	exit(EXIT_SUCCESS);
}