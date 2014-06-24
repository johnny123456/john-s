#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<signal.h>
#define MAXLINE 100

int main(void)
{
	
	struct sockaddr_in servaddr;
	char buf[MAXLINE];
	int n,i,k=0;
	socklen_t addrlen;
	int serfd,connfd;

	serfd=socket(AF_INET,SOCK_STREAM,0);

	bzero(&servaddr,sizeof(servaddr));
	servaddr.sin_family=AF_INET;
	servaddr.sin_addr.s_addr=htonl(INADDR_ANY);
	servaddr.sin_port=htons(8002);

	bind(serfd,(struct sockaddr_in *)&servaddr,sizeof(servaddr));
	listen(serfd,20);
	addrlen=sizeof(servaddr);

	while(1)
	{
		connfd=accept(serfd,NULL,&addrlen);
		n=(int)fork();
		if(n == 0)
		{
			close(serfd);
			while(1)
			{
				k++;
				n=read(connfd,buf,MAXLINE);
				for(i=0;i<n;i++)
				{
					buf[i]=toupper(buf[i]);
				}
				write(connfd,buf,strlen(buf));
				if(k == 10)
				{
					close(connfd);
					exit(0);
				}	
			}
		}
		else{
			close(connfd);
			signal(SIGCHLD, SIG_IGN);/*to solute child become a zombie process!*/
		}	
	}
				
	return 0;
}
