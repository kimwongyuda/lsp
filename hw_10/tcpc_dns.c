#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include "tcp.h"

//이거는 ip주소 이제 다른걸로.. 하드 코딩 말고
//udp도 이렇게 가능
main(int argc, char *argv[])
{
	int					sockfd, n;
	struct sockaddr_in	servAddr;
	MsgType				msg;
	struct hostent		*hp;

	if (argc != 2)  {
		fprintf(stderr, "Usage: %s IPaddress\n", argv[0]);
		exit(1);
	}

	if ((sockfd = socket(PF_INET, SOCK_STREAM, 0)) < 0)  {
		perror("socket");
		exit(1);
	}

	bzero((char *)&servAddr, sizeof(servAddr));
	servAddr.sin_family = PF_INET;
	servAddr.sin_port = htons(SERV_TCP_PORT);
	
	//0~9이면 숫자로 되면
	if (isdigit(argv[1][0]))  {
		servAddr.sin_addr.s_addr = inet_addr(argv[1]);
	}

	//문자면
	//근데 만약에 숫자인데 get으로 되면 어케..?
	else  {
		if ((hp = gethostbyname(argv[1])) == NULL)  {
			fprintf(stderr, "Unknown host: %s\n", argv[1]);
			exit(1);
		}
		memcpy(&servAddr.sin_addr, hp->h_addr, hp->h_length);
	}
	
	//뒤는 똑같다!
	if (connect(sockfd, (struct sockaddr *) &servAddr, sizeof(servAddr)) < 0)  {
		perror("connect");
		exit(1);
	}

	msg.type = MSG_REQUEST;
	sprintf(msg.data, "This is a request from %d.", getpid());
	if (write(sockfd, (char *)&msg, sizeof(msg)) < 0)  {
		perror("write");
		exit(1);
	}
	printf("Sent a request.....");
		
	if ((n = read(sockfd, (char *)&msg, sizeof(msg))) < 0)  {
		perror("read");
		exit(1);
	}
	printf("Received reply: %s\n", msg.data);

	close(sockfd);
}
