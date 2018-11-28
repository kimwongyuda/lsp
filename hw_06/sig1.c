#include <stdio.h>
#include <signal.h>

void
SigIntHandler(int signo)
{
	printf("Received a SIGINT signal\n");
	printf("Terminate this process\n");

	exit(0);
}

main()
{
	signal(SIGINT, SigIntHandler);
	
	printf("Press ^C to quit\n");

	
	printf("1111\n");
	pause();
	printf("2222\n");
}
