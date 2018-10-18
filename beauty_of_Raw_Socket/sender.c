#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <sys/ioctl.h>
#include <net/if.h>
#include <sys/types.h>
#include<sys/socket.h>
#include<netinet/ip.h>
#include<linux/udp.h>
#include<linux/if_ether.h>
#include<arpa/inet.h> 
#include<linux/if_packet.h> 
#include<errno.h> 
#define BUFF_SIZE 1500
#define DESTMAC0  0xdc
#define DESTMAC1  0xfe
#define DESTMAC2  0x07
#define DESTMAC3  0x2e
#define DESTMAC4  0xf7
#define DESTMAC5  0xe5


int main(){
int total_len =0 ;

int sock_raw=socket(AF_PACKET,SOCK_RAW,IPPROTO_RAW);
if(sock_raw == -1){
          perror("socket");
          printf("error in socket \n");
          exit(1);
}



struct ifreq ifreq_i;
memset(&ifreq_i,0,sizeof(ifreq_i));
strncpy(ifreq_i.ifr_name,"eth0",IFNAMSIZ-1); //giving name of Interface
 
if((ioctl(sock_raw,SIOCGIFINDEX,&ifreq_i))<0){
          perror("socket");
    printf("error in index ioctl reading");//getting Index Name
}
    printf("index=%d\n",ifreq_i.ifr_ifindex);



    struct ifreq ifreq_c;
    memset(&ifreq_c,0,sizeof(ifreq_c));
    strncpy(ifreq_c.ifr_name,"eth0",IFNAMSIZ-1);//giving name of Interface
     
    if((ioctl(sock_raw,SIOCGIFHWADDR,&ifreq_c))<0){
                                                      //getting MAC Address
          perror("socket");
    printf("error in SIOCGIFHWADDR ioctl reading");
    }












    struct ifreq ifreq_ip;
    memset(&ifreq_ip,0,sizeof(ifreq_ip));
    strncpy(ifreq_ip.ifr_name,"eth0",IFNAMSIZ-1);//giving name of Interface
    if(ioctl(sock_raw,SIOCGIFADDR,&ifreq_ip)<0) //getting IP Address
{
          perror("socket");
printf("error in SIOCGIFADDR \n");
}


char *sendbuff=(unsigned char*)malloc(BUFF_SIZE); // increase in case of more data
memset(sendbuff,0,BUFF_SIZE);


// create ethernet header 

struct ethhdr *eth = (struct ethhdr *)(sendbuff);
#if 1  
eth->h_source[0] = (unsigned char)(ifreq_c.ifr_hwaddr.sa_data[0]);
eth->h_source[1] = (unsigned char)(ifreq_c.ifr_hwaddr.sa_data[1]);
eth->h_source[2] = (unsigned char)(ifreq_c.ifr_hwaddr.sa_data[2]);
eth->h_source[3] = (unsigned char)(ifreq_c.ifr_hwaddr.sa_data[3]);
eth->h_source[4] = (unsigned char)(ifreq_c.ifr_hwaddr.sa_data[4]);
eth->h_source[5] = (unsigned char)(ifreq_c.ifr_hwaddr.sa_data[5]);
 

eth->h_dest[0] = DESTMAC0;
eth->h_dest[1] = DESTMAC1;
eth->h_dest[2] = DESTMAC2;
eth->h_dest[3] = DESTMAC3;
eth->h_dest[4] = DESTMAC4;
eth->h_dest[5] = DESTMAC5;


#endif

eth->h_proto = htons(ETH_P_IP); //means next header will be IP header
 
/* end of ethernet header */
 total_len+=sizeof(struct ethhdr);



struct iphdr *iph = (struct iphdr*)(sendbuff + sizeof(struct ethhdr));
iph->ihl = 5;
iph->version = 4;
iph->tos = 16;
iph->id = htons(10201);
iph->ttl = 64;
iph->protocol = 17;
iph->saddr = inet_addr(inet_ntoa((((struct sockaddr_in *)&(ifreq_ip.ifr_addr))->sin_addr)));
iph->daddr = inet_addr("172.16.5.64"); // put destination IP address
 
total_len += sizeof(struct iphdr);


struct udphdr *uh = (struct udphdr *)(sendbuff + sizeof(struct iphdr) + sizeof(struct ethhdr));
 
uh->source = htons(23451);
uh->dest = htons(23452);
uh->check = 0;
 
total_len+= sizeof(struct udphdr);



      int a,b,c;
       for (b=c=10;a="Let's show the creativity!!!!!!!"
                       ",R.SAy.TCy.RFu SIo TNn(ROo)SLq"
                       " SQq NLo VKs RLq TQn*RPn/TMy.LHy.z.p"[b+++21]; )
               for(; a-- > 64 ; )
                       sendbuff[total_len++]= ( ++c=='Z' ? c = c/ 9:33^b&1);
#if 0
sendbuff[total_len++] = 'f';
sendbuff[total_len++] = 'u';
sendbuff[total_len++] = 'c';
sendbuff[total_len++] = 'k';
sendbuff[total_len++] = '\n';
sendbuff[total_len++] = 'o';
sendbuff[total_len++] = 'f';
sendbuff[total_len++] = 'f';
sendbuff[total_len++] = ' ';
sendbuff[total_len++] = 'v';
sendbuff[total_len++] = 'i';
sendbuff[total_len++] = 'n';
sendbuff[total_len++] = 'a';
sendbuff[total_len++] = 'y';


#endif

uh->len = htons((total_len - sizeof(struct iphdr) - sizeof(struct ethhdr)));
//UDP length field
iph->tot_len = htons(total_len - sizeof(struct ethhdr));
//IP length field



unsigned short checksum(unsigned short* buff, int _16bitword)
{
unsigned long sum;
for(sum=0;_16bitword>0;_16bitword--)
sum+=htons(*(buff)++);
sum = ((sum >> 16) + (sum & 0xFFFF));
sum += (sum>>16);
return (unsigned short)(~sum);
}


struct sockaddr_ll sadr_ll;
sadr_ll.sll_ifindex = ifreq_i.ifr_ifindex; // index of interface
sadr_ll.sll_halen = ETH_ALEN; // length of destination mac address
sadr_ll.sll_addr[0] = DESTMAC0;
sadr_ll.sll_addr[1] = DESTMAC1;
sadr_ll.sll_addr[2] = DESTMAC2;
sadr_ll.sll_addr[3] = DESTMAC3;
sadr_ll.sll_addr[4] = DESTMAC4;
sadr_ll.sll_addr[5] = DESTMAC5;


ssize_t send_len = sendto(sock_raw,sendbuff,total_len,0,(const struct sockaddr*)&sadr_ll,sizeof(struct sockaddr_ll));
if(send_len<0)
{
printf("error in sending....sendlen=%d....errno=%d\n",send_len,errno);
return -1;
 
}







}


