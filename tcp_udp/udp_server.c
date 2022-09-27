#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<sys/types.h>

int main(int argc,char *argv[])
{
    if(argc!=3)
    {
        perror("argc\n");
        return 1;
    }
    int sockfd=socket(AF_INET,SOCK_DGRAM,0);
    if(sockfd<0)
    {
        perror("socket\n");
        return 2;
    }

    char buf[128];
    struct sockaddr_in local;
    local.sin_family=AF_INET;
    local.sin_port=htons(atoi(argv[2]));
    local.sin_addr.s_addr=inet_addr(argv[1]);

    if(bind(sockfd,(struct sockaddr*)&local,sizeof(local))<0)
    {
        perror("bind");
        return 2;
    }

    struct sockaddr_in client;

    while(1)
    {
        socklen_t len=sizeof(client);
        size_t recv=recvfrom(sockfd,buf,sizeof(buf),0,(struct sockaddr*)&client,&len);
        if(recv<0)
        {
            printf("recv error\n");
            return 4;
        }
        buf[recv]='\0';

        printf("[%s,%d] > %s\n",inet_ntoa(client.sin_addr),ntohs(client.sin_port),buf);
        sendto(sockfd,buf,strlen(buf),0,(struct sockaddr*)&client,sizeof(client));
    }
    close(sockfd);//use signal to delet
    return 0;
}      

