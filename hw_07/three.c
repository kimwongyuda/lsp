#include <stdio.h>

#define MAX_BUF 256

/*파일 디스크립터로 파일을 연다. 그 후 strstr을 이용해 argv[1]이 문장에 있다면 line과 함께 출력해준다.*/
main(int argc, char *argv[])
{
	FILE *fp;
	char buf[MAX_BUF];
	int line;

	if ((fp=fopen(argv[2], "rb")) ==NULL)
	{
		perror("fopen");
		exit(1);
	}
	line = 1;
	while(fgets(buf, MAX_BUF, fp))
	{
		if(strstr(buf, argv[1])!=NULL)
		{
			printf("%d: %s", line, buf);
		}
		line++;
		
	}
	fclose(fp);
}
