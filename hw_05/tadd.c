#include <stdio.h>
#include <pthread.h>

void *sum(void *num)
{
	int sum = *(int*)num;
	if(sum==1)
	{
		sum =0;
		int i;
		for(i = 1;i<51;i++)
			sum+=i;
	}
	if(sum==51)
	{
		sum = 0;
		int i;
		for(i=51;i<101;i++)
			sum+=i;
	}
	printf("%d:...thread에서 합\n",sum);
	/*return 대신 pthread_exit((void*)&sum*/
	return (void*)sum;

}
main()
{
	pthread_t tid1,tid2;
	int sum1=1, sum2=51;

	if (pthread_create(&tid1, NULL, sum, (void *)&sum1)<0)
	{
		perror("thread create error:");
		exit(1);
	}
	if (pthread_create(&tid2, NULL, sum, (void *)&sum2)<0)
	{
		perror("thread create error:");
		exit(1);
	}
	
	if (pthread_join(tid1,(void**)&sum1)<0){
		perror("pthread_join");
		exit(1);
	}
	
	if (pthread_join(tid2,(void**)&sum2)<0){
		perror("pthread_join");
		exit(1);
	}

	printf("%d 는 총합\n", sum1+sum2);
}
