#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <dirent.h>
#include <pwd.h>
#include <grp.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
/*파라미터로 넣거나 malloc해서 반환*/
char* make_rwx(mode_t file_mode)
{
	/*is directory?*/
	char* str = malloc(15*sizeof(char));
	strcpy(str, "");
	if(S_ISDIR(file_mode))
	{
		strcat(str,"d");
	}
	else
	{
		strcat(str,"-");
	}

	/*owner*/
	if(file_mode&S_IRUSR)
		strcat(str,"r");
	else
		strcat(str,"-");
	if(file_mode&S_IWUSR)
        strcat(str,"w");
    else
        strcat(str,"-");
	if(file_mode&S_IXUSR)
        strcat(str,"x");
    else
        strcat(str,"-");

	/*group*/
	if(file_mode&S_IRGRP)
        strcat(str,"r");
    else
        strcat(str,"-");
    if(file_mode&S_IWGRP)
        strcat(str,"w");
    else
        strcat(str,"-");
    if(file_mode&S_IXGRP)
        strcat(str,"x");
    else
        strcat(str,"-");

	/*other*/
	if(file_mode&S_IROTH)
        strcat(str,"r");
    else
        strcat(str,"-");
    if(file_mode&S_IWOTH)
        strcat(str,"w");
    else
        strcat(str,"-");
    if(file_mode&S_IXOTH)
        strcat(str,"x");
    else
        strcat(str,"-");
	
	printf("%s\n",str);	
	return str;
}

main()
{
	DIR *dp;
	mode_t file_mode;
	struct dirent *dep;
	struct stat	statbuf;
	struct passwd	*pw;
	struct group	*group;
	struct tm *tminfo;
	char* rwx;
	char buf[100];

	if((dp = opendir("."))==NULL)
	{
		perror("opendir");
		exit(0);
	}

	while(dep = readdir(dp))
	{
		if(lstat(dep->d_name, &statbuf)<0)
		{
			perror("lstat");
			continue;
		}
		file_mode=statbuf.st_mode;
		rwx = make_rwx(file_mode);
		printf("%s ", rwx);
		printf("%d ", statbuf.st_nlink);
		pw = getpwuid(statbuf.st_uid);
		group = getgrgid(statbuf.st_gid);
		printf("%s ", pw->pw_name);
		printf("%s ", group->gr_name);
		printf("%d ", statbuf.st_size);
		tminfo = localtime(&(statbuf.st_mtime));
		strftime(buf, sizeof(buf), "%m/%d %H:%M", tminfo);
		printf("%s ", buf);
		printf("%s\n", dep->d_name);
	}

	closedir(dp);
}
		
