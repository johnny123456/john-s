#include<sys/types.h>
#include<stdio.h>
#include<sys/stat.h>
#include<fcntl.h>

int main()
{
	int i;
	struct stat buff;
	
	/*if(stat(&buf,&buff)<0)*/
	
	if((i=open("/lx/passwd",O_RDWR))<0)
	printf("open error!\n"); 
	printf("%d\n",i);

/*	if(fstat(i,&buff)<0)
	printf("stat error!\n");
*/
	/*printf("%s",buff.st_uid);*/
	return 0;
}

