#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <errno.h>
#include <string.h>
#include <signal.h>

void tratarSenal(int signal){
    printf("he recibido SIGUSR1 y su codigo es %d\n",signal);
    exit(EXIT_SUCCESS);
}





int main(){
signal(SIGUSR1,&tratarSenal);
printf("SOY %ld y Me duermo...\n",(long int)getpid());
while(1);
exit(EXIT_SUCCESS);

}
