#include <stdio.h>

main()
{
	int i;
	int j;

	for(i=9;i>0;i--)
	{
		for(j=1;j<i+1;j++)
		{
			printf("%d ",j);
		}
		printf("\n");
	}
}
