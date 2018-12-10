#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/time.h>
#include "prodcons.h"

char buf[1024];

pthread_cond_t request;
pthread_cond_t reply;
pthread_cond_t Mutex;

void
sipc2(void *dummy)
{

                //lock mutex
                if (pthread_mutex_lock(&Mutex)<0)  {
                        perror("pthread_mutex_lock");
                        pthread_exit(NULL);
                }
                sprintf(buf,"This is a request from %ud",(int)pthread_self());
                printf("2: Sent a request. . . \n");

                // signal to request
                if (pthread_cond_signal(&request)<0)  {
                        perror("pthread_cond_signal");
                        pthread_exit(NULL);
                }
                // unlock mutex
                if (pthread_mutex_unlock(&Mutex)<0)  {
                        perror("pthread_mutex_unlock");
                        pthread_exit(NULL);
                }
                //wait for reply
                if (pthread_cond_wait(&reply, &Mutex) < 0)  {
                        perror("pthread_cond_wait");
                        pthread_exit(NULL);
                }


                printf("2: Received reply: %s\n", buf);

        pthread_exit(NULL);
}

void
sipc1(void *dummy)
{
        int             i, data;
                //lock mutex
                if (pthread_mutex_lock(&Mutex) < 0)  {
                        perror("pthread_mutex_lock");
                        pthread_exit(NULL);
                }
                //wait for request
                if (pthread_cond_wait(&request, &Mutex) < 0)  {
                        perror("pthread_cond_wait");
                        pthread_exit(NULL);
                }


                printf("1: Received request: %s......\n",buf);
                sprintf(buf,"This is a reply from %ud",(int)pthread_self());

                //signal to reply
                if (pthread_cond_signal(&reply) < 0)  {
                        perror("pthread_cond_signal");
                        pthread_exit(NULL);
                }
                //unlock mutex
                if (pthread_mutex_unlock(&Mutex) < 0)  {
                        perror("pthread_mutex_unlock");
                        pthread_exit(NULL);
                }

                printf("1: Replied.\n");


        sleep(1);

        pthread_exit(NULL);
}

main()
{
        pthread_t       tid1, tid2;

        srand(0x8888);
        //initiate condition valuables
        if (pthread_cond_init(&request, NULL) < 0)  {
                perror("pthread_cond_init");
                pthread_exit(NULL);
        }
        if (pthread_cond_init(&reply, NULL) < 0)  {
                perror("pthread_cond_init");
                pthread_exit(NULL);
        }
        //initiate mutex
        if (pthread_mutex_init(&Mutex, NULL) < 0)  {
                perror("pthread_mutex_init");
                pthread_exit(NULL);
        }
        //create threads
        if (pthread_create(&tid1, NULL, (void *)sipc1, (void *)NULL) < 0)  {
                perror("pthread_create");
                exit(1);
        }

        if (pthread_create(&tid2, NULL, (void *)sipc2, (void *)NULL) < 0)  {
                perror("pthread_create");
                exit(1);
        }
        //wait threads to be terminated
        
        if (pthread_join(tid1, NULL) < 0)  {
                perror("pthread_join");
                exit(1);
        }
        if (pthread_join(tid2, NULL) < 0)  {
                perror("pthread_join");
                exit(1);
        }

        //destroy condition values and mutex
        if (pthread_cond_destroy(&request) < 0)  {
                perror("pthread_cond_destroy");
        }
        if (pthread_cond_destroy(&reply) < 0)  {
                perror("pthread_cond_destroy");
        }
        if (pthread_mutex_destroy(&Mutex) < 0)  {
                perror("pthread_mutex_destroy");
        }
		
}

