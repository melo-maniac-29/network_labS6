#include<stdio.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<netdb.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include <arpa/inet.h>

#define SERV_TCP_PORT 5035
#define MAX 60
int main(int arg,char*argv[])
{
       int sockfd,n;
       struct sockaddr_in serv_addr;
       struct hostent*server;
       char send[MAX],recvline[MAX],s[MAX],name[MAX];

       //socket creation.
       sockfd=socket(AF_INET,SOCK_STREAM,0);

       //server info.
       serv_addr.sin_family=AF_INET
       serv_addr.sin_addr.s_addr=inet_addr("127.0.0.1");
       serv_addr.sin_port=htons(SERV_TCP_PORT);

       //connect to the server.
       connect(sockfd,(struct sockaddr*)&serv_addr,sizeof(serv_addr));
       printf("\nEnter the source file name : \n");
       scanf("%s",send);

       //send file name the socket.
       write(sockfd,send,MAX);

       //receive response from the server.
       while((n=read(sockfd,recvline,MAX))!=0)
       {
          printf("%s",recvline);
       }

       //close the connection.
       close(sockfd);
       return 0;
}
