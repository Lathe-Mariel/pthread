#include <sys/time.h>
#include <stdio.h>
#include <stdlib.h>

#define B 32// tbがアクセスする場所．0 or 1 or 32を設定する
#define N 1000000000
volatile int data[128];
void ta() {
for (int i = 0; i < N; i++)
data[0]++; // 配列の0番目をインクリメント
}
void tb() {
for (int i = 0; i < N; i++)
data[B]++; // 配列のB番目をインクリメント
}

int main(char *args){

	struct timeval t1, t2;

	printf("Start\n");
	gettimeofday(&t1, NULL);
#pragma omp parallel sections
	{
#pragma omp section
	ta();
#pragma omp section
	tb();
	}
	gettimeofday(&t2, NULL);
	long sec = t2.tv_sec - t1.tv_sec;
	long usec = t2.tv_usec - t1.tv_usec;
	double  s = sec + usec / 1000000.0;
	printf("time: %f s\n", s);
}
