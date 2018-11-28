#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
int main()
{
	
	char asd[] = "adasdasda"; 
	char *argv[] = {"s","as","asd"};
	int a = sizeof(argv)/sizeof(argv[0]);
	int b = sizeof(asd);
	int c = 2;
	char temp[c][22];
	gets(temp[0]);
	gets(temp[1]);
	printf("%d size of temp\n", strlen(temp));
	printf("%s %s ssss\n",temp[0],temp[1]);
	printf("%d, %d\n",a,b);
	
	for ( int i =0 ;i<a;i++)
	{
		printf("%s\n",argv[i]);
	}
	return 0;
}
