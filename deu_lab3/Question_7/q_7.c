#include <stdio.h>
#include <signal.h>
#include <sys/types.h>
#include <unistd.h>



int i = 0;
void p_handler (int);	
void c_handler (int);


int main()
{

	pid_t pid, ppid;
	struct sigaction act;

	pid = fork();

	
	if(pid == 0)
	{
		act.sa_handler = c_handler;
		sigaction (SIGUSR1, &act, NULL);
		ppid = getppid();
		
		while(1)
		{
			sleep(1);
			kill(ppid, SIGUSR1);
			pause();
		}
		
	}
	
	
	else if(pid > 0)
	{
		act.sa_handler = p_handler;
		sigaction (SIGUSR1, &act, NULL);
		
		while(1)
		{
			pause();
			sleep(1);
			kill(ppid, SIGUSR1);
		}
	}
	
	else
	{
		perror("Error");
	}

	return 0;

}


void p_handler(int signo)
{
	printf("\nParent handler : call %d times.\n", ++i);
}


void c_handler(int signo)
{
	printf("\nChild handler : call %d times.\n", ++i);
}

