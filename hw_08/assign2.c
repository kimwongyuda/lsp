#include <stdio.h>
#include <sys/types.h>
#include <sys/mman.h>
#include <fcntl.h>
#include "synclib.h"
#include <sys/shm.h>
#include <sys/ipc.h>
#include <stdlib.h>
#include "shm.h"


#define	ARRAY_SIZE	40000
#define	MALLOC_SIZE	100000
#define	SHM_SIZE	100000
#define	SHM_MODE	(SHM_R | SHM_W)

#define	NLOOPS	10
#define	SIZE	sizeof(long)


int
update(long *ptr)
{
	return ((*ptr)++);
}

main()
{
	int		fd, i, counter;
	pid_t	pid;
	caddr_t area;
	
	if ((fd = shmget(IPC_PRIVATE, SHM_SIZE, SHM_MODE))<0)
	{
		perror("open");
		exit(1);
	}
	
	if ((area = shmat(fd,0,0))== (void *)-1)
	{
		perror("shmat");
		exit(1);
	}

			
	TELL_WAIT();
	if ((pid = fork()) < 0)  {
		perror("fork");
		exit(1);
	}
	else if (pid > 0)  {
		
		for (i = 0 ; i < NLOOPS ; i += 2)  {
			if ((counter = update((long *) area)) != i)  {
				fprintf(stderr, "Counter mismatch\n");
				exit(1);
			}
			printf("Parent: counter=%d\n", counter);
			TELL_CHILD();
			WAIT_CHILD();
		}
	}
	else  {
		for (i = 1 ; i < NLOOPS ; i += 2)  {
			WAIT_PARENT();
			if ((counter = update((long *) area)) != i)  {
				fprintf(stderr, "Counter mismatch\n");
				exit(1);
			}
			printf("Child : counter=%d\n", counter);
			TELL_PARENT();
		}
	}
	
	if (shmctl(fd, IPC_RMID, 0) < 0)  {
		perror("shmctl");
		exit(1);
	}	
}
