#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

int port=8000;
int buf=1024;
int totalFrames=5;
int windowSize=3;

int main(){
    struct sockaddr_in server_addr;
    int sock;
    char buffer[64],buffer2[64];
    int ack;
    sock=socket(AF_INET,SOCK_STREAM,0);

    server_addr.sin_family=AF_INET;
    server_addr.sin_port=htons(port);
    inet_pton(AF_INET,"127.0.0.1",&server_addr.sin_addr);

    connect(sock,(struct sockaddr *)&server_addr,sizeof(server_addr));
    printf("Going 1in\n");
    for(int i=0;i<totalFrames;i++){
        sprintf(buffer,"Frame %d",i);
        write(sock,buffer,64);
        printf("Demo Sent %s\n",buffer);
    }   

    int base=0;
    while(base<totalFrames){
        for (int i=base;i<totalFrames&&i<windowSize+base;i++){
            sprintf(buffer,"Frame %d",i);
            write(sock, buffer,64);
            printf("Sent %s\n",buffer);
        }
        read(sock, &ack,sizeof(ack));
        printf("Recieved ACK for %d\n",ack);
        if(ack<base){
            printf("No progress, retransmitting from frame %d\n\n", base);
        }else{
            base=ack+1;
                        printf("Sliding window moves to frame %d\n\n", base);
            if( base >=totalFrames){break;}
        }

    }

}