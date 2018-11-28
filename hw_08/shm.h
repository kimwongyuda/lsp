#define	MY_ID		10	
#define	SHM_KEY		(0x9000 + MY_ID)
#define	SHM_SIZE	1024
#define	SHM_MODE	(SHM_R | SHM_W | IPC_CREAT)

/*문제 0으로 쓰고 0으로 쓰고 하면 문제가 된다.
나는 lsp10인데 MY_ID에 09 넣으면 어케 되냐? 안됨 16진수로 써야됨.
자기 ID 넣기*/
