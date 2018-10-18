#include <stdio.h>
#include <sys/socket.h>
#include <sys/un.h>
#include<stdlib.h>
#include "ipc.h"

int main() {
	int sock_fd;
	int ret;
	int len;
	char buff[8192];
	struct sockaddr_un addr;
	struct sockaddr_un from;
	socklen_t fromlen = sizeof(from);

	if ((sock_fd = socket(AF_UNIX, SOCK_DGRAM, 0)) < 0) {
		perror("socket");
		exit(0);
	}


	memset(&addr, 0, sizeof(addr));
	addr.sun_family = AF_UNIX;
	strcpy(addr.sun_path, SERVER_SOCK_FILE);
	unlink(SERVER_SOCK_FILE);
	
	if (bind(sock_fd, (struct sockaddr *)&addr, sizeof(addr)) < 0) {
		perror("bind");
		exit(0);
	}


	while ((len = recvfrom(sock_fd, buff, 8192, 0, (struct sockaddr *)&from, &fromlen)) > 0) {
		printf ("recvfrom: %s\n", buff);
		strcpy (buff, "transmit good!");
		ret = sendto(sock_fd, buff, strlen(buff)+1, 0, (struct sockaddr *)&from, fromlen);
		if (ret < 0) {
			perror("sendto");
			break;
		}
	}


	if (sock_fd >= 0) {
		close(sock_fd);
	}

	return 0;
}

