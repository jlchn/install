#include <stdio.h>
#include <unistd.h>

int main()
{
	char str[40];

	for (int x = 0 ; x < 40; x++)
	{
		str[x] = ' ';
	}	
 
	for(int x = 0; x < 40; x++)
	{
		sleep(1);
		str[x] = '#';
		
		/**
		 * we can get floating point division by converting one of the mumbers to double first.
		 **/
		printf("\r[%s] %d%%",str, (int)( ((double)x) / 39 * 100));
    		
		/*
		 * the output of printf is buffered, 
		 * meaning that the output appears on the console only if 
		 * we explicitly call fflush(stdout), print a newline, or the buffer becomes full.
		 * */
		fflush(stdout);
 	}
	printf("\n");
 	return 0;
}
