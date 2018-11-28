#include <stdio.h>

main(int argc, char *argv[])
{
	/*파일을 읽고 쓰기 위한 포인터*/
	FILE *src, *dst;
	int ch;

	/*매개변수가3개 아닐시*/
	if(argc!=3)
	{
		fprintf(stderr, "Usage: %s source destination\n", argv[0]);
		exit(1);
	}
	/*첫번째 파일 읽기로 열음*/
	if((src = fopen(argv[1], "rt")) == NULL)
	{
		perror("fopen");
		exit(1);
	}
	/*두번째 파일 쓰기로 열음*/
	if((dst = fopen(argv[2], "wt"))==NULL)
	{
		perror("fopen");
		exit(1);
	}
	/*src에서 dst로 복사기능!*/
	while((ch=fgetc(src))!=EOF)
	{
		fputc(ch, dst);
	}
	fclose(src);
	fclose(dst);
}
