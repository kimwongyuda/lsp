#include <stdio.h>

#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#define MAX_CMD 256

int mysystem(char *cmd)
{
	printf("cmd 입니다 %s\n", cmd);
	char temp[100];
	char *argv[] = {cmd,NULL};
	
	strcpy(temp,"/bin/");
	strcat(temp,cmd);
	printf("%s\n", temp);


	
    if(execv(temp,argv)<0){
		perror("execv");
		return 0;
	}	    
    
	return 1;
}
main(int argc, char *argv[])
{
	int status;
	char cmd[MAX_CMD];
	pid_t pid;	
	while(1){
		printf("CMD>");
		gets( cmd);
		printf("%s\n", cmd);
		if(cmd[0]=='q')
			break;
		
    	if ((pid=fork())<0){
        	perror("fork");
        	exit(1);
    	}

    	else if (pid==0){
        	printf("child!\n");
        	status = mysystem(cmd);
			if(status ==0)
			{
				printf("이상한 명령어 입니다.\n");
				exit(1);
			}
    	}

    	if (waitpid(pid, NULL, 0) <0){
        	perror("waitpid");
        	exit(1);
    	}
	}
}
	
