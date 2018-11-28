#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

#define MAX_BUF 1024

main(int argc, char *argv[])
{
	int fd1, fd2, count;
	char buf[MAX_BUF];

	if(argc!=3)
	{
		printf("Usage: %s source destination\n", argv[0]);
		exit(1);
	}
	/*첫번째꺼 읽기로 열음*/
	if((fd1 = open(argv[1], O_RDONLY)) <0)
	{
		perror("open");
		exit(1);
	}
	/*두번째꺼 쓰기로 열음.*/
	if((fd2 = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC, 0644)) <0)
	{
		perror("open");
		exit(1);
	}
	/*첫번째꺼를 두번째꺼에 복사*/
	while((count=read(fd1,buf,MAX_BUF))>0)
	{
		printf("%dasdasd\n",count);
		write(fd2,buf,count);
	}
	close(fd1);
	close(fd2);
}
