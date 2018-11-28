#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>

/*umask 특정 비트를 마스킹해서 1로 튀지 않도록 하는 시스템콜 그렇게 많이 쓰지는 않음.
mask(0)=> 마스크 안됨*/
main()
{
	umask(0);
	if (creat("bar", S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | 
				S_IROTH | S_IWOTH) < 0)  {
		perror("creat");
		exit(1);
	}

	umask(S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH);
	if (creat("foo", S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | 
				S_IROTH | S_IWOTH) < 0)  {
		perror("creat");
		exit(1);
	}
}
