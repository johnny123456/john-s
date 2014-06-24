#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<string.h>
#define MAXLINE 100

int main(void)
{
	
	struct sockaddr_in servaddr;
	int n,i;
	char buf[MAXLINE];
	int clifd;
	
	clifd=socket(AF_INET,SOCK_STREAM,0);
	
	bzero(&servaddr,sizeof(servaddr));
	servaddr.sin_family=AF_INET;
	inet_pton(AF_INET,"127.0.0.1",&servaddr.sin_addr);
	servaddr.sin_port=htonl(8001);
	
	/*i=connect(clifd,(struct sockaddr_in *)&servaddr,
sizeof(servaddr));*/

	i=connect(clifd,(struct sockaddr_in *)&servaddr,sizeof(servaddr));
	printf("i=%d",i);

	while((fgets(buf,MAXLINE,stdin)) != NULL)
	{
		write(clifd,buf,strlen(buf));
		n=read(clifd,buf,MAXLINE);
		if(n == 0)
		{
			fprintf(stdout,"connection is close!\n");
			break;
		}
		printf("response from server:\n");
		write(STDOUT_FILENO,buf,n);
		printf("\n");
	}

	close(clifd);
	return 0;
}

