#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

int port=8000;
int buf=1024;

int main(){
    int sock;
    struct sockaddr_in server_addr,client_addr;
    char buffer[buf];
    socklen_t addr_size;

    printf("Enter message to send: \n");
    scanf("%s",buffer);
    sock=socket(AF_INET,SOCK_STREAM,0);
    if (sock<0)printf("Failed to connect");
    
    server_addr.sin_port=htons(8000);
    server_addr.sin_family=AF_INET;
    inet_pton(AF_INET,"127.0.0.1",&server_addr.sin_addr);
   
    connect(sock,(struct sockaddr *)&server_addr,sizeof(server_addr));
    send(sock,buffer,buf,0);
    buffer[buf]='\0';
    recv(sock,buffer,buf,0);
    printf("From server: %s",buffer);
    
}