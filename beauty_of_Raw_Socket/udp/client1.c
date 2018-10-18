#include <stdio.h>
#include <sys/socket.h>
#include <unistd.h>
#include <sys/un.h>
#include <stdlib.h>
#include "ipc.h"

int main() {
	int sock_fd;
	int ret;
	int len;
	char buff[8192];
	struct sockaddr_un addr;
	struct sockaddr_un from;

	if ((sock_fd = socket(AF_UNIX, SOCK_DGRAM, 0)) < 0) {
		perror("socket");
		exit(0);
	}


	memset(&addr, 0, sizeof(addr));
	addr.sun_family = AF_UNIX;
	strcpy(addr.sun_path, CLIENT_SOCK_FILE);
	unlink(CLIENT_SOCK_FILE);

	if (bind(sock_fd, (struct sockaddr *)&addr, sizeof(addr)) < 0) {
		perror("bind");
		exit(0);
	}

	memset(&addr, 0, sizeof(addr));
	addr.sun_family = AF_UNIX;
	strcpy(addr.sun_path, SERVER_SOCK_FILE);
	if (connect(sock_fd, (struct sockaddr *)&addr, sizeof(addr)) == -1) {
		perror("connect");
		exit(0);

	}


	strcpy (buff, "Hii server");
	if (send(sock_fd, buff, strlen(buff)+1, 0) == -1) {
		perror("send");
		exit(0);
	}

	printf ("sending finished\n");


	if ((len = recv(sock_fd, buff, 8192, 0)) < 0) {
		perror("recv");
		exit(0);
	}
	printf ("received %d %s\n", len, buff);


	if (sock_fd >= 0) {
		close(sock_fd);
	}

	unlink (CLIENT_SOCK_FILE);
	return 0;
}

