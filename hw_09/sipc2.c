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
        int             shmid,semid1,semid2,mutexSemid;
        char     *ptr, *pData;

        //create a shared memory
        if ((shmid = shmget(SHM_KEY, SHM_SIZE, SHM_MODE)) < 0)  {
                perror("shmget");
                exit(1);
        }
        //attach shared memory to ptr
        if ((ptr = shmat(shmid, 0, 0)) == (void *) -1)  {
                perror("shmat");
                exit(1);
        }

        //initate semaphores
         if ((semid1 = semInit(SEM1_SEM_KEY)) < 0)  {
                fprintf(stderr, "semInit failure\n");
                exit(1);
        }
         if ((semid2 = semInit(SEM2_SEM_KEY)) < 0)  {
                fprintf(stderr, "semInit failure\n");
                exit(1);
        }
        if ((mutexSemid = semInit(MUTEX_SEM_KEY)) < 0)  {
                fprintf(stderr, "semInit failure\n");
                exit(1);
        }

         //set semaphore value
        if (semInitValue(semid1, 0) < 0)  {
                fprintf(stderr, "semInitValue failure\n");
                exit(1);
        }
        if (semInitValue(semid2, 0) < 0)  {
                fprintf(stderr, "semInitValue failure\n");
                exit(1);
        }
        if (semInitValue(mutexSemid, 1) < 0)  {
                fprintf(stderr, "semInitValue failure\n");
                exit(1);
        }

        pData = ptr;
        //wait for mutex
        if(semWait(mutexSemid)<0){
                fprintf(stderr,"semWait failure\n");
                exit(1);
        }
        sprintf(pData, "This is a request from %d.", getpid());

        printf("Sent a request.....");
        //post to mutex
        if(semPost(mutexSemid)<0){
                fprintf(stderr,"semPost failure\n");
                exit(1);
        }
        //post to sem2(request)
        if(semPost(semid2)<0){
                fprintf(stderr,"semPost failure\n");
                exit(1);
        }
        //wait for sem1(replqy)
        if(semWait(semid1)<0){
                fprintf(stderr,"semWait failure\n");
                exit(1);
        }
        printf("Received reply: %s\n", pData);
}
