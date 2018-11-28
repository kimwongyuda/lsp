#include <stdio.h>
#include <string.h>
void strupper(char str[])
{
	int i;
	int length = strlen(str);
	for (i=0;i<length;i++)
		str[i]=toupper(str[i]);
	printf("대문자열: %s\n",str);
}
main()
{
	char str[100];
	printf("문자열을 입력하세요: ");
	gets(str);
	strupper(str);
}
