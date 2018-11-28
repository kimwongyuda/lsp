#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

main()
{
	int fd;
	char ch = '\0';
	/*file.hole 파일 만듬.*/
	if((fd = creat("file.hole", 0400)) < 0) 
	{
		perror("creat");
		exit(1);
	}
	/*저 파일에서 1023칸 만큼 띄어져서 */
	if(lseek(fd,1023,SEEK_SET) <0)
	{
		perror("lseek");
		exit(1);
	}

	/*이거 출력*/
	write(fd, &ch, 1);

	close(fd);
}
