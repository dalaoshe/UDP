//
// Created by dalaoshe on 17-3-22.
//
#include "do_server.h"
#include "server_util.h"
#include "UDPThread.h"

static struct Token_Bucket output_token_bucket;
static struct TokenBucketMap *ip_input_token_bucket;
static struct sockaddr_in server_addr;
static struct ThreadPool* threadPool;
static pthread_mutex_t thread_counter_mutex = PTHREAD_MUTEX_INITIALIZER;
static uint32_t thread_counter;


static int check_from_client(struct control_hdr* hdr) {// 确认请求包来自客户端
    uint32_t client_auth = clientHash(hdr->ts);
    if(client_auth != hdr->ts_hash) {
        fprintf(stderr,"not from client client:%u  server:%u\n",hdr->ts_hash,client_auth);
        return 0;
    }
    return 1;
}
static int check_hdr(struct control_hdr* hdr) { // 检验请求包头信息
    int from_client = check_from_client(hdr);
    int no_time_out = checkTimeOut(hdr->ts);
    return from_client && no_time_out;
}
static int has_input_token(uint32_t ip) {
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

void* do_response(void* argv) {
    pthread_detach(pthread_self());
    struct do_response_para *para = (struct do_response_para *) argv;

    int sockfd = Socket(AF_INET, SOCK_DGRAM, 0);
    int opt = 1;
    setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, (const void *)&opt, sizeof(opt));
    Bind_Socket(sockfd, (struct sockaddr *) &server_addr, sizeof(struct sockaddr_in));

    printf("\n<---- do response sleep 3 first%u tid %lu---->\n",para->client_addr.sin_addr.s_addr,pthread_self());

    //sleep(3);
    struct ResponseData response[MAX_RESPONSE_PACKET];
    memset(response,0,sizeof(struct ResponseData)*MAX_RESPONSE_PACKET);

    if(check_hdr(&para->hdr)) { // 通过消息头, 检验请求合法性
        printf("valid hdr\n");
        if(has_input_token((&para->client_addr)->sin_addr.s_addr)) {//令牌桶 检验该ip是否有进入流量资格
            printf("has input token\n");
            if (getToken(&output_token_bucket)) {//令牌桶 检验服务器是否还有出口流量
                printf("get output token\n");
                int pkt_len = pack_response_data(&para->request, response);// 根据请求打包回复的分组序列
                for(int i = 0 ; i < pkt_len; ++i) {// 将分组逐一发送
                    pack_response_hdr(&para->hdr, pkt_len, (pkt_len-1-i)); // 设置每个分组的对应消息头
                    Sendto(sockfd, &para->hdr, sizeof(struct control_hdr), response+i, sizeof(struct ResponseData), (SA *) &para->client_addr, para->len);
                }
                printf("INFO: there are tokens=%u left\n", output_token_bucket.tokens);
            } else {
                printf("REJECT: no output token wait ! %u\n", output_token_bucket.tokens);
            }
        }
        else {
            printf("REJECT: no input token wait\n");
        }
    }
    close(sockfd);

    pthread_t pid = pthread_self();
    printf("\n<---- free tid %lu---->\n",pid);
    freeThread(threadPool, pid);
    pthread_exit(0);

    return (NULL);
}

void do_server() {

    memset(&server_addr, 0, sizeof(server_addr));


    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    server_addr.sin_port = htons(SERV_PORT);

    int sockfd = Socket(AF_INET, SOCK_DGRAM, 0);
    int opt = 1;
    setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, (const void *)&opt, sizeof(opt));
    Bind_Socket(sockfd, (struct sockaddr *) &server_addr, sizeof(struct sockaddr_in));

    //初始化限制外出流量的令牌桶
    memset(&output_token_bucket, 0, sizeof(output_token_bucket));
    output_token_bucket.capacity = SERVER_OUTPUT_CAPACITY;
    output_token_bucket.token_fill_rate = SERVER_OUTPUT_FILL_RATE;
    output_token_bucket.tokens = output_token_bucket.capacity >> 1;
    output_token_bucket.last_update_time = time(NULL);

    //初始化入口流量令牌桶(每个访问用户分配一个,)
    ip_input_token_bucket = initTokenBucket(ip_input_token_bucket);
    //初始化线程池
    threadPool = initThreadPool(threadPool, MAX_SERVER_THREAD_NUMBER);

    printf("<---- SERVER START..... ---->\n\n");
    while (1) {

        // 每次接收前清空缓存
        struct control_hdr hdr;
        struct RequestData request;
        struct unp_in_pktinfo info;
        struct sockaddr_in client_addr;

        socklen_t len = sizeof(client_addr);
        int flags = 0;

        memset(&hdr,0,sizeof(hdr));
        memset(&request,0,sizeof(request));
        memset(&info,0,sizeof(info));
        memset(&client_addr, 0, sizeof(client_addr));
        // 接收请求
        printf("\n2next\n");
        if(Recvfrom_flags(sockfd, &hdr, sizeof(hdr), &request, sizeof(request), &flags, (SA*)&client_addr, &len, &info)
           < (sizeof(hdr) + sizeof(request)))// 收到小于协议长度的包,不再处理
            continue;
        printf("\n<---- GET AN REQUEST FROM %u ---->\n",client_addr.sin_addr.s_addr);

        pthread_t *tid = getIdleThread(threadPool);
        if(tid == 0) {// 线程池满不处理请求，客户端自动超时重传
            printf("no thread\n");
            continue;
        }
        struct do_response_para para;
        memset(&para,0,sizeof(struct do_response_para));
        para.client_addr = client_addr;
        para.hdr = hdr;
        para.request = request;
        para.info = info;
        para.len = len;
        pthread_create(tid, NULL, &do_response, (void*)&para);
        printf("\n1next\n");
    }
}

