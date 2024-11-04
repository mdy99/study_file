#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

/*
	Thread의 숫자는 프로그램 내에서 일관되게 유지되어야 하므로 (오류 방지)
	const int num_thread = 5;
	#define NUM_THREAD 5
	이런 방식으로 스레드 수를 고정시키고 있다.
*/
#define NUM_THREAD 3

/*
	gettid()를 쓰기 위해 필요한 정의
	pthread_t는 POSIX THREAD 라이브러리 내에서 생성된 스레드들끼리 구분하기 위해 만든 id고
	gettid()는 실제 시스템 커널 단에서 구분하기 위해 만든 tid를 얻기 위한 함수이다.
	리턴값은 pid_t로 받는다.
*/
#define _GNU_SOURCE
#include <syscall.h>
pid_t gettid_implementation() // 실제 구현 시
{
	return syscall(SYS_gettid);
}

typedef struct // 전달해야할 인자값이 여러개인 경우, 구조체로 한번에 전달한다
{
	int id;
	const char *message; // 스레드 관련은 절대 수정 불가해야 안전함 그래서 상수화
} Thread_data;

void *many_var_function(void *arg)
{
	Thread_data data = *(Thread_data *)arg;
	printf("id is %d\n", data.id);
	return NULL;
}

/*
pthread_create에 인자로 들어가는 function은 일종의 start routine임
해당 스레드가 생성되면, 해야 할 일

pthread_create()의 4번째 인자값을 void *arg로 받음
(int*)arg로 바꾸고 *로 값 꺼내오기
*/
void *one_var_function(void *arg) // 인자가 한 개인 경우
{
	int num = *(int *)arg;
	printf("number is %d\n", num);
	return NULL;
}
void *no_var_function(void *arg) // 인자가 없는 경우
{
	printf("Hello, pthread!\n");
	return NULL;
}

int main()
{
	/*
		POSIX Thread
		Portable Operating System Interface uniX(?)
		이식성이 용이하도록 한 IEEE 표준 thread 규격
	*/
	pid_t tid = gettid();
	printf("%d\n", tid);

	/*
		pthread 내에서 구분하기 위해 만든 식별 id, 실제 커널 단에서 구분하는 스레드 id는 gettid로 구할 수 있다
	*/
	pthread_t pthread[3];

	/*
	pthread_attr_t : 스레드의 설정값이 담길 비트 변수
		스택 사이즈, 스레드 분리 상태. 스케줄링 정책 설정 가능

	>> 기본 설정 & 파괴 <<
	pthread_attr_init(&attr)  	: 설정값을 초기값으로 초기화 합니다.
	pthread_attr_destroy(&attr) : 속성 객체를 해제하여, 메모리를 반환합니다. 일종의 free

	>> 스택 사이즈 설정 <<
	pthread_attr_setstacksize(&attr, stacksize) : 스택 사이즈 설정
	pthread_attr_getstacksize(&attr, &stacksize) : 스택 사이즈를 담아서 받아옴

	>> 분리상태 설정 <<
	pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED) : 분리상태 설정
	pthread_attr_setdetachstate(&attr, &detachstate) 			: 현재 분리상태를 담아서 받아옴
		ㄴ> PTHREAD_CREATE_JOINABLE, PTHREAD_CREATE_DETACHED, (조인 가능, 분리 상태)
			(스레드가 끝나도 join되기 전까지 자원 미해제 >> JOINABLE이 default
			 스레드가 끝나면 자원 즉시 해제)

	>> 스케줄 정책 설정 <<
	pthread_attr_setschedpolicy(&attr, SCHED_FIFO) : 스케줄 정책 설정
	pthread_attr_getschedpolicy(&attr, &policy) : 현재 스케줄 정책을 담아서 가져옴 (int)
		ㄴ> SCHED_FIFO, SCHED_RR, SCHED_OTHER
		(높은 우선순위가 무조건 먼저 실행, 우선순위를 두지 않고 시간마다 돌아가며 실행함,
		(default)운영체제에 맡김)

	>>우선 순위 설정<<
	struct sched_param param;
	param.sched_priority = 10; // 순위를 10위로 설정함
	pthread_attr_setschedparam(&attr, &param); // 우선순위 설정함
	pthread_attr_getschedparam(&attr, &param); // 현재 우선순위를 받아옴
	*/
	pthread_attr_t new_attr;

	Thread_data tData = {10164, "Hello, Thread!"}; // 인자 한개밖에 못 전달하니 구조체를 이용
	size_t stacksize = 1024 * 1024;				   // 스택 사이즈 설정 10^6, 1MB
	int anyNumber = 10;

	pthread_attr_init(&new_attr); // 속성값 기본으로 초기화
	pthread_attr_setstacksize(&new_attr, stacksize);

	/*
	pthread_create() 생성되자마자 start_routine을 실행하기 시작함
		속성값 defalt로 설정 시, NULL
		인자 필요 없을 시, NULL
	*/
	pthread_create(&pthread[0], &new_attr, one_var_function, &anyNumber); // 인자가 1개인 경우
	pthread_create(&pthread[1], NULL, many_var_function, &tData);		  // 인자가 여러개인 경우, 구조체로 전달
	pthread_create(&pthread[2], NULL, no_var_function, NULL);			  // 인자가 없는 경우

	pthread_attr_destroy(&new_attr); // 해제시켜줘야 하는 건 attr밖에 없음

	return 0;
}