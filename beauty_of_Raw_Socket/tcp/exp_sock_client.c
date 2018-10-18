#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#define PORT 7000
  
int main(int argc, char *argv[])
{
    int index = 0;
    struct sockaddr_in address;
    int sock_fd; 
    int val;
    struct sockaddr_in serv_addr;
    char buffer[1024];
    if ((sock_fd = socket(AF_UNIX, SOCK_STREAM, IPPROTO_TCP)) == -1`)
    {
        printf(" Socket creation failed\n");
        return -1;
    }
  
    memset(&serv_addr, '0', sizeof(serv_addr));
  
    serv_addr.sin_family = AF_UNIX;
    serv_addr.sin_port = htons(PORT);
      
/*    if(inet_pton(AF_UNIX, "172.16.5.179", &serv_addr.sin_addr)<=0) 
    {
        printf("Invalid IP \n");
        return -1;
    }*/
  
    if (connect(sock_fd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
    {
        printf("Connection Failed \n");
        return -1;
    }
    while(index < 8)
    {
        fgets(buffer, 100, stdin); 
        send(sock_fd , buffer , strlen(buffer) , 0 );
        printf("client sent : %s\n",buffer);
        val = read(sock_fd , buffer, 1024);
        printf("server sent : %s\n",buffer );
        index++;
    }
    return 0;
}
