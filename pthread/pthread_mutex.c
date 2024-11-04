#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
/*
	mutex
	Mutual Exclusion : 상호 배제
	pthread_mutex_t 상호배제 설정값을 담은 비트값

	기본 동작은 그냥 lock이랑 unlock임.
	lock 쓴 스레드만 접근 가능

	>>설정<<
	pthread_mutex_t mutex; // 뮤텍스
	pthread_mutxattr_t mutexattr; // 속성 담은 변수

	>속성 초기화<
	pthread_mutxattr_t_init(&mutexattr); // 속성을 기본으로 초기화 해둠
	>속성 타입설정<
	pthread_mutxattr_t_settype(&mutexattr,PTHREAD_MUTEX_ERRORCHECK); // 에러체크로 속성 설정
	>해당 속성으로 설정된 뮤텍스로 뮤텍스 초기화<
	pthread_mutex_init(&mutex, &mutexattr);
	pthread_mutex_init(&mutex, NULL); //기본 속성으로 초기화(PTHREAD_MUTEX_NORMAL이 기본)



	PTHREAD_MUTEX_NORMAL : (기본) 동일 스레드 2번 잠그면, 손상 일어남
		ㄴ 하지만, 빠름. 프로그래머가 2번 잠그지만 않으면, 빠르게 동작 가능
	PTHREAD_MUTEX_ERRORCHECK : 동일 스레드 2번 잠그면, 에러 반환 함
	PTHREAD_MUTEX_RECURSIVE : 동일 스레드를 뮤텍스가 여러번 잠글 수 있고, 잠근 만큼 해제해야 함

	pthread_mutex_lock(&mutex) : 해당 뮤텍스 잠금
	pthread_mutex_unlock(&mutex) : 해당 뮤텍스 잠금 해제

	pthread_mutex_destroy(&mutex)
		사용이 끝난 뮤텍스를 해제하고 반환함

	이미 lock 되어있는 뮤텍스를 다른 스레드에서 lock을 시도하면?
		1. 잠겨있는지 확인
		2. 잠겨있으면, 해제될 때까지 대기
		3. 블로킹 상태, 스케줄링 상태에서 제외됨
		기본 상태는 블로킹으로 대처 되는 거임

		-> trylock을 사용하면, 잠겨있으면 다른 작업하도록 유도할 수 있음

		pthread_mutex_trylock(&mutex)

		if(pthread_mutex_trylock(&mutex)==0) // 잠금시도의 성공
		{

		}
		else // 딴 곳에서 이미 잠그고 있어서 다른 작업으로 빠짐
		{

		}

*/

pthread_mutexattr_t mutexattr;
int main()
{

	return 0;
}