//
// Created by dalaoshe on 17-3-22.
//
#include "do_server.h"
int check_hdr(struct control_hdr* hdr) {
    return 1;
}
void pack_response_data(struct RequestData* request, struct control_hdr* hdr, struct ResponseData* response) {
    switch (request->cmd) {
        case PI:
            *((double*)response->data) = 3.1415f;
            printf("recv request pi\n");
            break;
        default:
            break;
    }
}
void do_server() {
    struct sockaddr_in server_addr, client_addr;
    socklen_t len = sizeof(client_addr);

    memset(&server_addr, 0, sizeof(server_addr));
    memset(&client_addr, 0, sizeof(client_addr));
    int sockfd = Socket(AF_INET, SOCK_DGRAM, 0);

    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = htonl(INADDR_LOOPBACK);
    server_addr.sin_port = htons(SERV_PORT);

    Bind_Socket(sockfd, (struct sockaddr *) &server_addr, sizeof(struct sockaddr_in));

    printf("server start\n");
    while (1) {
        struct control_hdr hdr;
        struct RequestData request;
        struct ResponseData response;
        int flags;
        struct unp_in_pktinfo info;

//        memset(&client_addr, 0, sizeof(client_addr));
        Recvfrom_flags(sockfd, &hdr, sizeof(hdr), &request, sizeof(request), &flags, (SA*)&client_addr, &len, &info);
        printf("\n\nrecv request\n");
        if(check_hdr(&hdr)) { //检验合法性

            pack_response_data(&request, &hdr, &response);// 根据请求打包回复的包头和数据

            Sendto(sockfd, &hdr, sizeof(hdr), &response, sizeof(response), (SA*)&client_addr, len);
            printf("send ack seq=%u\n",hdr.seq);
        }
    }
}

