#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

int cekprima(int N);
void* cetakprima(void *ptr);
typedef struct{
	int from;
	int to;
}bound;

int main()
{
	int N,T; scanf("%d%d", &N, &T);
	pthread_t thr[T+1];
	bound batas; 
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
		printf("thr %d from %d to %d\n", i, batas.from, batas.to);
		int status = pthread_create( &thr[i], NULL, cetakprima, (void*)&batas);
		if (status){
			printf("Failed to create thread %d\n", i);
			i--;
		}
		else pthread_join(thr[i], NULL);
	}
	return 0;
}

int cekprima(int N){
	int i;
	if (N<2) return 0;
	for(i=2;i*i<=N;i++){
		if (N%i==0) return 0;
	}
	return 1;
}
void* cetakprima(void* ptr){
	int i;
	bound *batas = (bound*)ptr;
	for(i=batas->from;i<=batas->to;i++){
		if (cekprima(i)) printf("%d\n", i);
	}
}

/*
Latihan 2
Buatlah sebuah program multithreading yang dapat menampilkan N bilangan prima pertama. 
program akan dieksekusi menggunakan thread sebanyak T dimana setiap thread akan melakukan print sebanyak N/T bilangan prima. 
Input : N = banyak bilangan prima; T = banyak thread yang digunakan
*/