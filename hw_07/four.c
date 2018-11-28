#include <stdio.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <unistd.h>
#define MAX_CMD 256

void DoCmd(char *cmd)
{
	system(cmd);
}

int main()
{
	char cmd[MAX_CMD];
	int pid;
	
	while(1)
	{
		printf("CMD >");
		gets(cmd);
		if (cmd[0] =='q')
			break;
		if ((pid = fork()) <0)
		{
			perror("fork");
			exit(1);
		}
		else if (pid ==0)
		{
			DoCmd(cmd);
			exit(0);
		}
		else
		{
			wait(NULL);
		}
	}
}
