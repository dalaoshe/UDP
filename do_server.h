//
// Created by dalaoshe on 17-3-21.
//

#ifndef UDP_DO_SERVER_H_H
#define UDP_DO_SERVER_H_H

#include "recvfrom_flags.h"
#define IDENTIFIER_LEN 10
#define RESPONSE_LEN 10
#define PI 0
struct RequestData {
    char identifier[IDENTIFIER_LEN];
    char data[RESPONSE_LEN];
};

struct ResponseData {
    char identifier[IDENTIFIER_LEN];
    char data[RESPONSE_LEN];
};

uint32_t getCmd(struct RequestData request);

void do_server();


#endif //UDP_DO_SERVER_H_H
