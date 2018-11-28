#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include "shm.h"


main()
{
	int		shmid;
	char	*ptr, *pData;
	int		*pInt;


	if ((shmid = shmget(SHM_KEY, SHM_SIZE, SHM_MODE)) < 0)  {
		perror("shmget");
		exit(1);
	}
	if ((ptr = shmat(shmid, 0, 0)) == (void *) -1)  {
		perror("shmat");
		exit(1);
	}
	
	/*보통 피지컬 메모리를 0으로 초기화함 -> 따라서 0이면 아직 안쓰인거
	-> 쓰일때 까지 기다리는거 pInt => 4바이트의 포인터 
	다른 프로그램이 0이 아니라 1로 바꿔준다. = 메모리에 데이터를 썼구나 알수 있음.*/
	pInt = (int *)ptr;
	
	/*스핀락, 비지웨이팅, cpu 까먹음*/
	while ((*pInt) == 0)
		;

	pData = ptr + sizeof(int);
	printf("Received request: %s.....", pData);
	sprintf(pData, "This is a reply from %d.", getpid());
	*pInt = 0;
	printf("Replied.\n");
	
	/*이거 안하면 1초 안쉬니까 다른 프로세스가 메모리 정리할 시간 없이 아래
	강제로 피지컬 없애는거 실행됨*/
	sleep(1);

	if (shmctl(shmid, IPC_RMID, 0) < 0)  {
		perror("shmctl");
		exit(1);
	}
}
