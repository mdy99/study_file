#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#define NUM_THREAD 5
// 스레드에서의 값 설정
/*
	join(해당 스레드, 리턴받을 값을 가리키는 포인터)

	리턴받을 값을 가리키는 포인터로 변수를 받아오거나
	리턴 받을 필요없이 그냥 스레드 내에서 즉시 값을 바꾸거나
*/

int global_result; // 전역변수를 이용하는 방법

typedef struct // 구조체를 이용하는 방법
{
	int struct_result;
	// ...
	// ...
	// ...
	// ...
} Thread_data;

void *global_function(void *arg) // 정적변수, join 없이 값 설정 가능
{
	global_result = 10; // 전역변수의 값을 변경함
	return NULL;
}

void *struct_function(void *arg) // 구조체 포인터 사용, join 없이 값 설정 가능
{
	Thread_data *tData = (Thread_data *)arg; // 구조체를 받아온 다음
	tData->struct_result = 10;				 // 값을 변경함
	return NULL;
}

void *direct_function(void *arg) // 포인터를 직접 받아서 값 바꾸기
{
	int *result = (int *)arg; // 변수를 받아온 다음
	*result = 10;			  // 값을 변경함
	return NULL;
}

void *malloc_function(void *arg)
{
	int *result = (int *)malloc(sizeof(int)); // 값을 저장할 변수 공간을 생성함
	*result = 10;							  // 값을 설정함
	return (void *)result;					  // 해당 변수 공간을 리턴함 -> 이걸 join함수에서 두번째 인자로 받을 수 있음
}
void *malloc_function2(void *arg)
{
	int *result = (int *)malloc(sizeof(int));
	*result = 10;
	pthread_exit((void *)result); // return과 같지만, 코드 중간에 바로 나갈 수 있다는 장점이 있음
}
int main()
{
	int i;
	pthread_t pthread[5];
	Thread_data threadData;
	int val;
	int *direct_val = &val;

	int *retval;
	int *retval2;

	/* join 리턴값 없이 바로 값 설정하는 애들 */
	pthread_create(&pthread[0], NULL, global_function, NULL);
	pthread_create(&pthread[1], NULL, struct_function, &threadData);
	pthread_create(&pthread[2], NULL, direct_function, direct_val);

	/* join으로 리턴값 받아오는 애들 */
	pthread_create(&pthread[3], NULL, malloc_function, NULL);
	pthread_create(&pthread[4], NULL, malloc_function2, NULL);

	/* join 필요없이 값 설정 가능한 애들 */
	for (i = 0; i < NUM_THREAD - 2; i++)
	{
		pthread_join(pthread[i], NULL); // 얘네는 안 받아도 상관 없으니까 NULL로
	}

	/* >>join으로 리턴값 받는 애들 << */
	pthread_join(pthread[3], (void **)&retval); // <- join으로 리턴값을 받아올 수 있다
	pthread_join(pthread[4], (void **)&retval2);

	printf("global : %d\n", global_result);
	printf("struct : %d\n", threadData.struct_result);
	printf("direct : %d\n", *direct_val);
	printf("malloc : %d\n", *retval);
	printf("malloc2 : %d\n", *retval2);

	free(retval); // malloc 썼으니, 메모리 공간 돌려줘야겠지?
	free(retval2);

	return 0;
}
