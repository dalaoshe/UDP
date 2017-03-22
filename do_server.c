//
// Created by dalaoshe on 17-3-22.
//
#include "do_server.h"

static uint32_t packet_time[];
static int check_from_client(struct control_hdr* hdr) {// 基于源地址和序列号的首包丢弃策略，
    uint32_t client_auth = clientHash(hdr->ts);
    if(client_auth != hdr->ts_hash) {
        fprintf(stderr,"not from client client:%u  server:%u\n",hdr->ts_hash,client_auth);
        return 0;
    }
    return 1;
}
static int check_hdr(struct control_hdr* hdr) {
    int from_client = check_from_client(hdr);
    return from_client;
}
void pack_response_data(struct RequestData* request, struct control_hdr* hdr, struct ResponseData* response) {
    switch (request->cmd) {
        case GET:
            switch (request->identifier) {
                case PI: {
                    if((request->param & PARAM_P) && (request->param & PARAM_D))
                        *((double *) response->data) = 3.14159265f;
                    else
                        *((double *) response->data) = 3.1415f;
                    printf("recv request pi\n");
                    break;
                }
                default:
                    break;
            }
            break;
        default:
            break;
    }
    hdr->ts_hash = serverHash(hdr->ts);
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
        int flags = 0;
        struct unp_in_pktinfo info;
        struct control_hdr hdr;
        struct RequestData request;
        struct ResponseData response;
        memset(&response,0,sizeof(response));
        memset(&request,0,sizeof(request));
        memset(&hdr,0,sizeof(hdr));
        memset(&info,0,sizeof(info));

        Recvfrom_flags(sockfd, &hdr, sizeof(hdr), &request, sizeof(request), &flags, (SA*)&client_addr, &len, &info);
        printf("\n\nrecv request\n");
        if(check_hdr(&hdr)) { //检验合法性
            pack_response_data(&request, &hdr, &response);// 根据请求打包回复的包头和数据
            Sendto(sockfd, &hdr, sizeof(hdr), &response, sizeof(response), (SA*)&client_addr, len);
            printf("send ack seq=%u\n",hdr.seq);
        }
    }
}

