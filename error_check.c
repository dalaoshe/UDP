//
// Created by dalaoshe on 17-3-22.
//

#include "unp.h"

int Socket(int __domain, int __type, int __protocol) {
    int sockfd = socket(__domain, __type, __protocol);
    if(sockfd < 0) {
        printf("Cannot returns a file descriptor for the new socket! \n");
        exit(1);
    }
    return sockfd;
}

int Socket_Peer_Connect(int __fd, __CONST_SOCKADDR_ARG __addr, socklen_t __len) {
    int result = connect(__fd, __addr, __len);
    if(result < 0) {
        printf("Cannot set the peer connection ! \n");
        exit(0);
    }
    return result;
}

int Bind_Socket(int __fd, __CONST_SOCKADDR_ARG __addr, socklen_t __len) {
    if(bind(__fd, __addr, __len)) {
        printf("bind socket \n");
        exit(1);
    }
    return 0;
}