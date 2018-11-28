#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>

main()
{
	char cmd[100];
	gets(cmd);
	char *ptr = strtok(cmd," ");
	int a =strlen(ptr);
	printf("%d\n",a);
	char *temp[100];
	int count = 0;
	while(ptr !=NULL)
	{
		printf("%s\n", ptr);
		temp[count]=ptr;
		ptr = strtok(NULL, " ");
		count++;
	}
	
	for(int i=0;i<count;i++)
		printf("%s...\n",temp[i]);
	
}
