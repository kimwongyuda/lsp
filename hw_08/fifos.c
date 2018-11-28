#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <signal.h>
#include <errno.h>
#include "fifo.h"

/*애는 서버라 끝날때 까지 계속 종료 => SIGINT 이용
서버 fifo 없애고 종료*/
void
SigIntHandler(int signo)
{
	if (remove(SERV_FIFO) < 0)  {
		perror("remove");
		exit(1);
	}

	exit(0);
}


main()
{
	int			fd, cfd, n;
	MsgType		msg;

	if (signal(SIGINT, SigIntHandler) == SIG_ERR)  {
		perror("signal");
		exit(1);
	}

	/*fifo 만듬. 0600 -> 내 id로 만들어진 프로세스들만 보낼 수 있음 0110?*/
	/*서버 피포 만드는거 ./.fifo -> 근데 이미 만들어진 fifo있으면 안됨. 없어야 만들수 있음 => 
	이미 있을시 에러*/
	if (mkfifo(SERV_FIFO, 0600) < 0)  {
		if (errno != EEXIST)  {
			perror("mkfifo");
			exit(1);
		}
	}
	
	/*피포 오픈*/
	if ((fd = open(SERV_FIFO, O_RDWR)) < 0)  {
		perror("open");
		exit(1);
	}

	while (1)  {
		/*만든 피포, 구조체 시작 주소, 구조체 크기
		읽기 기다리고 있음.*/
		
		if ((n = read(fd, (char *)&msg, sizeof(msg))) < 0)  {
			/*시그널 발생해서 잠자다 깨는건데 이거 때문에 종료되면 안되니 이경우 continue
			EINTR = interupt*/
			if (errno == EINTR)  {
				continue;
			}
			else  {
				perror("read");
				exit(1);
			}
		}
		printf("Received request: %s.....", msg.data);

		if ((cfd = open(msg.returnFifo, O_WRONLY)) < 0)  {
			perror("open");
			exit(1);
		}
		sprintf(msg.data, "This is a reply from %d.", getpid());
		write(cfd, (char *)&msg, sizeof(msg));
		close(cfd);
		printf("Replied.\n");
	}
}
