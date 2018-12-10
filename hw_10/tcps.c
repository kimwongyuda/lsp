#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <signal.h>
#include "tcp.h"


int	Sockfd;

/*시그널 핸들러 (서버는 영원히 돌아가지만 죽이기도 해야되니 컨트롤+C의 그 경우)*/
void
CloseServer()
{
	close(Sockfd);
	printf("\nTCP Server exit.....\n");

	exit(0);
}


main(int argc, char *argv[])
{
	int					newSockfd, cliAddrLen, n;
	struct sockaddr_in	cliAddr, servAddr;
	MsgType				msg;

	signal(SIGINT, CloseServer);
	
	/*가급적이면 이거 전역변수 아니게 하는게 좋지만 시그널 핸들러 처리하기위해 Sockfd 전역변수로*/
	if ((Sockfd = socket(PF_INET, SOCK_STREAM, 0)) < 0)  {
		perror("socket");
		exit(1);
	}

	bzero((char *)&servAddr, sizeof(servAddr));
	servAddr.sin_family = PF_INET;
	servAddr.sin_addr.s_addr = htonl(INADDR_ANY);// 아이피 어드레스 와야되는데 INADDR_ANY옴 => 무슨의미? = 어떤 아이피로 와도 받겠다
	// 만약 그 외에 특정 아이피 넣으면 그 특정 아이피에서 오는거만 받겠다는것
	servAddr.sin_port = htons(SERV_TCP_PORT);// 7000+10 아이디!

	if (bind(Sockfd, (struct sockaddr *) &servAddr, sizeof(servAddr)) < 0)  {
		perror("bind");
		exit(1);
	}

	//일반적인 .. 
	listen(Sockfd, 5);

	printf("TCP Server started.....\n");

	cliAddrLen = sizeof(cliAddr);
	while (1)  {
		
		//사용자의 커넥션이 오기를 기다린다.
		//여기서 어셉트 디스크립터 생김(웹서버로 치면 80번)
		newSockfd = accept(Sockfd, (struct sockaddr *) &cliAddr, &cliAddrLen);
		if (newSockfd < 0)  {
			perror("accept");
			exit(1);
		}
		
		if ((n = read(newSockfd, (char *)&msg, sizeof(msg))) < 0)  {
			perror("read");
			exit(1);
		}
		printf("Received request: %s.....", msg.data);

		msg.type = MSG_REPLY;
		sprintf(msg.data, "This is a reply from %d.", getpid());
		if (write(newSockfd, (char *)&msg, sizeof(msg)) < 0)  {
			perror("write");
			exit(1);
		}
		printf("Replied.\n");

		usleep(10000);
		close(newSockfd);
	}
}
