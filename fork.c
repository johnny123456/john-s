#include<sys/types.h>
#include<unistd.h>
#include<stdio.h>

int main()
{
	pid_t pid;
	int n;
	char * mesg;

	pid=fork();
	if(pid ==0)
	{
		mesg="this is a child process!\n";
		n=6;
	}
	else
	{
		mesg="this is a parent process!\n";
		n=3;
		sleep(120);
	}

	for(;n>0;n--)
	{
		fprintf(stdout, mesg);
		sleep(1);
	}
	
	return 0;
}
		
