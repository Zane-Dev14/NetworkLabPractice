#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

int port=8000;
int buf=64;

int main(){
    int sock,client_sock;
    struct sockaddr_in server_addr,client_addr;
    char buffer[buf],filename[32];

    sock=socket(AF_INET,SOCK_DGRAM,0);
    server_addr.sin_family=AF_INET;
    server_addr.sin_port=htons(port);
    server_addr.sin_addr.s_addr=INADDR_ANY;
    
    bind(sock,(struct sockaddr *)&server_addr,sizeof(server_addr));
    socklen_t addr_size=sizeof(client_addr);
    recvfrom(sock,filename,32,0,(struct sockaddr *)&client_addr,&addr_size);
    
    printf("Ontents: %s",filename);
    FILE *fp=fopen(filename,"r");
    fread(buffer,1,buf,fp);
    printf("%s",buffer);
    sendto(sock,buffer,strlen(buffer),0,(struct sockaddr *)&client_addr,sizeof(client_addr));   

}