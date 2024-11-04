#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

void *cancel_function(void *arg)
{
	printf("Thread1 : Now I'm Sleeping...Zzz\n");
	sleep(5);
	return NULL;
}

void *self_function(void *arg)
{
	pthread_t *thread_id = (pthread_t *)malloc(sizeof(pthread_t));
	*thread_id = pthread_self(); // pthread id를 리턴해줌
	printf("Thread2 : My Id is ...here!\n");

	return (void *)thread_id;
}

int main()
{
	pthread_t pthread;
	pthread_t *retid;

	pthread_create(&pthread, NULL, cancel_function, NULL);
	pthread_cancel(pthread); // 동작 중인 해당 스레드를 중지시킴
	printf("Main Thread : you fired!\n");
	printf("Main Thread : Thread2, what your thread id?\n");
	pthread_create(&pthread, NULL, self_function, NULL);
	pthread_join(pthread, (void **)&retid); // join으로 값 받아오기 가능
	printf("MainThread : a-ha, Thread2's id is %ld... Ok!\n", *retid);
	free(retid);
	return 0;
}