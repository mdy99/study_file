#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>

pthread_mutex_t mutex; // 잠그는 놈은 하나,
// 잠그는 스레드만이 프로세스 내 모든 공유 자원을 사용 가능, 나머지는 대기 >> 이부분은 확실치 않음
pthread_cond_t cond_produce;
pthread_cond_t cond_consume;

/*
cond랑 mutex는 모두 해당 함수를 실행한 스레드에 wait, lock을 해주는 거임
signal로 wait된 해당 스레드를 깨워주는 거고

스레드 간 깨우고, 자고 하는 거 관리하는 놈
조건 됐으니 빨리 나가! 역할
*/

#define STORAGESIZE 5

int storage[STORAGESIZE];
int count = 0;

void *producer_fucntion(void *arg)
{
	while (1)
	{
		pthread_mutex_lock(&mutex);

		while (count == STORAGESIZE) // 창고가 가득 차서 더 생산 못함
		{
			printf("Storage is Full now... waiting...\n");
			pthread_cond_wait(&cond_produce, &mutex);
		}

		storage[count] = rand() % 100;
		printf("Producer : Produce [%d]item %d\n", count, storage[count]);
		count++;

		pthread_cond_signal(&cond_consume); // 만약에 자고 있으면 깨움
		pthread_mutex_unlock(&mutex);

		sleep(1);
	}
}

void *consumer_fucntion(void *arg)
{
	while (1)
	{
		pthread_mutex_lock(&mutex);

		while (count == 0) // 창고가 비어서 소비할 게 없으니 대기
		{
			printf("Storage is Empty now... waiting...\n");
			pthread_cond_wait(&cond_consume, &mutex);
		}

		int item = storage[--count];
		printf("Consumer : Consume [%d]item %d\n", count, item);

		pthread_cond_signal(&cond_produce); // 만약에 자고 있으면 깨움
		pthread_mutex_unlock(&mutex);

		sleep(1);
	}
}

int main()
{

	pthread_t producer_thread, consumer_thread;

	pthread_mutex_init(&mutex, NULL);
	pthread_cond_init(&cond_produce, NULL);
	pthread_cond_init(&cond_consume, NULL);

	pthread_create(&producer_thread, NULL, producer_fucntion, NULL);
	pthread_create(&consumer_thread, NULL, consumer_fucntion, NULL);

	pthread_join(producer_thread, NULL);
	pthread_join(consumer_thread, NULL);

	pthread_mutex_destroy(&mutex);
	pthread_cond_destroy(&cond_produce);
	pthread_cond_destroy(&cond_consume);

	return 0;
}

/*
	pthread_condattr_t에 들어갈 수 있는 값
		PTHREAD_PROCESS_PRIVATE : 기본값, cond를 동일 프로세스 내에서 사용될 때 사용,
								| 공유하지 않으므로 좀 더 빠름
		PTHREAD_PROCESS_SHARED 	: 다른 프로세스에서도 cond를 공유할 수 있음
	pthread_condattr_setpshared();를 통해 설정 가능
*/