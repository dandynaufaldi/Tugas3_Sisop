#include<stdio.h>
#include<string.h>
#include<pthread.h>
#include<stdlib.h>
#include<unistd.h>
#include<stdlib.h>
pthread_t tid[2];
char string[200];

int wait=1;

void* copy(void *arg)
{
    unsigned long i=0;
    pthread_t id=pthread_self();
    int iter;
    if(pthread_equal(id,tid[0]))
    {
        FILE* inpu=fopen("baca.txt","r");
	FILE* outp=fopen("salin1.txt","w");
	if(inpu !=NULL)
	{
		while(fgets(string, 199, inpu)!=NULL)
		{
			fputs(string,outp);
		}
		fclose(inpu);
		wait = 0;
	}
	else
	printf("Cannot access baca.txt");
	fclose(outp);
    }
    else if(pthread_equal(id,tid[1]))
    {
        while(wait);
	FILE* inp=fopen("salin1.txt","r");
	FILE* out=fopen("salin2.txt", "w");
	if(inp !=NULL)
	{
		while(fgets(string, 199, inp)!=NULL)
		{
			fputs(string,out);
		}
		fclose(inp);
	}
	else
	printf("Cannot access salin1.txt");
	fclose(out);
    }
    return NULL;
}
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
