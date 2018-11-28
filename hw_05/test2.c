#include <stdio.h>
#include <string.h>

main()
{
	char temp[100] = "ls -al";
	printf("%s\n",temp);
	
	char *temp2[100];
	char *ptr = strtok(temp," ");
	int count = 0;
	while(ptr !=NULL)
	{
		printf("%s\n", ptr);
		temp2[count] = ptr;
		ptr = strtok(NULL," ");
		count++;
	}

	for (int i =0;i<count;i++)
	{
		printf("%s\n", temp2[i]);
	}
}
