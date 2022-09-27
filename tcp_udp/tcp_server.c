#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<sys/types.h>
#include<sys/wait.h>

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
        struct sockaddr_in local;
        local.sin_family=AF_INET;
        local.sin_port=htons(atoi(argv[2]));
        local.sin_addr.s_addr=inet_addr(argv[1]);

        if(bind(sockfd,(struct sockaddr*)&local,sizeof(local))<0)
        {
                perror("bind");
                return 2;
        }

        if(listen(sockfd,5)<0)
        {
                perror("listen\n");
                return 5;
        }
        while(1)
        {
                int new_sockfd=accept(sockfd,NULL,NULL);
                if(new_sockfd<0)
                {
                        perror("accept\n");
                        return 6;
                }
                pid_t pid=fork();
                if(pid==0)
                {
                        if(fork()==0)
                        {
                                struct sockaddr_in client;

                                while(1)
                                {

                                        socklen_t len=sizeof(client);
                                        size_t rec=recv(new_sockfd,buf,sizeof(buf),0);
                                        if(rec<0)
                                        {
                                                printf("recv error\n");
                                                return 4;
                                        }
                                        if(rec==0)
                                        {
                                                break;;
                                        }

                                        buf[rec]='\0';
                                        printf("[%s,%d] > %s\n",inet_ntoa(client.sin_addr),ntohs(client.sin_port),buf);
                                        send(new_sockfd,buf,strlen(buf),0);
                                }
                                close(new_sockfd);//use signal to delet
                        }

                        else
                        {
                                exit(1);
                        }
                }
                else
                {
                        //wait(pid);
                }
        }

        close(sockfd);
        return 0;
}     

