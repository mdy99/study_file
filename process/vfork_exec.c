#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

int main()
{
	printf("Parent process (PID: %d)\n", getpid());

	pid_t pid = vfork(); // vfork 사용

	if (pid < 0)
	{
		perror("vfork failed");
		exit(EXIT_FAILURE);
	}
	else if (pid == 0)
	{
		// 자식 프로세스에서 exec 호출
		char *args[] = {"ls", "-al", NULL};
		execvp("ls", args);

		// exec 실패 시
		perror("execvp failed");
		_exit(EXIT_FAILURE); // vfork 사용 시 _exit()로 종료해야 함, 부모의 메모리 상태를 보존하기 위해서
	}
	else
	{
		// 부모 프로세스는 자식이 끝날 때까지 대기
		printf("Child process (PID: %d) is replacing itself with 'ls -l' command.\n", pid);
	}

	return 0;
}
