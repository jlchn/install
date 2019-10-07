#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

#define BUFFERSIZE 4096
#define COPYMODE 0644

int main(int ac, char * av[])
{
	int in_fd;
	int out_fd;
	int n_chars;
	char bf[BUFFERSIZE];

	if(ac != 3)
	{
		fprintf(stderr, "usage: %s source destination\n", av[0]);
		exit(1);
	}

	if((in_fd = open(av[1], O_RDONLY)) == -1)
	{
		fprintf(stderr, "cannot open ");
		perror(av[1]);
		exit(1);
	}

	if((out_fd = creat(av[2], COPYMODE)) == -1)
	{
		fprintf(stderr, "cannot create ");
		perror(av[2]);
		exit(1);
	}

	while((n_chars = read(in_fd, bf, BUFFERSIZE)) > 0 )
	{
		printf("%c, %d",bf[0], n_chars);
		if(write(out_fd, bf, n_chars) != n_chars)
		{
			fprintf(stderr, "failed to write to ");
			perror(av[2]);
			exit(1);
		}

	}

	if(n_chars == -1)
	{
		fprintf(stderr, "failed to read from ");
		perror(av[1]);
		exit(1);
	}

	if(close(in_fd) == -1 || close(out_fd) == -1)
	{
		fprintf(stderr, "error close files");
		exit(1);
	}


	return 0;
}
