#include <stdio.h>
#include <ctype.h>

#define MAX_BUF 1024

main(int argc, char* argv[])
{
	FILE *src;
	char buf[MAX_BUF];
	int count;

	printf("adasdas\n");
	if(argc!=2)
	{
		
		exit(1);
	}

	if((src = fopen(argv[1], "rb")) ==NULL)
	{
		perror("fopen");
		exit(1);
	}

	while((count = fread(buf,1,MAX_BUF,src))>0)
	{
		
	}
	printf(buf);
	int i;

	for(i=0;i<MAX_BUF;i++)
	{
		buf[i]=toupper(buf[i]);
	}
	printf(buf);
	fclose(src);
}
		
