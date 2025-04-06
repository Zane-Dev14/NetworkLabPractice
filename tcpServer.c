#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

int port=8000;
int buf=1024;

int main(){
    struct sockaddr_in server_addr,client_addr;
    int sock,client_sock;
    socklen_t addr_size;
    char buffer[buf];
    char buffer2[buf];

    sock=socket(AF_INET,SOCK_STREAM,0);
    if(sock<0){printf("No socket");}else{printf("Sock");}
    server_addr.sin_family=AF_INET;
    server_addr.sin_port=htons(port);
    server_addr.sin_addr.s_addr=INADDR_ANY;
    
    if (bind(sock,(struct sockaddr *)&server_addr,sizeof(server_addr))<0){printf("Could not bind");}else{printf("Binded socket at port %d.\n",port);}
    addr_size=sizeof(client_addr);
    
    listen(sock,5);
    client_sock=accept(sock,(struct sockaddr *)&client_addr,&addr_size);
    read(client_sock,buffer,buf);
    
    int j=0;
    for(int i=strlen(buffer)-1;i>=  0;i--){
        buffer2[j]=buffer[i];
        j++;
    }buffer2[j]='\0';
    send(client_sock,buffer2,strlen(buffer2),0);
}