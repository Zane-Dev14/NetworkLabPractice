#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>

int port=8000;
int buf=1024;
int windowSize=3;
int totalFrames=5;


int main(){
    int sock, client_sock;
    struct sockaddr_in server_addr,client_addr;
    socklen_t addr_size;
    char buffer[64],buffer2[64];

    sock=socket(AF_INET,SOCK_STREAM,0);
    server_addr.sin_family=AF_INET;
    server_addr.sin_port=htons(port);
    server_addr.sin_addr.s_addr=INADDR_ANY;

    bind(sock, (struct sockaddr *)&server_addr,sizeof(server_addr));
    listen(sock,5);
    addr_size=sizeof(client_addr);
    client_sock=accept(sock,(struct sockaddr *)&client_addr,&addr_size );

    for(int i=0;i<totalFrames;i++){
        read(client_sock,buffer,64);
        printf("Demo: %s\n",buffer);}

    printf("go back n \n\n");
    int expectedFrame=0;
    while(expectedFrame<totalFrames){
        int receivedFrames=0;
        for (int i=0;i<windowSize&&(expectedFrame+i)<totalFrames;i++){
            read(client_sock,buffer,64);
            printf("\nGot Frame %d: %s\n",expectedFrame+i,buffer);
            printf("Send ACK for frame %d??",expectedFrame+i);
            fflush(stdout);

            scanf("%s",buffer2);
            if (strcmp(buffer2,"yes")==0){receivedFrames++;
}
            else{printf("\nSending NACK for frame %d",expectedFrame+i);break;}
        }
        if(receivedFrames>0){
            expectedFrame+=receivedFrames;
            int ack = expectedFrame - 1;
            printf("\nSending ack %d\n\n", ack);
            write(client_sock, &ack, sizeof(ack));
        }else{    printf("\nNo progress made. Waiting for retransmission...\n\n");int ack = expectedFrame - 1;
            printf("\nSending ack %d\n\n", ack);
            write(client_sock, &ack, sizeof(ack));}
        
        if (expectedFrame>=totalFrames){break;}
    }
    printf("\nDONE");
}