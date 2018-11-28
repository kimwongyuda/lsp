#include <stdio.h>
#include <signal.h>
#include <pwd.h>

/*리눅스는 알아서 막아놓음ㅑ*/
/*락 걸어놓음 이미 ptr에서! 하지만 이 핸들러가 리턴 되야 ptr로 가서 풀 수 있음... 따라서 rooptr 먼저 되면 안됨.... 데드락됨.*/
void
MyAlarmHandler(int signo)
{
	struct passwd	*rootptr;

	signal(SIGALRM, MyAlarmHandler);
	alarm(1);

	printf("in signal handler\n");

	if ((rootptr = getpwnam("root")) == NULL)  {
		perror("getpwnam");
		exit(1);
	}
	printf("%s\n",rootptr->pw_name);
	return;
}
/*getpwnam => 주소를 리턴, => 바뀜 값, 거기다 static*/
/*ptr도 rootptr도 다 getpwnam 스태틱 데이터 가리킴*/
main()
{
	struct passwd	*ptr;

	signal(SIGALRM, MyAlarmHandler);
	alarm(1);

	for ( ; ; )  {
		if ((ptr = getpwnam("lsp10")) == NULL)  {
			perror("getpwnam");
			exit(1);
		}
		
		if (strcmp(ptr->pw_name, "lsp10") != 0)  {
			printf("return value corrupted!, pw_name = %s\n", ptr->pw_name);
			exit(0);
		}
	}
}
