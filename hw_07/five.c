#include <stdio.h>
#include <signal.h>

static int count;
static FILE* f;

void
SigAlarmHandler(int signo)
{
    if (signal(SIGALRM, SigAlarmHandler) == SIG_ERR)  {
        perror("signal");
        exit(1);
    }

    fprintf(f, "%d\n", ++count);

    return;
}

void sigint_handler(int signo){
    fclose(f);
    exit(0);
}

int
SetPeriodicAlarm(unsigned int usecs)
{
    if (signal(SIGALRM, SigAlarmHandler) == SIG_ERR)  {
        return -1;
    }

    ualarm(usecs,usecs);

    return 0;
}

main()
{
    signal(SIGINT, sigint_handler);
    f = fopen("alarm.txt", "wb");
    SetPeriodicAlarm(500000);

    for ( ; ; )
        pause();
}
