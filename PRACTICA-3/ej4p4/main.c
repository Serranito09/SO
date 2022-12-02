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

sem_t a;
sem_t b;

void * escribirA(void *p){
	int i;
	for(i=0;i<5;i++){
		sem_wait(&a);
		printf("A");
		fflush(NULL);
		sem_post(&b);
	}
}

void * escribirB(void *p){
	int i;
	for(i=0;i<5;i++){
		sem_wait(&b);
		printf("B");
		fflush(NULL);
		sem_post(&a);
	}
}

void main(){
	sem_init(&a, 0, 0);
	sem_init(&b, 0, 1);
	pthread_t idhilo1;
	pthread_t idhilo2;

	
	if(pthread_create(&idhilo1,NULL,(void*)escribirA,NULL)!=0){
		printf("ERROR 1...\n");
		exit(EXIT_FAILURE);
	}
	if(pthread_create(&idhilo2,NULL,(void*)escribirB,NULL)!=0){
		printf("ERROR 1...\n");
		exit(EXIT_FAILURE);
	}

	if(pthread_join(idhilo1,(void**)NULL)!=0){
		printf("ERROR 3...\n");
		exit(EXIT_FAILURE);
	}
	if(pthread_join(idhilo2,(void**)NULL)!=0){
		printf("ERROR 3...\n");
		exit(EXIT_FAILURE);
	}
  printf("\n");
	sem_destroy(&a);
	sem_destroy(&b);

	exit(EXIT_SUCCESS);
}