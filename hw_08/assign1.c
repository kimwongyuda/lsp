#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

#define	MAX_BUF	128

main()
{
	int		n, fd[2],fd2[2];
	pid_t	pid;
	char	buf[MAX_BUF],buf2[MAX_BUF];

	if (pipe(fd) < 0)  {
		perror("pipe");
		exit(1);
	}
	if (pipe(fd2) <0)
	{
		perror("pipe");
		exit(1);
	}

	if ((pid = fork()) < 0)  {
		perror("fork");
		exit(1);
	}
	else if (pid == 0)  {
		close(fd[1]);
		close(fd2[0]);

		printf("Child : Wait for parent to send data\n");
		if ((n = read(fd[0], buf, MAX_BUF)) < 0)  {
			perror("read");
			exit(1);
		}
		printf("Child : Received data from parent: ");
		fflush(stdout);
		write(STDOUT_FILENO, buf, n);

        strcpy(buf2, "자식이 부모에게 보내는 메세지\n");
        printf("자식이 부모에게...\n");
        write(fd2[1], buf2, strlen(buf2)+1);
	}
	else  {
		close(fd[0]);
		close(fd2[1]);

		strcpy(buf, "Hello, World!\n");
		printf("Parent: Send data to child\n");
		write(fd[1], buf, strlen(buf)+1);

		printf("부모가 자식에게 받음\n");
        if ((n = read(fd2[0], buf2, MAX_BUF)) < 0)  {
            perror("read");
            exit(1);
        }
        printf("부모가 받은 메세지 =  ");
        fflush(stdout);
        write(STDOUT_FILENO, buf2, n);
	}

	exit(0);
}
