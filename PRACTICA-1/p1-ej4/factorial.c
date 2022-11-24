#include <stdio.h>
#include <stdlib.h>
int main(int argc,char**argv){
    if(argc==0){
        printf("error en linea de argumentos\n");
        exit(-1);
    }
    int n=atoi(argv[1]);
    int fact=1;
    for(int i=1;i<=n;i++){
        fact=fact*i;
    }
    printf("el factorial es:%i\n",fact);
}