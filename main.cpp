#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <memory.h>
#include "cstdio"
#define SERV_PORT 6666
#define CLIENT_PORT 5555
#define MAX_LEN 4096

typedef struct sockaddr* SA;

int main(int argc, char **argv) {
    std::cout << "Hello, World!" << std::endl;
    int sockfd;
    struct sockaddr_in servaddr;
    struct sockaddr_in clientaddr
    ;
    memset(&servaddr,0,sizeof(servaddr));
    memset(&clientaddr,0,sizeof(clientaddr));

    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(SERV_PORT);
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);

    clientaddr.sin_family = AF_INET;
    clientaddr.sin_port = htons(CLIENT_PORT);
    clientaddr.sin_addr.s_addr = htonl(INADDR_ANY);


    //Inet_pton(AF_INET,argv[1], &servaddr.sin_addr);
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if(sockfd < 0) {
        printf("ERROR\n");
    }
    if(strcmp(argv[1],"1") == 0) {
        printf("server\n");
        bind(sockfd, (sockaddr *) &servaddr, sizeof(struct sockaddr_in));
        int n;
        socklen_t len = sizeof(clientaddr);
        char cache[MAX_LEN];
        while (1) {
            recvfrom(sockfd, cache, MAX_LEN, 0, (sockaddr*)&clientaddr, &len);
            printf("recv client: %s \n",cache);
            strcpy(cache, "server get u msg\n");
            sendto(sockfd, cache, MAX_LEN, 0, (SA) &clientaddr, len);
            //printf("send: %s \n",cache);
        }
    }
    else {
        printf("client\n");
        int n;
        socklen_t len = sizeof(clientaddr);
        char cache[MAX_LEN] = "client send u msg\n";
        while(1) {
            sendto(sockfd, cache, MAX_LEN, 0, (SA) &servaddr, len);
            recvfrom(sockfd, cache, MAX_LEN, 0, NULL, NULL);
            printf("recv server: %s \n", cache);
        }
    }
    return 0;
}