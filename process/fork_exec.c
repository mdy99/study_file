#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>

int main()
{
	printf("Parent process (PID: %d)\n", getpid());

	pid_t pid = fork(); // fork 사용

	if (pid < 0)
	{
		perror("fork failed");
		exit(EXIT_FAILURE);
	}
	else if (pid == 0)
	{
		// 자식 프로세스에서 exec 호출
		char *args[] = {"ls", "-al", NULL};
		execvp("ls", args); // 프로그램 이름, 프로그램 실행에 필요한 인자

		// exec 실패 시
		perror("execvp failed");
		exit(EXIT_FAILURE);
	}
	else
	{
		// 부모 프로세스는 자식이 종료할 때까지 대기
		wait(NULL);
		printf("Child process finished\n");
	}

	return 0;
}
