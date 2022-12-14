#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <errno.h>
#include <string.h>

int main(int argc,char **argv){
    if(argc!=2){
        printf("error en la linea de argumentos");
        exit(EXIT_FAILURE);
    }
    pid_t pid,flag;
    int status;
    int n=atoi(argv[1]);
    for(int i=0;i<n;i++){
        pid=fork();
        if(pid==-1){
            printf("ERROR\n");
        }
        else if(pid==0){
            printf("Hijo con pid:%ld,y mi padre es:%ld\n",(long int)getpid(),(long int)getppid());
        }
        else{
            while((flag=wait(&status))>0){
		    if(WIFEXITED(status)){
		        printf("hijo %ld finalizado con status %d\n",(long int)flag,WEXITSTATUS(status));
		    }
		    else if(WIFSIGNALED(status)){
		        printf("hijo %ld finalizado tras recibir una senal con status %d\n",(long int)flag,WTERMSIG(status));
		    }
		    else if(WIFSTOPPED(status)){
		        printf("hijo %ld parado con status %d\n",(long int)flag,WSTOPSIG(status));
		    }
		    else if(WIFCONTINUED(status)){
		        printf("hijo %ld reanudado\n",(long int)flag);
		    }

		}
		if(flag==(pid_t)-1 && errno==ECHILD){ 
		    printf("Valor del errno= %d, definido como %s\n",errno,strerror(errno));
		}
		else{
		    printf("Error en la invocacion de wait o la llamada ha sido interrumpida por una señal\n");
		    exit(EXIT_FAILURE);
		} 

		exit(EXIT_SUCCESS);

        }
    }
    exit(EXIT_SUCCESS);
}