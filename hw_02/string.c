#include <stdio.h>
#include <string.h>
/* "hello"라는 값의 첫번째 문자를 *str이 가리킨다.
while문에서 보면 *str++이라는 부분이 있는데 디버깅을 해서 봤을 때
맨처음 *str값은 'h'라는 값을 가리키고 쭉쭉 돌리다가 마지막 '\0'값
까지 하고 while문은 끝나게 된다.*/
int strlen_p(char *str)
{
	int len = 0;
	while(*str++)
	{
		len++;
	}
	return len;
}

/* "hello"라는 값이 문자열로 파라미터로 넘어온다.
문자 배열로 그 값을 받고 for문에서 캐릭터 배열 마지막에 있는
'\0' 값이 나올 때까지 i값을 키워 길이를 구한다*/
int strlen_a(char str[])
{
	int i;
	for(i=0; str[i]!= '\0';i++);	
	
	return i;
}


/*첫번째 파라미터에는 빈 문자 배열이 오고 
두번째 파라미터에는"hello"라는 값을 가진  캐릭터 배열이 파라미터로 온다
while문은 의미가 없는 '\0'값이 나올때 까지만 돈다
*dst는 아직 빈포인터를 가리키고 있다.
*src는 h라는 값을 가리키고 *dst에 넣어준다.
그다음 두 포인터를 둘다 다음 배열의 요소를 가리키게 한다.
반복하여 값을 복사한다.
*/
void strcpy_p(char *dst, char*src)
{
	while(*src)
	{
		*dst++ = *src++;
	}
	*dst = *src;
}

/*배열이 그대로 파라미터로 전해진다.
for문은 src[i]값이 문자 배열 마지막 의미없는 값인 '\0'값이 나올때 까지 for문을 돌고 그 값을 dst[i]에 넣어 준다.*/
void strcpy_a(char dst[], char src[])
{
	int i;

	for(i=0;src[i] !='\0';i++)
		dst[i] = src[i];
	printf("마지막 이거 왜함? %cqweq \n", src[i]);
	dst[i]=src[i];
}
/* 위 과정에서 *dst 는 hello라는 배열의 마지막 요소를 가리키게 된다. *src는 새로 들어온 ",World!"중 ','를 가리킨다 *dst가 이제 배열의 끝 주소를 가리키기 위해 while문 과 같은 작업을 수행하고 그러면 '\0'을 가리키게 된다. 그 다음 dst--로 하여 '\0' 전 의 요소를 가리키게 하고 그다음 while(*src)를 통해 위에서와 마찬가지로 *dst를 , W o r l d ! 요소 한개씩 점차 가리키게하여 Hello ,World를 만든다*/
void strcat_p(char *dst, char *src)
{
	while (*dst++);

	dst--;
	while(*src)
	{
		*dst++ = *src++;
	}
	*dst = *src;
}

/*파라미터로 들어온 dst[]가 끝 요소인 '\0'을 가리키기 위해 for문을 돌리고 그에 맞는 index를 찾기 위해  i를 증가 시킨다. 그 다음 위에서 했듯이 src의 문자 배열에서 마지막 요소인'\0'가 나올 때까지 for문 돌면서 dst 배열에 추가해준다.*/
void strcat_a(char dst[], char src[])
{
	int i, j;
	for(i =0; dst[i] !='\0'; i++);

	for(j=0;src[j]!='\0'; j++)
		dst[i+j] = src[j];
	dst[i+j] = src[j];
}

/* *dst는 들어온 파라미터의 첫번째 문자를 가리키고 src도 마찬가지이다 while문을 돌려서 위에 방법과 마찬가지로 계속 인덱스 별로 문자를 비교하다가 만약 다르다면 while문을 멈추고 다르다는것을 리턴하고 같다면 문자 배열 길이까지 진행하여 1을 리턴한다.*/
int strcmp_p(char *dst, char *src)
{
	int index=0;
	int correct = 1;
		
	while(*dst)
	{
		printf("dst: %c, src: %c \n",*dst,src[index]);
		if(*dst++==*src++)
		{
			printf("아직까진 같은 문자\n");
			index++;
		}
		else
		{
			correct = 0;
			break;
		}
		
	}
	if(correct ==0)
		return 0;
	else
		return 1;
}
/*배열로 문자 배열을 보내준다. for문으로 같은 인덱스의 문자를 비교해가며 만약 다를 시 correct를 0으로 바꾸어 마지막에 리턴한다. 만약 다르다면 0이, 같다면 1이 리턴된다.*/
int strcmp_a(char dst[], char src[])
{
	int i;
	int correct = 1;

	for(i=0;dst[i]!='\0';i++)
	{
		printf("dst: %c, src: %c \n", dst[i], src[i]);
		if(dst[i]!=src[i])
			correct=0;
	}
	if(correct==0)
		return 0;
	else
		return 1;
}

main()
{
	int len1, len2;
	char str1[20], str2[20];

	/*문자 길이 구하기*/
	len1 = strlen_p("Hello");
	len2 = strlen_a("Hello");
	printf("strlen: p=%d, a=%d\n", len1, len2);
	
	/*문자 복사*/
	strcpy_p(str1, "Hello");
	strcpy_a(str2, "Hello");
	printf("strcpy: p=%s, a=%s\n", str1, str2);

	/*문자 더하기*/
	strcat_p(str1, ",World!");
	strcat_a(str2, ",World!");
	printf("strcat: p=%s, a=%s\n", str1, str2);

	/*문자 비교 Hello,World와 Hello,World!를 비교해 0이 나오게함(틀림)*/
	printf("0: not same, 1: same\n is it same? %d\n", strcmp_p(str1, "Hello,World"));
	printf("0: not same, 1: same\n is it same?? %d\n", strcmp_a(str1, "Hello,World"));

	char test_str1[10]="q1";
	char test_str2[10]="q2";
	strcat(test_str1,test_str2);
	printf("%s\n",test_str1);
}







