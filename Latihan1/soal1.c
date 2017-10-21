#include<stdio.h>
#include<string.h>
#include<pthread.h>
#include<stdlib.h>
#include<unistd.h>
#include<stdlib.h>
pthread_t tid[2];
char string[200];

int wait=1;
int main(void)
{
    int i=0;
    int err;
    while(i<2)
    {
        err=pthread_create(&(tid[i]),NULL,&copy,NULL);
        if(err!=0)
        {
            printf("\n can't create thread : [%s]",strerror(err));
        }
        i++;
    }
    pthread_join(tid[0],NULL);
    pthread_join(tid[1],NULL);
    return 0;
}
