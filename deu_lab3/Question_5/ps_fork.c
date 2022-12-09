#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>



int main(int argc, char* argv[])
{

	int i;
	int num;

	 if(argc < 1)
	 {
	 	printf("HI! I'm ~~~~ .\n");
	 }
	else
	{
		num = atoi(argv[1]);
		printf("Hello");
		
		for(i=0; i<num; i++)
			fork();
			
		printf("\n");
	}

	return 0;
}
