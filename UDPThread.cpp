//
// Created by dalaoshe on 17-3-29.
//
#include "UDPThread.h"
int dec_counter(uint32_t *counter, pthread_mutex_t *mutex, uint32_t threshold) {
    pthread_mutex_lock(mutex);
    int state = -1;
    if(*counter > threshold) {
        *counter = *counter - 1;
        state = *counter;
    }
    printf("dec , thread counter %d\n",*counter);
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
    printf("inc , thread counter %d\n",*counter);
    pthread_mutex_unlock(mutex);
    return state;
}
