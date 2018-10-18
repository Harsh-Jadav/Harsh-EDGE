#include <arpa/inet.h>
#include <netdb.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <string.h>
#include <stdio.h>

#define MAXBUF 256
#define PORT 8000

void main ( void )
{
	char buf[MAXBUF];
	int sock_fd;
	
	socklen_t remoteAddrLen;
	
	struct sockaddr_in remoteAddr;
	struct sockaddr_in localAddr;

	/* session is created for a new socket */
	sock_fd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	memset(&remoteAddr, 0, sizeof(remoteAddr));

	remoteAddr.sin_family = AF_INET;
	remoteAddr.sin_port = htons(PORT);
	remoteAddr.sin_addr.s_addr = inet_addr("172.16.5.179");

	remoteAddrLen = sizeof(remoteAddr);

	while(fgets(buf, MAXBUF, stdin)) {
		sendto(sock_fd, buf, MAXBUF, 0, (struct sockaddr*)&remoteAddr, remoteAddrLen);
		memset(buf, 0, sizeof(buf));
		recvfrom(sock_fd, buf, MAXBUF, 0, (struct sockaddr*)&remoteAddr, &remoteAddrLen);
		printf("%s\n", buf);
	}
	close(sock_fd);
}
