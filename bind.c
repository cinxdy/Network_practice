#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define MYPORT 50000

int main(){
    int sockfd;
    struct sockaddr_in my_addr;
    if ((sockfd = socket(PF_INET, SOCK_STREAM, 0)) < 0) {
        perror("socket error"); 
        exit (1); 
    }
    memset(&my_addr, 0, sizeof(my_addr));
    /* bzero( (char *)&my_addr, sizeof(my_addr)); */
    my_addr.sin_family = AF_INET;
    my_addr.sin_port = htons(MYPORT);
    my_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    if (bind(sockfd, (struct sockaddr *)&my_addr, sizeof(my_addr)) < 0) {
        perror("bind error"); 
        exit(1);
    }
}