#include<stdio.h>
#include<stdlib.h>
#include<string.h> 
#include <sys/types.h>
#include<arpa/inet.h>
#include<sys/socket.h>
#include<netinet/ip.h>
#include<linux/udp.h>
#include<linux/tcp.h> 
#include<linux/if_ether.h>
#include<linux/icmp.h>
#define MAX 65536

int main(){

    int sockfd;

    // opening a raw socket 

    sockfd=socket(AF_PACKET,SOCK_RAW,htons(ETH_P_ALL));
    if(sockfd<0)
    {
    perror("sock");
    printf("error in socket\n");
    exit(1);
    }



    // reception of the network 

    unsigned char *buffer = (unsigned char *) malloc(MAX); //to receive data
    memset(buffer,0,MAX);
    struct sockaddr saddr;
    int saddr_len = sizeof (saddr);





    //Receive a network packet and copy in to buffer

    while(1){
    int buflen=recvfrom(sockfd,buffer,MAX,0,&saddr,(socklen_t *)&saddr_len);
    if(buflen<0)
    {
    perror("recvfrom");
    printf("error in reading recvfrom function\n");
    exit(1);
    }


    // Extracting the ethernet header 

    struct ethhdr *eth = (struct ethhdr *)(buffer);
    printf("\nEthernet Header\n");
    printf("\t|-Source Address : %.2X-%.2X-%.2X-%.2X-%.2X-%.2X\n",eth->h_source[0],eth->h_source[1],eth->h_source[2],eth->h_source[3],eth->h_source[4],eth->h_source[5]);
    printf("\t|-Destination Address : %.2X-%.2X-%.2X-%.2X-%.2X-%.2X\n",eth->h_dest[0],eth->h_dest[1],eth->h_dest[2],eth->h_dest[3],eth->h_dest[4],eth->h_dest[5]);
    printf("\t|-Protocol : %d\n",eth->h_proto);

    // Extracting ip header 

    struct sockaddr_in source ;
    struct sockaddr_in dest ;
    unsigned short iphdrlen;
    struct iphdr *ip = (struct iphdr*)(buffer + sizeof(struct ethhdr));
    memset(&source, 0, sizeof(source));
    source.sin_addr.s_addr = ip->saddr;
    memset(&dest, 0, sizeof(dest));
    dest.sin_addr.s_addr = ip->daddr;


    printf("\n  Ip Header\n");
    printf("\t|-Version : %d\n",(unsigned int)ip->version);

    printf("\t|-Internet Header Length : %d DWORDS or %d Bytes\n",(unsigned int)ip->ihl,((unsigned int)(ip->ihl))*4);

    printf("\t|-Type Of Service : %d\n",(unsigned int)ip->tos);

    printf("\t|-Total Length : %d Bytes\n",ntohs(ip->tot_len));

    printf("\t|-Identification : %d\n",ntohs(ip->id));

    printf("\t|-Time To Live : %d\n",(unsigned int)ip->ttl);

    printf("\t|-Protocol : %d\n",(unsigned int)ip->protocol);

    printf("\t|-Header Checksum : %d\n",ntohs(ip->check));

    printf("\t|-Source IP : %s\n", (char*)inet_ntoa(source.sin_addr));

    printf("\t|-Destination IP : %s\n",(char *)inet_ntoa(dest.sin_addr));




    iphdrlen = ip->ihl*4;

    /* getting pointer to udp header*/
    if(ip->protocol == 1){
    
    struct icmphdr *icmp=(struct icmphdr*)(buffer + iphdrlen + sizeof(struct ethhdr));
     
    
    printf("\n ICMP Header\n");
    
    printf("\t| -Type:%d\n ", (icmp->type));
    printf("\t| -code:%d\n ", ntohs(icmp->code));
    printf("\t| -checksum:%d\n ", ntohs(icmp->checksum));

    }
    else if(ip->protocol == 6){

    struct tcphdr *tcp=(struct tcphdr*)(buffer + iphdrlen + sizeof(struct ethhdr));
    printf("\n TCP Header\n");
    printf("\t| -source :%d\n ", ntohs(tcp->source));
    printf("\t| -destination :%d\n ", ntohs(tcp->dest));
    printf("\t| -sequence :%d\n ", ntohs(tcp->seq));
    printf("\t| -ack :%d\n ", ntohs(tcp->ack_seq));

    }
    else{
    struct udphdr *udp=(struct udphdr*)(buffer + iphdrlen + sizeof(struct ethhdr));

    printf("\n  UDP Header\n");
    printf("\t|-Source Port : %d\n" , ntohs(udp->source));
    printf("\t|-Destination Port : %d\n" , ntohs(udp->dest));
    printf("\t|-UDP Length : %d\n" , ntohs(udp->len));
    printf("\t|-UDP Checksum : %d\n" , ntohs(udp->check));

    }


    // Extracting data 

    int i ;
    unsigned char * data = (buffer + iphdrlen + sizeof(struct ethhdr) + sizeof(struct udphdr));


    int remaining_data = buflen - (iphdrlen + sizeof(struct ethhdr) + sizeof(struct udphdr));

    
    

    for(i=0;i<remaining_data;i++)
    {
     printf("%c", data[i]);
    }
}

} 
