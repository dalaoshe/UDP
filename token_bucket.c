//
// Created by dalaoshe on 17-3-24.
//
#include "token_bucket.h"
int getToken(struct Token_Bucket* bucket) {

    if(bucket == NULL)
        return 0;
    pthread_mutex_lock(&bucket->token_bucket_mutex);
    updateToken(bucket);
    if(bucket->tokens > 0) {
        bucket->tokens--;
        pthread_mutex_unlock(&bucket->token_bucket_mutex);
        return 1;
    }
    pthread_mutex_unlock(&bucket->token_bucket_mutex);
    return 0;
}

void updateToken(struct Token_Bucket* bucket) {
    time_t now = time(NULL);
    time_t diff = (now - bucket->last_update_time);
    if(diff > 0) {
        bucket->last_update_time = now;
        bucket->tokens += diff * bucket->token_fill_rate;
        if(bucket->tokens > bucket->capacity)
            bucket->tokens = bucket->capacity;
    }
}
