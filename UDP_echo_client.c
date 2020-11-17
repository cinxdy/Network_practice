#define BUFSIZE 30
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>

void error_handling(char *message);

int main(int argc, char **argv){
    int sock;
    char message[BUFSIZE];
    int str_len, addr_size, i;
    char MSG1[] = "Hello ";
    char MSG2[] = "World ";
    char MSG3[] = "Bye";
    struct sockaddr_in serv_addr;
    struct sockaddr_in from_addr;
    if(argc!=3){
        printf("Usage : %s <IP> <port>\n", argv[0]);
        exit(1);
    }
    sock=socket(PF_INET, SOCK_DGRAM, 0);
    if(sock == -1)
        error_handling("UDP 소켓생성오류");

    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family=AF_INET;
    serv_addr.sin_addr.s_addr=inet_addr(argv[1]);
    serv_addr.sin_port=htons(atoi(argv[2]));
    sendto(sock, MSG1, strlen(MSG1), 0, (struct sockaddr*)&serv_addr, sizeof(serv_addr));
    sendto(sock, MSG2, strlen(MSG2), 0, (struct sockaddr*)&serv_addr, sizeof(serv_addr));
    sendto(sock, MSG3, strlen(MSG3), 0, (struct sockaddr*)&serv_addr, sizeof(serv_addr));
    
    for(i=0; i<3; i++){
        addr_size = sizeof(from_addr);
        str_len = recvfrom(sock, message, BUFSIZE, 0, (struct sockaddr*)&from_addr, &addr_size);
        message[str_len]=0;
        printf("서버로부터수신된%d차메시지: %s \n", i, message);
    }
    close(sock);
    return 0;
}

void error_handling(char *message){
    fputs(message, stderr);
    fputc('\n', stderr);
    exit(1);
}
