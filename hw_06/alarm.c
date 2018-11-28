#include <stdio.h>
#include <signal.h>

static unsigned int	AlarmSecs;


void
SigAlarmHandler(int signo)
{
	/*사실상 여기 없어도 리눅스에서는 한번만 등록해줘도 되지만 유닉스 대비시에 한번더 등록해주는거 */
	if (signal(SIGALRM, SigAlarmHandler) == SIG_ERR)  {
		perror("signal");
		exit(1);
	}

	alarm(AlarmSecs);

	/* Do something */
	printf(".");
	fflush(stdout);

	return;
}

int
SetPeriodicAlarm(unsigned int nsecs)
{
	if (signal(SIGALRM, SigAlarmHandler) == SIG_ERR)  {
		return -1;
	}

	AlarmSecs = nsecs;

	alarm(nsecs);

	return 0;
}

main()
{
	printf("Doing something every one seconds\n");

	SetPeriodicAlarm(1);

	for ( ; ; )
		pause();
}
