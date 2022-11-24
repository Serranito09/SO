#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <errno.h>
#include <string.h>
#include <signal.h>

void recibo(int signal){
    printf("se ha recibido la señal ctrl+c\n");
}

int main(){
    signal(SIGINT,&recibo);
    printf("Me duermo 30 segundos...\n");
    sleep(30);
    exit(EXIT_SUCCESS);
}