#include <stdio.h>
#include <stdlib.h>
//#include <pthread.h>

int cekprima(int N){
	int i;
	if (N<2) return 0;
	for(i=2;i*i<=N;i++){
		if (N%i==0) return 0;
	}
	return 1;
}



int main()
{
	
	return 0;
}