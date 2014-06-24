#include<stdio.h>
#include<unistd.h>

int main(int argc, char * argv[])
{
	extern char ** environ;
	int i;

	for(i=0; environ[i]!=NULL; i++)
		printf("%s\n",environ[i]);

	return 0;
}
