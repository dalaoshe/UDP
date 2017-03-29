//
// Created by dalaoshe on 17-3-27.
//

#include "server_util.h"
#include <cstdlib>
#define MAX_NUMBER_LEN 4096
static char pi[] = "3.141592657123456789123456789";
static int getNumber(int id, char* buffer) {
    switch (id) {
        case PI: {
            sprintf(buffer,"%s",pi);
            break;
        }
        default:
            break;
    }
    return 0;
}

//根据请求常数所带的参数,判断应该回复几个分组才能传输所请求的常数长度
static int getNeedPackets(u_int8_t params) {
    int response_packet = 1;
    if((params & PARAM_P) && (params & PARAM_D))
        response_packet = 10;
    else
        response_packet = 4;
    return response_packet;
}

//打包回复的消息头,设置flag和对应的ts_hash, 不改变seq
int pack_response_hdr(struct control_hdr* hdr, int resp_size, int flag) {
    hdr->flags = flag;
    hdr->resp_len = resp_size;
    hdr->ts_hash = serverHash(hdr->ts);
}

//根据请求,将请求常数打包成最大长度固定的分组的回复包response_list, 返回分组数量
int pack_response_data(struct RequestData* request, struct ResponseData* response_list) {
    int response_packet = getNeedPackets(request->param);
    memset(response_list,0,sizeof(struct ResponseData)*response_packet);
    switch (request->cmd) {
        case GET: {
            char *buffer = new char[MAX_NUMBER_LEN];
            getNumber(request->identifier, buffer);
            for (int i = 0; i < response_packet; ++i) {
                char *data = buffer + RESPONSE_LEN * i;
                for (int j = 0; j < RESPONSE_LEN; ++j) {
                    response_list[i].data[j] = data[j];
                }
                response_list[i].response_no = i;
            }
            delete[]buffer;
            break;
        }
        default: {
            break;
        }
    }
    return response_packet;
}