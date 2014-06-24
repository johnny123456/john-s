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

	struct sockaddr_in servaddr;
	int clifd;
	int n;
	socklen_t serlen;
	char buf[MAXLINE];

	clifd=socket(AF_INET,SOCK_DGRAM,0);

	bzero(&servaddr,sizeof(servaddr));
	servaddr.sin_family=AF_INET;
	inet_pton(AF_INET,"127.0.0.1",&servaddr.sin_addr);
	servaddr.sin_port=htons(SER_PORT);

	serlen=sizeof(servaddr);
	while(1)
	{
		fgets(buf,MAXLINE,stdin);
		n=sendto(clifd,buf,strlen(buf),0,(struct sockaddr_in *)&servaddr,serlen);
		if(n == -1)
		{
			fprintf(stderr,"sendto faild\n");
			exit(1);
		}

		n=recvfrom(clifd,buf,MAXLINE,0,(struct sockaddr *)&servaddr,&serlen);

		if(n == -1)
		{
			fprintf(stderr,"recvfrom faild\n");
			exit(1);
		}
	
		printf("recvive from server\n");
		write(STDOUT_FILENO,buf,n);
		printf("\n");
	}

	close(clifd);
	return 0;
}

