#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>


int main()
{

	int fd;
	struct flock testlock;
	int pid;
	
	testlock.l_type = F_WRLCK; 
	testlock.l_whence = SEEK_SET;
	testlock.l_start = 0;
	testlock.l_len = 10;
				
	
	fd = open("testlock", O_RDWR | O_CREAT, 0666);
	
	if(fcntl (fd, F_SETLKW, &testlock) == -1)
	{
		perror("parent : locking");
		exit(1);
	}

	printf("Parent : locked record\n");
	
	pid = fork();
	
	if(pid == 0)
	{
		testlock.l_len = 5;
		
		if(fcntl (fd, F_SETLKW, &testlock) == -1)
		{
			printf("Child : locked\n");
			exit(1);
		}
		printf("Child : locked\n");
		sleep(5);
		printf("Child : exiting\n");
	}
	else if (pid > 0)
	{
		sleep(5);
		printf("Parent : exiting\n");
	}
	else
	{
		perror("fork failed");
	}
	return 0;
}
