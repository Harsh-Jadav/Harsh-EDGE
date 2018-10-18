#include <unistd.h>
#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#define PORT 7000
int main(int argc, char *argv[])
{
    int sock_fd;
    int new_sockfd;
    int val;
    struct sockaddr_in address;
    
    int addrlen = sizeof(address);
    char buffer[1024];
      
    if ((sock_fd = socket(AF_UNIX, SOCK_STREAM, IPPROTO_TCP)) == -1)
    {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }
      
    address.sin_family = AF_UNIX;
    address.sin_addr.s_addr = htons("172.16.5.179");
    address.sin_port = htons( PORT );
      
    if (bind(sock_fd, (struct sockaddr *)&address, 
                                 sizeof(address))<0)
    {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }
    if (listen(sock_fd, 0) < -1)
    {
        perror("listen failed\n");
        exit(EXIT_FAILURE);
    }
    if ((new_sockfd = accept(sock_fd, (struct sockaddr *)&address, 
                       (socklen_t*)&addrlen)) == -1)
    {
        perror("accept");
        exit(EXIT_FAILURE);
    }
    int index = 0;

    while(index < 8)
    {
    val = read( new_sockfd , buffer, 1024);
    printf("%s\n",buffer );
    fgets(buffer, 100, stdin);
    send(new_sockfd , buffer , strlen(buffer) , 0 );
    printf("message sent from server\n");
    index++;
    }
    return 0;
}
