#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>

main()
{
	pid_t	pid;
	int		status;

	if ((pid = fork()) < 0)  {
		perror("fork");
		exit(1);
	}
	else if (pid == 0)  {
		printf("I'm a child\n");
		printf("my number: %d\n", getpid());
		sleep(2);
	}
	else  {
		wait(&status);
		printf("A child killed with %d status\n", status);
		printf("parent number: %d\n", getpid());
	}
}
