#include<stdio.h> 
#include<netdb.h> 
#include<sys/socket.h>
#include<sys/types.h>
#include<unistd.h>
#include<netinet/in.h>
#include<netinet/ip.h>
#include<arpa/inet.h> 
#include<errno.h>
#include<stdlib.h> 
#include<string.h> 

#define PACKET_SIZE 4096

struct sockaddr_in dest_addr;
struct hostent *host ;
int sockfd ;
int datalen = 56 ;
int nsend = 0;
int recv

char sendpacket[PACKET_SIZE];
char recvpacket[PACKET_SIZE];

int main(int argc, char**argv)
{

     unsigned long inaddr = 01;
     struct protoent *protocol;

    if(argc > 2 ){
        printf("Give hostname or ipaddress \n ");
        exit(1); 
    
    }

// opening raw socket 

    if((sockfd = socket(AF_INET, SOCK_RAW, protocol->p_proto)) < 0){
             perror("socket error");
             exit(1);
            
   }



   memset(&dest_addr, 0, sizeof(dest_addr));

    dest_addr.sin_family = AF_INET;

    if(inaddr = inet_addr(argv[1]) == INADDR_NONE){
            
          if((host = gethostbyname(argv[1])) == NULL){
                 perror("gethostbyname error");
                 exit(1);
           }
       memcpy((char*) &dest_addr.sin_addr, host->h_addr, host->h_length);
    }
   
    else{
         dest_addr.sin_addr.s_addr = inet_addr(argv[1]);
      
    }

    printf("PING %s(%s): %d bytes data in ICMP packets.\n", argv[1], inet_ntoa (dest_addr.sin_addr), datalen);
        
//   send_packet(); 
//   recv_packet(); 


}













