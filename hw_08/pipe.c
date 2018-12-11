#include <stdio.h>

#include <sys/types.h>
#include <unistd.h>

#define	MAX_BUF	128

main()
{
	int		n, fd[2];
	pid_t	pid;
	char	buf[MAX_BUF];
	FILE *fp;
	if (pipe(fd) < 0)  {
		perror("pipe");
		exit(1);
	}

	if ((pid = fork()) < 0)  {
		perror("fork");
		exit(1);
	}

	/*파일 오픈 하면 무조건 err, in, out 됨!!!!!!! 이 디스크립터 3개 열림 순서대로 2, 0, 1임 그 뒤로 파일 연거는 3부터 셈
	즉 fd[0]은 프로세스에서 3, fd[1]은 4로 설정됨.*/
	else if (pid == 0)  {
		close(fd[1]);
		printf("Child : Wait for parent to send data\n");
		
		/*이때 자식이 먼저 요청 했으면 자식 wait상태*/
		if ((n = read(fd[0], buf, MAX_BUF)) < 0)  {
			perror("read");
			exit(1);
		}
		printf("Child : Received data from parent: ");
		fflush(stdout);
		/*fprintf도 가능!*/
		/*STDOUT_FILENO = 화면 출력*/
		/*write(STDOUT_FILENO, buf, n);*/
		fp = fopen("asd.txt", "w");
		fprintf(fp, buf, n);
	}
	else  {
		close(fd[0]);
		strcpy(buf, "Hello, World!\n");
		printf("Parent: Send data to child\n");
		/* 부모는 pipe로 열고 write하는 방식*/
		write(fd[1], buf, strlen(buf)+1);
	}

	exit(0);
}
