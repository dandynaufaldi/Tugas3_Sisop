#include<stdio.h>
#include<string.h>
#include<pthread.h>
#include<stdlib.h>
#include<unistd.h>
#include<stdlib.h>
pthread_t tmusic;
pthread_t tmenu;
int mode;
int delay;
int change=0;
int wait=1;

void* menu(void *,arg)
{
    return NULL;
}

void* music(void *arg)
{
    
    return NULL;
}
int main(void)
{
    int i=0;
    int err;
    err=pthread_create(&tmusic),NULL,&music,NULL);
    if(err!=0)
    {
        printf("\n can't create thread music : [%s]",strerror(err));
    }
    err=pthread_create(&tmenu),NULL,&menu,NULL);
    if(err!=0)
    {
        printf("\n can't create thread menu : [%s]",strerror(err));
    }
    pthread_join(tmusic,NULL);
    pthread_join(tmenu,NULL);
    return 0;
}
