#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>

#define	ARRAY_SIZE	40000
#define	MALLOC_SIZE	100000
#define	SHM_SIZE	100000
#define	SHM_MODE	(SHM_R | SHM_W)

char	Array[ARRAY_SIZE];

main()
{
	int		shmid;
	char	*ptr, *shmptr;
	
	/*heap 영역 사용한다. 프로세스 메모리 주소(포인터로)*/
	if ((ptr = (char *)malloc(MALLOC_SIZE)) == NULL)  {
		perror("malloc");
		exit(1);
	}
	
	/*sh 만듬, (키, ) 두 개의 프로세스가 똑같은 메모리 접근할때는 특정 키 이름
필요하다 하지만 여기서는 프로세스 한개 => IPC_PRIVATE -> 이 프로세스 종료되면
직접 지우지 않아도 알아서 지워짐. 키 값을 주면 프로세스 종료되도 physical 남아있다. IPC_PRIVATE 언제씀? fork 했을때 이름없는 physical 부모 자식이 공유하게 됨.
부모, 자식 둘다 종료되면 아까처럼 반환.*/
	if ((shmid = shmget(IPC_PRIVATE, SHM_SIZE, SHM_MODE)) < 0)  {
		perror("shmget");
		exit(1);
	}

	/*실제 피지컬에 attach 하는 과정*/
	if ((shmptr = shmat(shmid, 0, 0)) == (void *) -1)  {
		perror("shmat");
		exit(1);
	}
	
	/*Array => data 세그먼트에 있음
	shmid는 local => stack에 있음.
	malloc은 힙
	
	그다음 shmptr도 heap
	맨아래가 0이니 Array의 logical 주소가 가장 커야댐.*/

	printf("Array[] from %x to %x\n", &Array[0], &Array[ARRAY_SIZE]);
	printf("Stack around %x\n", &shmid);
	printf("Malloced from %x to %x\n", ptr, ptr+MALLOC_SIZE);
	printf("Shared memory attached from %x to %x\n", shmptr, shmptr+SHM_SIZE);

	/*shm 다쓰고 죽이는거 하지만 IPC_PRIVATE하면 이거 아라서 해줌*/
	if (shmctl(shmid, IPC_RMID, 0) < 0)  {
		perror("shmctl");
		exit(1);
	}
}
