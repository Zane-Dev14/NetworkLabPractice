#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

int port=8000;
int buf=1024;
 
int main(){
    int sock,client_sock;
    socklen_t addr_size;
    struct sockaddr_in server_addr,client_addr;
    char buffer[buf],filename[30];

    sock=socket(AF_INET,SOCK_STREAM,0);
    server_addr.sin_addr.s_addr=INADDR_ANY;
    server_addr.sin_family=AF_INET;
    server_addr.sin_port=htons(port);

    bind(sock,(struct sockaddr *)&server_addr,sizeof(server_addr));
    listen(sock,5);
    addr_size=sizeof(client_addr);
    client_sock=accept(sock,(struct sockaddr *)&client_addr,&addr_size);
    read(client_sock,filename,30);
    printf("Filanem : %s",filename);
    FILE* fp =fopen(filename,"r");
    fread(buffer,1,buf,fp);
    write(client_sock,buffer,buf);
}