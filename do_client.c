//
// Created by dalaoshe on 17-3-22.
//

#include "do_client.h"
uint32_t getCmd(char cmd_str[]) {
    if(strcmp(cmd_str,"PI") == 0) {
        return PI;
    }
    return 0xffffffff;
}
void do_client() {


    struct sockaddr_in servaddr;
    struct sockaddr_in clientaddr;
    memset(&servaddr,0,sizeof(servaddr));
    memset(&clientaddr,0,sizeof(clientaddr));

    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(SERV_PORT);
    servaddr.sin_addr.s_addr = htonl(INADDR_LOOPBACK);
    socklen_t len = sizeof(servaddr);

    int sockfd = Socket(AF_INET, SOCK_DGRAM, 0);
    Socket_Peer_Connect(sockfd, (SA*) &servaddr, len);

    char cmd_str[MAX_LEN]  = "PI" ;

    printf("client start\n");
    while(1) {
        struct RequestData requestData;
        struct ResponseData responseData;
        uint32_t cmd = getCmd(cmd_str);
        requestData.cmd = cmd;
        printf("fd %d \n",sockfd);
        Dg_send_recv(sockfd, &requestData, sizeof(requestData), &responseData, sizeof(responseData), (SA*)&servaddr, len);
        printf("recv server: %lf \n", *((double*)(responseData.data)));

        sleep(10);
    }
}