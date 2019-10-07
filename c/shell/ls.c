#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>
#include <sys/stat.h>
#include <pwd.h>
#include <grp.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

void do_ls(char[]);
void mode_to_letters(int, char[]);
char * uid_to_name(uid_t);
char * gid_to_name(gid_t);// why gid_t

int main(int ac, char * av[]) // why * []
{
	if ( ac == 1)
	{
		do_ls(".");
	}
	else
	{
		while (--ac)
		{
			do_ls(* ++av);// attention
		}
	}

	return 0;
}


void do_ls(char dir_name[])
{
	printf("%s:\n", dir_name);
	DIR * p_dir; // opendir return the pointer to the dir stream
	struct dirent * p_entry; 
	if(( p_dir = opendir(dir_name)) == NULL)
	{
		fprintf(stderr, "cannot open ");
		perror(dir_name);
		exit(1);
	}
	else
	{
		while(( p_entry = readdir(p_dir)) != NULL)
		{
			struct stat info;
			if(stat(p_entry->d_name, &info) == -1)
			{
				perror(p_entry->d_name);
				exit(1);
			}
			char modestr[11];
			mode_to_letters(info.st_mode, modestr);
			printf("%s", modestr);
			printf("%4ld ", info.st_nlink);
			printf("%-8s ", uid_to_name(info.st_uid));
			printf("%-8s ", gid_to_name(info.st_gid));
			printf("%8ld ", info.st_size);
			printf("%.12s ", 4 + ctime(&info.st_mtime));// if don't include <time.h>, there would be segment fault, why?
			printf("%s\n", p_entry->d_name);
		}

		closedir(p_dir);
	}

}

void mode_to_letters(int mode, char str[])
{
	strcpy(str, "----------");

	if(S_ISDIR(mode)) str[0] = 'd';
	if(S_ISCHR(mode)) str[0] = 'c';
	if(S_ISBLK(mode)) str[0] = 'b';
	if(S_IRUSR & mode) str[1] = 'r';
	if(S_IWUSR & mode) str[2] = 'w';
	if(S_IXUSR & mode) str[3] = 'x';
	if(S_IRGRP & mode) str[4] = 'r';
	if(S_IWGRP & mode) str[5] = 'w';
	if(S_IXGRP & mode) str[6] = 'x';
	if(S_IROTH & mode) str[7] = 'r';
	if(S_IWOTH & mode) str[8] = 'w';
	if(S_IXOTH & mode) str[9] = 'x';
}
char * uid_to_name(uid_t uid)
{
	struct passwd * getpwuid(), * pw_str; // what?
	static char ret[10];

	if( (pw_str = getpwuid(uid)) == NULL)
	{
		sprintf(ret, "%d", uid);// cast to char[]
		return ret;
	}
	return pw_str->pw_name;
}

char * gid_to_name(gid_t gid)
{
	struct group * getgrgid(), * grp_str;
	static char ret[10];

	if((grp_str = getgrgid(gid)) == NULL)
	{
		sprintf(ret, "%d", gid);
		return ret;
	}

	return grp_str->gr_name;
}
