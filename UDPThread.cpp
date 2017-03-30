//
// Created by dalaoshe on 17-3-29.
//
#include "UDPThread.h"
#include <map>
//#define THREAD_POOL_DEBUG
struct ThreadPool{
    pthread_t *threads;
    uint32_t threads_number;
    pthread_mutex_t pool_mutex;
    ThreadPool(uint32_t threads_number) {
        threads = new pthread_t[threads_number];
        this->threads_number = threads_number;
        memset(threads, 0, sizeof(pthread_t)*threads_number);
        pool_mutex = PTHREAD_MUTEX_INITIALIZER;
    }
};
struct ThreadPool* initThreadPool(struct ThreadPool* threadPool, uint32_t threads_number) {
    threadPool = new ThreadPool(threads_number);
    return threadPool;
}
pthread_t* getIdleThread(struct ThreadPool* threadPool) {
    pthread_mutex_lock(&threadPool->pool_mutex);
    pthread_t* pid = NULL;
    for(int i = 0 ; i < threadPool->threads_number; ++i) {
        if(threadPool->threads[i] == 0) {
            pid = &threadPool->threads[i];
            break;
        }
    }
    pthread_mutex_unlock(&threadPool->pool_mutex);
    return pid;
}
void freeThread(struct ThreadPool* threadPool, pthread_t pid) {
    pthread_mutex_lock(&threadPool->pool_mutex);
    for(int i = 0 ; i < threadPool->threads_number; ++i) {
        if(threadPool->threads[i] == pid) {
#ifdef THREAD_POOL_DEBUG
            printf("free thread %lu\n",pid);
#endif
            threadPool->threads[i] = 0;
        }
    }
    pthread_mutex_unlock(&threadPool->pool_mutex);
}

int dec_counter(uint32_t *counter, pthread_mutex_t *mutex, uint32_t threshold) {
    pthread_mutex_lock(mutex);
    int state = -1;
    if(*counter > threshold) {
        *counter = *counter - 1;
        state = *counter;
    }
    printf("dec , counter %d\n",*counter);
    pthread_mutex_unlock(mutex);
    return state;
}
int inc_counter(uint32_t *counter, pthread_mutex_t *mutex, uint32_t threshold) {
    pthread_mutex_lock(mutex);
    int state = -1;
    if(*counter < threshold) {
        *counter = *counter + 1;
        state = *counter;
    }
    printf("inc , counter %d\n",*counter);
    pthread_mutex_unlock(mutex);
    return state;
}
