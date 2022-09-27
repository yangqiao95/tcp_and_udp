#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>

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
    struct sockaddr_in server;
    server.sin_family=AF_INET;
    server.sin_port=htons(atoi(argv[2]));
    server.sin_addr.s_addr=inet_addr(argv[1]);
    while(1)
    {
        ssize_t r=read(0,buf,sizeof(buf));  
        if(r<0)
        {
            printf("read error\n");
            continue;
        }
        buf[r-1]='\0';

        sendto(sockfd,buf,strlen(buf),0,(struct sockaddr*)&server,sizeof(server));
        ssize_t recv=recvfrom(sockfd,buf,sizeof(buf),0,NULL,NULL);
        buf[recv]=0;
        printf("server > %s\n",buf);
    }
    close(sockfd);//use signal to delet
    return 0;
}      

