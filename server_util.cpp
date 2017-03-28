//
// Created by dalaoshe on 17-3-27.
//

#include "server_util.h"
#include <cstdlib>
#define setBit(x,y) { y = 1 << y; x = x | y; }
#define clearBit(x,y) { y = 1 << y; x = x ^ y; }
#define getBit(x,y) { y = 1 << y; }
static double pi = 3.1415927365298276735725375;
static int getNumber(int id, char* buffer) {
    switch (request->identifier) {
        case PI: {
            sprintf(buffer,"%lf0",pi);
            break;
        }
        default:
            break;
    }
    return 0;
}

static int getNeedPackets(u_int8_t params) {
    int response_packet = 1;
    if((request->param & PARAM_P) && (request->param & PARAM_D))
        response_packet = 4;
    else
        response_packet = 1;
    return response_packet;
}

int pack_response_hdr(struct control_hdr* hdr, int flag) {
    hdr->ts_hash = serverHash(hdr->ts);
}
int pack_response_data(struct RequestData* request, struct ResponseData* response_list) {
    int response_packet = getNeedPackets(request->param);
    memset(response_list,0,sizeof(struct ResponseData)*response_packet);
    switch (request->cmd) {
        case GET:
            char *buffer = new buffer[4096];
            getNumber(request->identifier, buffer);
            for(int i = 0; i < response_packet; ++i) {
                char* data = buffer+RESPONSE_LEN*i;
                for(int j = 0; j < RESPONSE_LEN; ++j) {
                    response_list[i].data[j] = data[j];
                }
                response_list[i].response_no = i;
            }
            break;
        default:
            break;
    }
    return response_packet;
}