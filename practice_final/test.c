#include <stdio.h>

main()
{
	char s1[10];
	int num = 222;

	sprintf(s1, "%d\n", num);

	printf("%s\n", s1);

	return 0;
}
