#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

int port=8000;
int buf=64;

int main(){
    int sock;
    struct sockaddr_in server_addr;
    char buffer[buf],filename[32];
    printf("enter name: ");
    scanf("%s",filename);
    sock=socket(AF_INET,SOCK_DGRAM,0);
    server_addr.sin_family=AF_INET;
    server_addr.sin_port=htons(port);
    inet_pton(AF_INET,"127.0.0.1",&server_addr.sin_addr);
        sendto(sock,filename,strlen(filename),0,(struct sockaddr *)&server_addr,sizeof(server_addr));

    recvfrom(sock,buffer,buf,0,NULL,NULL);

    printf("Response : %s",buffer);
}