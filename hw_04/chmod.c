#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>

main()
{
	struct stat	statbuf;
/*현재의 모드를 갖고와서 변경*/
	if (stat("bar", &statbuf) < 0)  {
		perror("stat");
		exit(1);
	}
/*group write 끄고 user execute는 S로그자리만 0 해서 곱함.??? S*/
/*우리들의 변경된 패스워드 etc -> shadow 밑에 저장 됨.
우리들이 read write 못함, super user, root가 가능 
set uid bit => 이거 켜진거 실행하면 이 프로그램 owner의 권한으로 실행한다.
루트권한 쉽게 획득 가능..? 
그 프로그램의 owner가 root!*/
	if (chmod("bar", (statbuf.st_mode & ~S_IWGRP) | S_ISUID) < 0)  {
		perror("chmod");
		exit(1);
	}

/*기존거 무시하고 이걸로*/
	if (chmod("foo", S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH) < 0)  {
		perror("chmod");
		exit(1);
	}
}
