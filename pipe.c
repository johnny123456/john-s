#include<stdlib.h>
#include<unistd.h>
#include<stdio.h>
#define MAXLINE 100

int main(int argc, char * argv[])
{

	size_t n;
	int  fd[2];
	pid_t pid;
	char line[MAXLINE];

	memset(line,0x00,sizeof(line));
	
	if(pipe(fd) < 0)
	{	
		fprintf(stderr,"pipe error!\n");
		exit(1);
	}
	if((pid=fork()) <  0)
	{
		fprintf(stderr,"fork error!\n");
		exit(1);
	}
	if(pid == 0)
	{
		/*this is a child pro!*/
		/*close(fd[1]);*/
		n=read(fd[0],line,MAXLINE);
		if(n < 0)
		{
			fprintf(stderr,"read error!\n");
			exit(1);
		}
		printf("father say: %s\n",line);
		write(fd[1],"child\n",10);
	}
	else
	{
		/*this is a father pro!*/
		/*close(fd[0]);*/
		n=write(fd[1],argv[1],strlen(argv[1]));
		if(n < 0)
		{
			fprintf(stderr,"write error!\n");
			exit(1);
		}
		wait(NULL);
		read(fd[0],line,MAXLINE);
		printf("child say:%s\n",line);
	}
	return 0;
}
