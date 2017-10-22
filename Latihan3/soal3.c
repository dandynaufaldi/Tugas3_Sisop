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
int ready=0;

void* menu(void *arg)
{
    while(!ready);
    while(1)
    {
	wait=1;
	delay=0;
	printf("Choose mode:\n0.Exit\n1.Display Playlist\n2.Play\n3.Stop\n4.Pause\n5.Resume\n6.Help\n");
	scanf("%d",&mode);
	if(mode>2&&mode<6)
	{
	    printf("Enter the delay:\n");
	    scanf("%d",&delay);
	    sleep(delay);
	}
	if(mode > 0 && mode < 6)
	change=1;
	else if(mode==6)
	{
	    printf("0.Exit:Exit media player\n1.Display Playlist:Display current playlist contents\n2.Play:Play the current media\n3,Stop:Stop the current media\n4.Pause:Pause the current media\n5.Resume:Resumes the current media\n6.Help:Display help\n");
	    wait = 0;
	}
	else if(mode==0)
	{
	    change=1;
	    break;
	}
	else
	{
	    printf("Unknown Mode. Please Try Again");
	    wait=0;
	}
	while(wait);
    }
    return NULL;
}

void* music(void *arg)
{
    while(!ready);
    while(1)
    {
	while(!change);
	if(mode==0)
	{
	    break;
	}
	else if(mode==1)
	{
	    system("echo playlist | netcat localhost 12350");
	}
	else if(mode==2)
	{
	    system("echo play | netcat localhost 12350");
	}
	else if(mode==3)
	{
	    system("echo stop | netcat localhost 12350");
	}
	else if(mode==4)
	{
	    system("echo pause | netcat localhost 12350");
	}
	else if(mode==5)
	{
	    system("echo play | netcat localhost 12350");
	}
	change = 0;
	wait = 0;
    }
	system("echo shutdown | netcat localhost 12350");
    return NULL;
}
int main(void)
{
    int i=0;
    int err;
    err=pthread_create((&tmusic),NULL,&music,NULL);
    if(err!=0)
    {
        printf("\n can't create thread music : [%s]",strerror(err));
    }
    err=pthread_create((&tmenu),NULL,&menu,NULL);
    if(err!=0)
    {
        printf("\n can't create thread menu : [%s]",strerror(err));
    }
    system("cvlc --intf rc --rc-host localhost:12350 -d");
    ready=1;
    pthread_join(tmusic,NULL);
    pthread_join(tmenu,NULL);
    return 0;
}
