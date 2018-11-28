#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>


void MyChildHandler(int signo)
{
	printf("자식 죽었습니다\n");
	exit(0);
}
main()
{
	pid_t pid;
	int status;
	
	if(signal(SIGCHLD, MyChildHandler)==SIG_ERR)
	{
		printf("signal error");
		exit(0);
	}
	
	if((pid=fork())<0){
		perror("fork");
		exit(1);
	}
	/*exit(1) 해줘도 종료되는거고 안해줘도 다하면 종료되는거*/
	/*wait => syncro하게 기다림, pause도 일단 그 프로세스 일시 중지니까 wait랑 비슷한거*/
	/*while 문은 어찌됐든 머라도 하는거니까!*/
	else if (pid==0){
		printf("I'm child\n");
		sleep(2);
	}
	else {
		while(1)
			printf("assd\n");
	}
}
