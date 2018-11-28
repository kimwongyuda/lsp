#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

#define MAX_CMD 256

int mysystem(int argc, char *cmd[])
{
	int i;
	printf("cmd 입니다\n");
		
	for (i=1;i<argc;i++)
	{
		printf(cmd[i]);
	}
	printf("\n");
		
	char *argv[] = {};
	for (i=1;i<argc;i++)
	{
		argv[i-1] = cmd[i];
	}
	argv[argc-1] = NULL; 
	printf("argv:\n");
	for (i=0;i<argc;i++)
	{
		printf(argv[i]);
	}
	printf("\n");

	char temp[100] = "/bin/";
	strcat(temp,cmd[1]);
	printf("real cmd: %s",temp);

	if (execv(temp,argv)<0){
		perror("execv");
		return 0;
	}
	return 1;
}

main(int argc, char *argv[])
{
	int status;
	pid_t pid;
	
	
	if ((pid=fork())<0){
	perror("fork");
	exit(1);
	}

	else if (pid==0){
		printf("child!\n");
		status = mysystem(argc,argv);
		if (status==0){
			printf("이상한 명령어 입력\n");
			exit(1);
		}
			
	}
	if (waitpid(pid, NULL, 0) <0){
			perror("waitpid");
			exit(1);
	}
	
}
	
