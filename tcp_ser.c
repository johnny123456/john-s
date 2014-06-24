#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<sys/socket.h>
#include<netinet/in.h>
#define MAXLINE 100
#define SERV_PORT 8001

int main(void)
{
	
	struct sockaddr_in servaddr;
	char buf[MAXLINE];
	int n,i,k=0;
	int servfd,connfd;
	socklen_t addrlen;

	servfd=socket(AF_INET,SOCK_STREAM,0);

	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servaddr.sin_port = htons(SERV_PORT);

	bind(servfd,(struct sockaddr_in *)&servaddr,
sizeof(servaddr));
	listen(servfd,20);

	printf("Accepting connections...\n");

	addrlen=sizeof(servaddr);
	connfd=accept(servfd,NULL,(socklen_t *)&addrlen);
	while(1)
	{
		k++;
		n=read(connfd,buf,MAXLINE);
		printf("received from client!\n");
		for(i=0;i<n;i++)
		{
			buf[i]=toupper(buf[i]);
		}
		sleep(2);
		write(connfd,buf,n);

		if(k == 10)
			break;
	}

	close(connfd);
	return 0;
}
