#include <stdio.h>

#define	MAX_BUF	256

main(int argc, char *argv[])
{
	FILE	*src, *dst;
	char	buf[MAX_BUF];

	/*매개변수3개*/
	if (argc != 3)  {
		fprintf(stderr, "Usage: %s source destination\n", argv[0]);
		exit(1);
	}
	/*첫번째 파일 포인터로 읽음*/
	if ((src = fopen(argv[1], "rt")) == NULL)  {
		perror("fopen");
		exit(1);
		}
	/*두번째 파일 읽음*/
	if ((dst = fopen(argv[2], "wt")) == NULL)  {
		perror("fopen");
		exit(1);																		}
	while (fgets(buf, MAX_BUF, src) != NULL)
	/*문장 단위로 복사*/
	{fputs(buf,dst);
																					}
																					fclose(src);
																					fclose(dst);
																				}
