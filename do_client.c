//
// Created by dalaoshe on 17-3-22.
//

#include "do_client.h"
void printRequest(struct RequestData* data) {
    printf("request %u %u %u \n",data->cmd, data->identifier, data->param);
}
uint32_t getCmd(char cmd_str[]) {
   // printf("cmd %s1\n",cmd_str);
    if((strcmp(cmd_str,"GET") == 0)) {
      //  printf("CMD GET\n");
        return GET;
    }

    return ERROR_CMD;
}
uint32_t getIdentifier(char identifier[]) {
  //  printf("identif %s\n",identifier);
    if(strcmp(identifier,"PI") == 0) {
        return PI;
    }

    return ERROR_IDENTIFIER;
}
u_int8_t getParam(char param[]) {
   // printf("param %s\n",param);
    if(strcmp(param,"-l=10") == 0) {
        //printf("param %s\n",param);
        return (PARAM_P | PARAM_D);
    }

    return 0;
}
uint32_t pack_request_data(char cmd_str[], struct RequestData* data) {
    FILE* fd = fmemopen(cmd_str,strlen(cmd_str),"r");
    char c; //

    int status = 0; // 状态机
    char cmd[CMD_LEN]; // 命令字符串
    char identifier[IDENTIFIER_LEN]; // 常数字符串
    char params[PARAMS_LEN];// 参数字符串
    memset(params,0,sizeof(params));
    memset(identifier,0,sizeof(identifier));
    memset(cmd,0,sizeof(cmd));
    uint32_t index = 0;
    uint32_t n = 0;// 读取多少位

    data->cmd = ERROR_CMD;
    data->identifier = ERROR_IDENTIFIER;
    data->param = 0;
    int over = 0;
    while((c = getc(fd)) != EOF) {
        if(over)break;
        n++;
        if(c == '\n' || c == '\r') {
            if(status == 0)continue;
            break;
        }
        if(c == ' ') {
            if((status & 1)== 0) continue;//偶数表示正在过滤空格
            if(status == 1) {// CMD读取完毕
                cmd[index] = 0;
                status = 2;// 过滤cmd之后的空格
                index = 0;
                continue;
            }
            if(status == 3) {// 请求常数标识符读取完毕
                identifier[index] = 0;
                status = 4;// 过滤常数标识符之后的空格
                index = 0;
                continue;
            }
            if(status == 5) {// 参数读取完毕
                params[index] = 0;
                break;// 结束本次读取
            }
        }
        else {
            switch (status) {
                case 0: {//开始cmd的读取
                    cmd[index] = c;
                    status = 1;
                    index++;
                    break;
                }
                case 1: {//继续读取cmd
                    cmd[index] = c;
                    status = 1;
                    index++;
                    break;
                }
                case 2: {//开始常数标识符读取
                    identifier[index] = c;
                    status = 3;
                    index++;
                    break;
                }
                case 3: {// 继续读取常数标识符
                    identifier[index] = c;
                    status = 3;
                    index++;
                    break;
                }
                case 4: {
                    if(c == '-') {// 读取请求参数
                        params[index] = c;
                        status = 5;
                        index++;
                    }
                    else {// 下一个请求
                        n = n-1;
                        over = 1;
                    }
                    break;
                }
                case 5: {
                    params[index] = c;
                    index++;
                    break;
                }
                default: {

                }
            }
        }
    }
    data->cmd = getCmd(cmd);
    data->identifier = getIdentifier(identifier);
    data->param = getParam(params);
    //mprintf("\n");
    return n;
}
struct ResponseData* getResponseById(struct ResponseData* base, int pkt_len, int id) {
    for(int i = 0; i < pkt_len; ++i) {
        struct ResponseData* data = base+i;
        if(data->response_no == id) return data;
    }
    return base;
}
void do_client() {


    struct sockaddr_in servaddr;
    struct sockaddr_in clientaddr;
    memset(&servaddr,0,sizeof(servaddr));
    memset(&clientaddr,0,sizeof(clientaddr));

    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(SERV_PORT);
    int res = inet_pton(AF_INET, "59.66.134.48", &servaddr.sin_addr);
    //servaddr.sin_addr.s_addr = htonl("59.66.134.48");
    socklen_t len = sizeof(servaddr);

    int sockfd = Socket(AF_INET, SOCK_DGRAM, 0);
    Socket_Peer_Connect(sockfd, (SA*) &servaddr, len);

    char cmd_str[MAX_LEN]  = "PI" ;
    char name[MAX_LEN] = "test.txt";
    printf("client start\n");
    FILE* file;
    if(!(file = fopen(name, "r"))) {
        fprintf(stderr, "open file:%s failed \n", name);
    }
    size_t n = fread(cmd_str,1,MAX_LEN,file);
    int index = 0;
    struct ResponseData responseData[MAX_RESPONSE_PACKET];
    struct RequestData requestData;
    while(index < n) {

        memset(responseData, 0, sizeof(struct ResponseData)*MAX_RESPONSE_PACKET);
        printf("YOU ARE SENDING REQUEST: \n%s\n...........\n",cmd_str);
        index += pack_request_data(cmd_str+index, &requestData);

        int resp_pkt_len = Client_send_recv(sockfd, &requestData, sizeof(requestData), responseData, sizeof(struct ResponseData), (SA*)&servaddr, len);
        if(resp_pkt_len < 0) {
            printf("ERROR: RECV %d PKT, ERROR\n",resp_pkt_len);
        }
        else {
            printf("INFO: RECV %d PKT FROM SERVER\nGET NUMBER: ", resp_pkt_len);
            for(int i = 0; i < resp_pkt_len; ++i) {
                struct ResponseData *response = getResponseById(responseData, resp_pkt_len, i);
                for(int j = 0; j < RESPONSE_LEN; ++j)
                    printf("%c",response->data[j]);
            }
            printf("\nOVER\n");
        }

        sleep(10);
    }
}