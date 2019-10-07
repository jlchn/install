#include <stdio.h>
#include <sys/stat.h>


int main(int ac, char * av[])
{
	struct stat info;// why cannot be * p_info

	if( ac == 1)
	{
		printf("usage: stat file_name");
		return 0;
	}

	if(stat(av[1], &info) == -1)
	{
		perror(av[1]);
		exit(1);
	}

	printf("%o %d %d %d %d %d %s\n", info.st_mode, info.st_nlink, info.st_uid, info.st_gid, info.st_size, info.st_mtime, av[1]);
}
