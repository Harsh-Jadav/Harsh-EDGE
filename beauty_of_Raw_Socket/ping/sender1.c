 #include<stdio.h>
  2 #include<linux/in.h>
    3 #include<netdb.h>
      4 #include<sys/socket.h>
        5 #include<netinet/in.h>
          6 #include<arpa/inet.h>
            7 
              8 struct sockaddr_in dest_addr;
                9 struct hostent *host ;
                 10 int sockfd ;
                  11 
                   12 int main(int argc, char*argv)
     13 {
      14 
      15 
      16     if(argc > 2 ){
       17         printf("Give hostname or ipaddress \n ");
       18         exit(1);
       19 
       20     }
      21 
      22 // opening raw socket 
      23 
      24     if((sockfd = socket(AF_INET, SOCK_RAW, protocol->p_proto)) < 0){
       25              perror("socket error");
       26              exit(1);
       27 
       28    }
      29 
      30 
      31                                                    
      32    memset(&dest_addr, 0, sizeof(dest_addr));                                 
      33                                                                     
      34     dest_addr.sin_family = AF_INET;                                       
      35                                                                           
      36     if(inaddr = inet_addr(argv[1]) == INADDR_NONE){                          
       37                                                                          
       38           if((host = gethostbyname(argv[1])) == NULL){                   
        39                  perror("gethostbyname error");                          
        40                  exit(1);                                                
        41            }            

        memcpy((char*) &dest_addr.sin_addr, host->h_addr, host->h_length);
         43     }
       44 
            45     else{
             46          dest_addr.sin_addr.s_addr = inet_addr(argv[1]);
              47 
                   48     }
        49 
             50    printf("PING %s(%s): %d bytes data in ICMP packets.\n", argv[1], inet_ntoa
                      51 
                       52                     (dest_addr.sin_addr), datalen);
         53 
              54    send_packet();
          55    recv_packet();
           56 
                57 
                 58 }
                 
