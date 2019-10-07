#include <fcntl.h>
#include <stdio.h>
#include <utmp.h>
#include <unistd.h>
#include <time.h>
#define SHOWHOST
int main()
{
	struct utmp record;
	int rec_len = sizeof(record);

	int fd = open("/var/run/utmp",O_RDONLY);
	if (fd == -1)
	{
		perror(UTMP_FILE);
		exit(1);
	}
	
	while(read(fd, &record, rec_len) == rec_len)
	{
		if(record.ut_type != USER_PROCESS)
		{
			continue;
		}	
		printf("% - 8.8s ", record.ut_name);
		printf("% - 8.8s ", record.ut_line);
		long int t = record.ut_time;
		printf("%s ", 4 + ctime(&t));
		#ifdef SHOWHOST
		printf("%s", record.ut_host);
		#endif
	}
	close(fd);
	return 0;
}
