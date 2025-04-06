#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>

int port=8000;
int buf=1024;

int main(){
    int sock;int j=0;
    struct sockaddr_in server_addr,client_addr;
    char buffer[buf],buffer2[buf];
    socklen_t addr_size;

    sock=socket(AF_INET,SOCK_DGRAM,0);if(sock<0)printf("Could not connect Socket.\n");else{printf("Connected socket\n");}
    server_addr.sin_port=htons(port);
    server_addr.sin_family=AF_INET;
    server_addr.sin_addr.s_addr=INADDR_ANY;

    addr_size=sizeof(client_addr);
    bind(sock,(struct sockaddr *)&server_addr,sizeof(server_addr));

    recvfrom(sock,buffer,buf,0,(struct sockaddr *)&client_addr,&addr_size);
    printf("Buffer :%s",buffer);
    for(int i=strlen(buffer)-1;i>=0;i--){
        buffer2[j]=buffer[i];
        j++;
    }buffer2[j]='\0';
    sendto(sock,buffer2,strlen(buffer2),0,(struct sockaddr *)&client_addr,sizeof(client_addr));
}