#include	"unp.h"

int
main(int argc, char **argv)
{
	int					sockfd, n;
	char				recvline[MAXLINE + 1];
	struct sockaddr_in	servaddr;

	if ( (sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
		err_sys("socket error");

	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_port   = htons(PORT);	/* daytime server */
	if (inet_pton(AF_INET, ADDR_IP, &servaddr.sin_addr) <= 0)
		err_quit("inet_pton error for %s", ADDR_IP);

    
	if (connect(sockfd, (SA *) &servaddr, sizeof(servaddr)) < 0)
	    err_sys("connect error");
	
	while (1)
	{
	    n = read(sockfd, recvline, sizeof(recvline));
	    if (n > 0)
	    {
	        fputs(recvline, stdout);
	    }
	    else if (n ==0)
	    {
	        continue;
	    }else
	    {
	        fprintf(stderr, "read fail.");
	        return -1;
	    }
	}

	/*while ( (n = read(sockfd, recvline, MAXLINE)) > 0) {
		recvline[n] = 0;	
		if (fputs(recvline, stdout) == EOF)
			err_sys("fputs error");
	}
	if (n < 0)
		err_sys("read error");*/
		
		

	exit(0);
}
