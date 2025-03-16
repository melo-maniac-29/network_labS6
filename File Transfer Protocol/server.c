#include<stdio.h>
#include<arpa/inet.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<netdb.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#define SERV_TCP_PORT 5035
#define MAX 60

char buff[4096];
FILE *f1;

int main(int afg, char *argv)
{
       int sockfd, newsockfd, clength;
       struct sockaddr_in serv_addr,cli_addr;
       char str[MAX];

       //socket creation.
       sockfd=socket(AF_INET, SOCK_STREAM,0);
       
       //server info.
       serv_addr.sin_family=AF_INET;
       serv_addr.sin_addr.s_addr=INADDR_ANY;
       serv_addr.sin_port=htons(SERV_TCP_PORT);
       
       //bind the server into with the socket.
       printf("\nBinded");
       bind(sockfd,(struct sockaddr*)&serv_addr, sizeof(serv_addr));
       
       //listen for client connections.
       printf("\nListening...");
       listen(sockfd, 5);
       clength=sizeof(cli_addr);

       //create client socket.
       newsockfd=accept(sockfd,(struct sockaddr*) &cli_addr,&clength);
       close(sockfd);
       
       //read the command from the client.
       read(newsockfd, &str, MAX);
       printf("\nClient message\n File Name : %s\n", str);
       f1=fopen(str, "r");
       
       //read the data from the file.
       while(fgets(buff, 4096, f1)!=NULL)
       {
            write(newsockfd, buff,MAX);
            printf("\n");
       }
       fclose(f1);
       close(newsockfd);
       printf("\nFile Transferred\n");
       return 0;
}
