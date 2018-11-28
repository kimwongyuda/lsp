#include <stdio.h>
#include "synclib.h"

#define	NLOOPS	5


main()
{
	int		i;
	pid_t	pid;
	/*두 개의 파일 pipe 로 가능한지 확인!
	여기서는 두개, 부모도 읽고 쓰게 만듬*/
	TELL_WAIT();
	if ((pid = fork()) < 0)  {
		perror("fork");
		exit(1);
	}
	/*wait=> 부모가 쓰길 기다림 (반대로도 가능), tell=>부모가 쓰고 자식에게 알림.*/
	else if (pid > 0)  {
		for (i = 0 ; i < NLOOPS ; i++)  {
			TELL_CHILD();
			printf("Parent: Tell to child\n");
			printf("Parent: Wait for child to tell\n");
			WAIT_CHILD();
		}
	}
	else  {
		for (i = 0 ; i < NLOOPS ; i++)  {
			printf("Child: Wait for parent to tell\n");
			WAIT_PARENT();
			TELL_PARENT();
			printf("Child: Tell to parent\n");
		}
	}
}
