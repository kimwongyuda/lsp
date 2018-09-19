#CC = 어떤 컴파일러를 사용할 것인지에 대한 매크로
#CFLAGS = 컴파일 되지 않을 시 오류를 출력하게 하는 옵션의 매크로
#TARGET = 실행파일 매크로
#OBJECTS = 오브젝트 파일 모아놓은 매크로
CC = gcc
CFLAGS = -W -Wall
TARGET = diary_exe
OBJECTS = memo.o main.o calendar.o

#사실 all은 여러 개의 타겟 파일이 존재할 때 쓰는 옵션인데 1개도 가능
all : $(TARGET)

#타겟은 오브젝트 파일로 CC와 CFLAGS의 컴파일 과정을 통해 이루어진다.
#하지만 여기서는 오브젝트 파일로 실행파일을 만들 때를 의미
#-o는생성될 파일의 이름을 지정하는 옵션이다.
#$@는 첫번째인 타겟을 의미
#$^ 두번째인 오브젝트파일 리스트들을 의미
$(TARGET) : $(OBJECTS)
	$(CC) $(CFLAGS) -o $@ $^

#CC라는 컴파일러와 CFLAG라는 컴파일 오류 잡는 것을 통해 오브젝트 파일을 만든다.
#-c는 object 파일을 각 c파일에서 생성시켜준다.
#-o는 생성될 파일 이름을 지정하는 옵션이다. 그렇지 않으면 a.out이 생김.
memo.o : memo.c
	$(CC) $(CFLAGS) -c -o memo.o memo.c
calendar.o : calendar.c
	$(CC) $(CFLAGS) -c -o calendar.o calendar.c
main.o : main.c
	$(CC) $(CFLAGS) -c -o main.o main.c

#더미타겟으로 make clean 입력시 .o파일과 diary_exe 파일이 없어지도록 해놨다.
clean :
	rm *.o diary_exe
