//
// Created by dalaoshe on 17-3-22.
//
#include "do_server.h"
void do_server() {
    struct sockaddr_in server_addr, client_addr;
    socklen_t len = sizeof(client_addr);

    memset(&server_addr, 0, sizeof(server_addr));
    memset(&client_addr, 0, sizeof(client_addr));
    int sockfd = socket(AF_INET, SOCK_DGRAM, 0);

    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    server_addr.sin_port = htons(SERV_PORT);

    printf("server\n");
    if(bind(sockfd, (struct sockaddr *) &server_addr, sizeof(struct sockaddr_in))) {
        printf("erro sock");
    }

    int n;

    char rev[MAX_LEN];
    char msg[MAX_LEN];
    int flags;
    struct unp_in_pktinfo info;
    while (1) {
        memset(rev,0,MAX_LEN);
        struct control_hdr hdr;
        struct RequestData request;
        struct ResponseData response;
        int flags;
        struct unp_in_pktinfo info;
        Recvfrom_flags(sockfd, &hdr, &request, sizeof(request), &flags, (SA*)&client_addr, &len, &info);
        printf("seq %u, recv client request: what is %s ?\n",hdr.seq, request.identifier);
        strcpy(response.identifier,request.identifier);
        uint32_t cmd = getCmd(request);
        switch (cmd) {
            case PI:
                *((double*)response.data) = 3.1415f;
                printf("pi");
                break;
            default:
                break;
        }
        Sendto_flags(sockfd, &hdr, &response, sizeof(response), &flags, (SA*)&client_addr, len);
    }
}

uint32_t getCmd(struct RequestData request) {
    if(strcmp(request.identifier, "PI") == 0) return PI;
}
