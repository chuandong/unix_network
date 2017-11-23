#include	"unp.h"
#include	<time.h>

int
main(int argc, char **argv)
{
	int					listenfd, connfd;
	struct sockaddr_in	servaddr;
	char				buff[MAXLINE]={0};
	char                writebuf[MAXLINE]={0};
	time_t				ticks;
	socklen_t              len;

	listenfd = Socket(AF_INET, SOCK_STREAM, 0);

	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family      = AF_INET;
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servaddr.sin_port        = htons(PORT);	/* daytime server */

	Bind(listenfd, (SA *) &servaddr, sizeof(servaddr));

	Listen(listenfd, LISTENQ);

	for ( ; ; ) {
	    len = sizeof(servaddr);
		connfd = Accept(listenfd, (SA *)&servaddr, &len);

        ticks = time(NULL);
        puts("input you want >:");
        fgets(writebuf, MAXLINE, stdin);
        snprintf(buff, sizeof(buff), "%.24s%s\r", ctime(&ticks), writebuf);
        write(connfd, buff, strlen(buff));

		
	}
	
	return 0;
}
