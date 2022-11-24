#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <errno.h>
#include <string.h>


int main(){
    pid_t pid,flag;
    int status,dato;
    pid=fork();

    //HIJO 1
    if(pid==-1){
        printf("error\n");
    }
    else if(pid==0){
        printf("Soy el hijo:%ld,y mi padre es:%ld\n",(long int)getpid(),(long int)getppid());
        exit(EXIT_SUCCESS);
    }

    //HIJO 2
     pid=fork();
    if(pid==-1){
        printf("error\n");
    }
    else if(pid==0){
        printf("Soy el hijo:%ld,y mi padre es:%ld\n",(long int)getpid(),(long int)getppid());
        pid=fork();
        if(pid==-1){
        printf("error\n");
        }
        else if(pid==0){
        printf("Soy el hijo:%ld,y mi padre es:%ld\n",(long int)getpid(),(long int)getppid());
        exit(EXIT_SUCCESS);
        }

        pid=fork();
        if(pid==-1){
        printf("error\n");
        }
        else if(pid==0){
        printf("Soy el hijo:%ld,y mi padre es:%ld\n",(long int)getpid(),(long int)getppid());
        pid=fork();
        if(pid==-1){
        printf("error\n");
        }
        else if(pid==0){
        printf("Soy el hijo:%ld,y mi padre es:%ld\n",(long int)getpid(),(long int)getppid());
        exit(EXIT_SUCCESS);
        }
        //espera hijo 3
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
        
        }

        //espera h2
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

    //espera a.out
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