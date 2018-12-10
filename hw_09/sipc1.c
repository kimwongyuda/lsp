#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include "semlib.h"
#include "sipc.h"


main()
{
        int             shmid;
        char    *ptr, *pData;
        int semid1,semid2,mutexSemid;

        //create shared memory
        if ((shmid = shmget(SHM_KEY, SHM_SIZE, SHM_MODE)) < 0)  {
                perror("shmget");
                exit(1);
        }
        //attach shared memory to pointer
        if ((ptr = shmat(shmid, 0, 0)) == (void *) -1)  {
                perror("shmat");
                exit(1);
        }
        //create semaphores
        if ((semid1 = semInit(SEM1_SEM_KEY)) < 0)  {
                fprintf(stderr, "semInit failure\n");
                exit(1);
        }
        if ((mutexSemid = semInit(MUTEX_SEM_KEY)) < 0)  {
                fprintf(stderr, "semInit failure\n");
                exit(1);
        }
        if ((semid2 = semInit(SEM2_SEM_KEY)) < 0)  {
                fprintf(stderr, "semInit failure\n");
                exit(1);
        }

		
        //wait for sem2 (request)
        if (semWait(semid2) < 0)  {
                fprintf(stderr, "semWait failure\n");
                exit(1);
        }
        //lock mutex
        if (semWait(mutexSemid) < 0)  {
                fprintf(stderr, "semWait failure\n");
                exit(1);
        }
        pData = ptr;
        printf("Received request: %s.....", pData);
        sprintf(pData, "This is a reply from %d.", getpid());
        printf("Replied.\n");
        //unlock mutex
        if (semPost(mutexSemid) < 0)  {
                fprintf(stderr, "semPost failure\n");
                exit(1);
        }
        //post to sem1 (reply)
        if (semPost(semid1) < 0)  {
                fprintf(stderr, "semPost failure\n");
                exit(1);
        }
        sleep(1);
        //destory semaphores
        if (semDestroy(mutexSemid) < 0)  {
                fprintf(stderr, "semDestroy failure\n");
        }
        if (semDestroy(semid1) < 0)  {
                fprintf(stderr, "semDestroy failure\n");
        }
        if(semDestroy(semid2)<0){
                fprintf(stderr, "semDestroy failure\n");
        }
        if (shmctl(shmid, IPC_RMID, 0) < 0){
                perror("shmctl");
                exit(1);
		}
}
