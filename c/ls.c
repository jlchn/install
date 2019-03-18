#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>

void do_ls(char[]);

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
			printf("%s \n", p_entry->d_name);
		}

		closedir(p_dir);
	}

}
