//
// Created by dalaoshe on 17-3-29.
//
#include "UDPThread.h"
#include <map>
struct ThreadPool{
    std::map<int, pthread_t>threads_map;
    pthread_t *threads;
    uint32_t threads_number;
    pthread_mutex_t pool_mutex;
    ThreadPool(uint32_t threads_number) {
        threads = new pthread_t[threads_number];
        this->threads_number = threads_number;
        memset(threads, 0, sizeof(pthread_t)*threads_number);
//        for(int i = 0 ; i < threads_number; ++i) {
//            threads[i] = i+1;
//            printf("insert tid %lu\n",threads[i]);
//            threads_map.insert(std::pair<int,>(threads[i],0));
//        }
        pool_mutex = PTHREAD_MUTEX_INITIALIZER;
    }
};
struct ThreadPool* initThreadPool(struct ThreadPool* threadPool, int threads_number) {
    threadPool = new ThreadPool(threads_number);
    return threadPool;
}
pthread_t* getIdleThread(struct ThreadPool* threadPool) {
    pthread_mutex_lock(&threadPool->pool_mutex);
    pthread_t* pid = NULL;
//    std::map<pthread_t, int>::iterator it;
//    it = threadPool->threads_map.begin();
//    for( it ;it != threadPool->threads_map.end(); ++it) {
//        if(it->second == 0) {
//            pid = it->first;
//            threadPool->threads_map[it->first] = 1;
//            printf("getidle thread %lu\n",pid);
//            break;
//        }
//    }
    for(int i = 0 ; i < threadPool->threads_number; ++i) {
        if(threadPool->threads[i] == 0) {
            printf("getidle thread %lu\n",i);
            pid = &threadPool->threads[i];
            break;
        }
    }
    pthread_mutex_unlock(&threadPool->pool_mutex);
    return pid;
}
void freeThread(struct ThreadPool* threadPool, pthread_t pid) {
    pthread_mutex_lock(&threadPool->pool_mutex);
//    if(threadPool->threads_map.count(pid) != 0) {
//        threadPool->threads_map[pid] = 0;
//        printf("free thread %lu\n",pid);
//    }
    printf("try to free tid %lu",pid);
    for(int i = 0 ; i < threadPool->threads_number; ++i) {
        if(threadPool->threads[i] == pid) {
            printf("free thread %lu\n",pid);
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
