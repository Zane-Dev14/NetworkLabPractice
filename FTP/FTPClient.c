#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

int port=8000;
int buf=1024;

int main(){
    int sock;
    struct sockaddr_in server_addr;
    char buffer[buf],filename[30];

    printf("\nenter name of file :");
    scanf("%s",filename);
    sock=socket(AF_INET,SOCK_STREAM,0);
    server_addr.sin_family=AF_INET;
    server_addr.sin_port=htons(port);
    inet_pton(AF_INET,"127.0.0.1",&server_addr.sin_addr);

    connect(sock,(struct sockaddr *)&server_addr,sizeof(server_addr));
    send(sock,filename,strlen(filename),0);
    recv(sock,buffer,buf,0);
    printf("Contents: %s",buffer);

}