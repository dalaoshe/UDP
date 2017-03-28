//
// Created by dalaoshe on 17-3-22.
//
#include "do_server.h"
#include "token_bucket.h"
static struct Token_Bucket output_token_bucket;
static struct TokenBucketMap *ip_input_token_bucket;
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
    int no_time_out = checkTimeOut(hdr->ts);
    return from_client && no_time_out;
}
static int has_input_token(uint32_t ip) {
    printf("check input_token\n");
    // Lazy方式情况过期的令牌桶记录
    clearTimeOutTokenBucket(ip_input_token_bucket);
    if(exist(ip_input_token_bucket, ip)) {
        int token = getToken(getTokenBucket(ip_input_token_bucket,ip));
        if(!token) {
            fprintf(stderr, "%u bucket exist but not token\n", ip);
            return 0;
        }
    }
    else {
        fprintf(stderr, "add an bucket for %u\n", ip);
        addTokenBucket(ip_input_token_bucket,ip);
        int token = getToken(getTokenBucket(ip_input_token_bucket,ip));
        return token;
    }
}
static void pack_response_data(struct RequestData* request, struct control_hdr* hdr, struct ResponseData* response) {
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
    // 设置时间戳和对应的hash值
    hdr->ts = time(NULL);
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
    //初始化限制外出流量的令牌桶
    memset(&output_token_bucket, 0, sizeof(output_token_bucket));
    output_token_bucket.capacity = SERVER_OUTPUT_CAPACITY;
    output_token_bucket.token_fill_rate = SERVER_OUTPUT_FILL_RATE;
    output_token_bucket.tokens = output_token_bucket.capacity >> 1;
    output_token_bucket.last_update_time = time(NULL);

    //初始化入口流量令牌桶(每个访问用户分配一个,)
    ip_input_token_bucket = initTokenBucket(ip_input_token_bucket);

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
        printf("\nrequest\n");
        if(check_hdr(&hdr)) { //检验合法性
            if(has_input_token(client_addr.sin_addr.s_addr)) {//令牌桶 检验该ip是否有进入流量资格
                if (getToken(&output_token_bucket)) {//令牌桶 检验服务器是否还有出口流量
                    pack_response_data(&request, &hdr, &response);// 根据请求打包回复的包头和数据
                    Sendto(sockfd, &hdr, sizeof(hdr), &response, sizeof(response), (SA *) &client_addr, len);
                    printf("leafover token=%u\n", output_token_bucket.tokens);
                } else {
                    printf("no token wait ! %u\n", output_token_bucket.tokens);
                }
            }
            else {
                printf("no input token wait\n");
            }
        }
    }
}

