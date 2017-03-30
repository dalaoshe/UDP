//
// Created by dalaoshe on 17-3-29.
//

#ifndef UDP_UDPTHREAD_H
#define UDP_UDPTHREAD_H

#include <pthread.h>
#include "unprtt.h"
#define MAX_SERVER_THREAD_NUMBER 3
int dec_counter(uint32_t *counter, pthread_mutex_t *mutex, uint32_t threshold);
int inc_counter(uint32_t *counter, pthread_mutex_t *mutex, uint32_t threshold);
struct do_response_para {
    struct control_hdr hdr;
    struct RequestData request;
    struct sockaddr_in client_addr;
            socklen_t len;
    struct unp_in_pktinfo info;
};
struct ThreadPool;
struct ThreadPool* initThreadPool(struct ThreadPool* threadPool, uint32_t threads_number);
pthread_t* getIdleThread(struct ThreadPool* threadPool);
void freeThread(struct ThreadPool* threadPool, pthread_t pid);
#endif //UDP_UDPTHREAD_H
