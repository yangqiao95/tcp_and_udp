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
        int sockfd=socket(AF_INET,SOCK_STREAM,0);
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
        if(connect(sockfd,(struct sockaddr*)&server,sizeof(server))<0)
        {
                perror("connect\n");
                return 3;
        }

        printf("connetc success\n");

        while(1)
        {
                memset(buf,0,sizeof(buf));
                ssize_t r=read(0,buf,sizeof(buf));  
                if(r<0)
                {
                        printf("read error\n");
                        continue;
                }
                buf[r-1]=0;
                if(send(sockfd,buf,strlen(buf),0)==0)
                        continue;
                memset(buf,0,sizeof(buf));
                ssize_t rec=recv(sockfd,buf,sizeof(buf),0);
                printf("server > %s\n",buf);
        }
        close(sockfd);//use signal to delet
        return 0;
}      


