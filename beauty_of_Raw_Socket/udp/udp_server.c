#include<stdio.h>
#include<unistd.h>
#include<sys/socket.h>
#include<stdlib.h>
#include<netinet/in.h>
#include<string.h>

#define MAXBUF 256
#define PORT 8000

int main(void)
{
	int sock_fd;
	int new_fd;
	int ret;
	int var;
	char buf[MAXBUF];
	struct sockaddr_in remoteAddr;
    struct sockaddr_in localAddr;
    socklen_t localAddrLen;


	sock_fd = socket(AF_INET, SOCK_DGRAM, 0);
	if(sock_fd == -1)
	{
		printf("socket failed\n");
		exit(0);
	}
    memset(&localAddr, 0, sizeof(localAddr));
    
    localAddr.sin_family = AF_INET;
	localAddr.sin_port = htons(PORT);
	localAddr.sin_addr.s_addr = INADDR_ANY;

    localAddrLen = sizeof(localAddr);

	ret = bind(sock_fd, (struct sockaddr*)&localAddr, sizeof(localAddr));
	if(ret == -1)
	{
		printf("bind failed\n");
		exit(0);
	}

    int index = 0;
    while(index < 8)
    {
        recvfrom(sock_fd, buf, MAXBUF, 0, (struct sockaddr*)&localAddr, &localAddrLen);
        printf("%s\n",buf);
        fgets(buf, MAXBUF, stdin);
        sendto(sock_fd, buf, MAXBUF, 0, (struct sockaddr*)&localAddr, localAddrLen);
        memset(buf, 0, sizeof(buf));
    }

	return 0;
}
