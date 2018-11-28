#include <stdio.h>
#include <signal.h>

void
SigAlarmHandler(int signo)
{
	/* nothing to do, just return to wake up the pause */
	printf("일어나라!!!!\n");
	return;
}

unsigned int
mysleep(unsigned int nsecs)
{
	if (signal(SIGALRM, SigAlarmHandler) == SIG_ERR)  {
		return nsecs;
	}

	alarm(nsecs);

	pause();

	return alarm(0);
}

main()
{
	printf("Wait for 5 seconds...\n");

	printf("이정도만 잤다 %d\n",mysleep(5));
}
