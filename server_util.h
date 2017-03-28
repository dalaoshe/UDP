//
// Created by dalaoshe on 17-3-27.
//

#ifndef UDP_SERVER_UTIL_H
#define UDP_SERVER_UTIL_H

#include "unprtt.h"
#include "token_bucket.h"
#define MOREPACKET 1
int pack_response_data(struct RequestData* request, struct ResponseData* response);
int pack_response_hdr(struct control_hdr* hdr, int resp_size, int flag);
#endif //UDP_SERVER_UTIL_H
