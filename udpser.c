#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/socket.h>
#include<netinet/in.h>
#define MAXLINE 80
#define SER_PORT 8003

int main(void)
{

	struct sockaddr_in servaddr,cliaddr;
	int serfd;
	char buf[MAXLINE];
	int n,i=0;
	socklen_t serlen,clilen;

	serfd=socket(AF_INET,SOCK_DGRAM,0);
	
	bzero(&servaddr,sizeof(servaddr));
	servaddr.sin_addr.s_addr=htonl(INADDR_ANY);
	servaddr.sin_port=htons(SER_PORT);

	bind(serfd,(struct sockaddr_in *)&servaddr,sizeof(servaddr));

	fprintf(stdout,"Recvfrom Client....\n");

	clilen=sizeof(cliaddr);
	while(1)
	{
		n=recvfrom(serfd,buf,MAXLINE,0,(struct sockaddr_in *)&cliaddr,&clilen);
		if(n == -1)
		{
			fprintf(stderr,"recvfrom faild!\n");
			exit(1);
		}
		for(i=0;i<strlen(buf);i++)
		{
			buf[i]=toupper(buf[i]);
		}
		n=sendto(serfd,buf,strlen(buf),0,(struct sockaddr_in *)&cliaddr,clilen);
		if(n == -1)
		{
			fprintf(stderr,"sendto faild!\n");
			exit(1);
		}
	}
	
	close(serfd);
	return 0;
}
