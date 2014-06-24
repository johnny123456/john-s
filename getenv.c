#include<stdio.h>
#include<stdlib.h>

int main(int argc,char * argv[])
{
	if(argc != 2)
		exit(1);

	char * psr;
	if((psr=(char *)getenv(argv[1])) == NULL)
	{
		fprintf(stderr ,"getenv faild!\n");
		exit(1);
	}
	printf("%s=%s\n",argv[1],psr);
	return 0;
}
