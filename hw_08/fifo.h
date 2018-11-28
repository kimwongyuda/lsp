#define	MAX_FIFO_NAME	32

/*이게 well-known fifo*/
#define	SERV_FIFO	"./.fifo"

/*이게 클라이언트 마다 있는 fifo
data에 원하는 정보*/
typedef struct  {
	char	returnFifo[MAX_FIFO_NAME];
	char	data[128];
}
	MsgType;
