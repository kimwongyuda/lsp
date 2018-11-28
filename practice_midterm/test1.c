#include <stdio.h>
#include <string.h>

main(int argc, char *argv[])
{
	int a;
	a = atoi(argv[1]);
	int b;
	
	b = strlen(argv[1]);
	printf("%d, %d\n",a,b);
}
