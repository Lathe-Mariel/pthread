#include <sys/time.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#define B 32// tbがアクセスする場所．0 or 1 or 32を設定する
#define N 1000000000
volatile int data[128];
void * ta(void *argp) {
for (int i = 0; i < N; i++)
data[0]++; // 配列の0番目をインクリメント
}
void * tb(void *argp) {
for (int i = 0; i < N; i++)
data[B]++; // 配列のB番目をインクリメント
}

int main(char *args){
int a1[] = {};
int a2[] = {};
	struct timeval t1, t2;
	pthread_t thread1, thread2;

	printf("Start\n");
	gettimeofday(&t1, NULL);
		pthread_create(&thread1, NULL, ta, a1);
		pthread_create(&thread2, NULL, tb, a2);
		pthread_join(thread1, NULL);
		pthread_join(thread2, NULL);
	gettimeofday(&t2, NULL);
	long sec = t2.tv_sec - t1.tv_sec;
	long usec = t2.tv_usec - t1.tv_usec;
	double  s = sec + usec / 1000000.0;
	printf("time: %f s\n", s);
}
