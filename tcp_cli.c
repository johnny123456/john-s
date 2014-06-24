#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<unistd.h>
#define MAXLINE 100

int main()
{

	struct sockaddr_in servaddr;
	int n,k=0;
	char buf[MAXLINE];
	int sockfd;
	
	sockfd=socket(AF_INET,SOCK_STREAM,0);
	if(sockfd == -1)
	{
		fprintf(stderr,"socket error!\n");
		exit(1);
	}
	
	bzero(&servaddr, sizeof(servaddr));
        servaddr.sin_family = AF_INET;
        inet_pton(AF_INET, "127.0.0.1", &servaddr.sin_addr);
        servaddr.sin_port = htons(8001);

	k=connect(sockfd,(struct sockaddr_in *)&servaddr,sizeof(servaddr));
	printf("k=%d\n",k);

	while(1)
	{

		fgets(buf,MAXLINE,stdin);
		write(sockfd,buf,strlen(buf));
		n=read(sockfd,buf,MAXLINE);
		if(n == 0)
		{
			fprintf(stdout,"conn is close!\n");
			break;
		}
		printf("this is server's response:\n");
		fprintf(stdout,"%s\n",buf);
	}
	close(sockfd);
	return 0;
}
