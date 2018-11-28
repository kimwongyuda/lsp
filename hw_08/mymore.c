#include <stdio.h>


#include <stdlib.h>
#include <unistd.h>

int main() 
{
	int fd[2];
	pid_t child;
	/*예제로 아주 좋다고 하심*/
	/*pipe로 열리는지 확인*/
	if(pipe(fd) == -1)  {
		perror("pipe");
		exit(1);
	}

	/*fork를 한다.*/
	child = fork();
	/*fork안되면? 에러*/
	if(child == (pid_t)(-1))  {
        	perror("fork");
		exit(1);
	}
	else if(child == (pid_t)0) {
        	close(1);
		close(fd[0]);
        	
			/*fd[1] 파이프로 내보냄. 그치만 여기 뭐라 연결해라 없음 => dup
			dup2는 뒤에 파라미터가 한개 더 붙어서 뭐랑 연결해라 있음.
			dup2는 뒤에 0,1 등 stdin, stdout으로 복제해라 나옴.
			dup2쓰는거랑 close(1) + dup 사용이랑 같음.*/
        	if(dup(fd[1]) == -1)  {
        		perror("dup");
			exit(1);
		}
			/*system은 차일드 만들고 그거로 실행, exec은 자기가 실행하고 자기 없어짐*/
        	if((execlp("ls", "ls", "-l", NULL)) == -1)  {
        		perror("execlp");
			exit(1);
		}
	} 
	else {
        	close(0);
		close(fd[1]);
        	
        	if(dup(fd[0]) == -1)  {
        		perror("dup");
			exit(1);
		}

        	if((execlp("more", "more", NULL)) == -1)  {
        		perror("execlp");
			exit(1);
		}
	}
 
	return 0;
}
