#include <stdio.h>

#include <sys/types.h>
#include <unistd.h>

char	*EnvInit[] = { "USER=unknown", "PATH=/tmp", NULL };

main()
{
	pid_t	pid;

	if ((pid = fork()) < 0)  {
		perror("fork");
		exit(1);
	}
	else if (pid == 0)  {
		/* specify pathname, specify environment */
		printf("i================1");
		if (execle("./env",
				"env", "myarg1", "MYARG2", NULL, EnvInit) < 0)  {
			perror("execle");
			exit(1);
		}
	}
	if (waitpid(pid, NULL, 0) < 0)  {
		perror("waitpid");
		exit(1);
	}
	printf("parent\n\n\n\n\n");

	if ((pid = fork()) < 0)  {
		perror("fork");
		exit(1);
	}
	else if (pid == 0)  {
	 	/* specify filename, inherit environment */
		printf("i========2");
		if (execlp("env", "env", NULL) < 0)  {
			perror("execlp");
			exit(1);
		}
	}
}
