#include <stdio.h>

main(int argc, char *argv[])
{
	FILE *src;
	char buf[1024];
	int count;
	int length;
	if (argc!=2)
	{
		printf("에러\n");
		exit(1);
	}

	if((src = fopen(argv[1],"rb"))==NULL)
	{
		perror("fopen");
		exit(1);
	}

	while((count=fread(buf,1,1024,src))>0)
	{
		length = count;
		printf("%d  = length: \n",count);
	}
	
	int i;
	int word_count = 0;
	int flag = 0;
	for (i = 0;i<length;i++)
	{
		printf("%c",buf[i]);
		if(buf[i]==' ')
		{
			if(flag ==0)
			{
				flag=1;
				
				printf("\n");
			}
			
		}
		else
		{
			if(flag==1)
				if(buf[i]!='\n')
					word_count++;
			flag=0;
		}
		
	}

	printf("%d 카운트 갯수 입니다.\n",word_count);
	fclose(src);
}
