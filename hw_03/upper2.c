#include <stdio.h>
#include <ctype.h>

#define MAX_BUF 1024

main(int argc, char* argv[])
{
	FILE *src;
	char buf[MAX_BUF];
	int count;

	if(argc!=2)
	{
		printf("error\n");
		exit(1);
	}

	if((src = fopen(argv[1], "rb")) ==NULL)
	{
		perror("fopen");
		exit(1);
	}

	while((count = fread(buf,1,MAX_BUF,src))>0)
	{

		printf(toupper(buf));
	}
	fclose(src);
}
		
