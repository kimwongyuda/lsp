#include <stdio.h>
#include <signal.h>

void
SigUsrHandler(int signo)
{
	/*kill USR1 = USR1 시그널을 알림, -TERM = TERM 시그널을 알림*/
	if (signo == SIGUSR1)  {
		printf("Received a SIGUSR1 signal\n");
	}
	else if (signo == SIGUSR2)  {
		printf("Received a SIGUSR2 signal\n");
	}
	else  {
		printf("Received unknown signal\n");
		printf("Terminate this process\n");
		exit(0);
	}
}

main()
{
	if (signal(SIGUSR1, SigUsrHandler) == SIG_ERR)  {
		perror("signal");
		exit(1);
	}

	if (signal(SIGUSR2, SigUsrHandler) == SIG_ERR)  {
		perror("signal");
		exit(1);
	}
	
	/*이거 안하면 시그널 한번하고 퍼즈 풀림*/
	for( ; ;)	
		pause();
}
