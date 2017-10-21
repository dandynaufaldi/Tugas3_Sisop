#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

int cekprima(int N);
void* cetakprima(void *ptr);
int key=0, status = 0;
typedef struct{
	int from;
	int to;
	pthread_mutex_t lock;
	pthread_cond_t done;
}bound;

int main()
{
	int N,T; scanf("%d%d", &N, &T);
	pthread_t thr[T+1];
	bound batas;
	pthread_mutex_init(&batas.lock, NULL);
	pthread_cond_init (&batas.done, NULL);
	pthread_mutex_lock (&batas.lock);
	int i, cnt=1;
	for(i=0;i<T;i++){
		 
		if (i==T-1){
			batas.from = cnt;
			batas.to = N;
		}
		else{
			batas.from = cnt;
			batas.to = cnt + N/T - 1;
			cnt = cnt + N/T;
		}
		int status = pthread_create( &thr[i], NULL, cetakprima, (void*)&batas);
		if (status){
			printf("Failed to create thread %d\n", i);
			i--;
		}
		pthread_cond_wait (&batas.done, &batas.lock);
		//printf("Create thread %d from %d to %d\n", i, batas.from, batas.to);
	}
	for(i=0;i<T;i++) pthread_join(thr[i], NULL);
	pthread_mutex_destroy (&batas.lock);
	pthread_cond_destroy (&batas.done);
	return 0;
}

int cekprima(int N){
	int j;
	if (N<2) {
		//status = 0;
		return 0;
	}
	for(j=2;j*j<=N;j++){
		if (N%j==0) {
			return 0;
		}
	}
	return 1;
}
void* cetakprima(void* ptr){
	pthread_mutex_lock(&(*(bound*)(ptr)).lock);
	bound *batas = ptr;
	int k;
	//printf("Run thread from %d to %d\n", batas->from, batas->to);
	for(k=batas->from;k<=batas->to;k++){
		if (cekprima(k)) printf("%d\n", k);
	}
	
	pthread_mutex_unlock(&(*(bound*)(ptr)).lock);
	pthread_cond_signal (&(*(bound*)(ptr)).done);
}

/*
Latihan 2
Buatlah sebuah program multithreading yang dapat menampilkan N bilangan prima pertama. 
program akan dieksekusi menggunakan thread sebanyak T dimana setiap thread akan melakukan print sebanyak N/T bilangan prima. 
Input : N = banyak bilangan prima; T = banyak thread yang digunakan

https://www.cs.nmsu.edu/~jcook/Tools/pthreads/pthread_cond.html
https://stackoverflow.com/questions/10879420/using-of-shared-variable-by-10-pthreads
*/