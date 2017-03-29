//
// Created by dalaoshe on 17-3-26.
//
#include "token_bucket.h"
#include <map>
#include <cstdio>
struct TokenBucketMap {
    std::map<uint32_t, Token_Bucket*> ip_token_bucket;
    pthread_mutex_t input_token_bucket_map_mutex; // 保护映射表，不保护Bucket，Bucket由各自的mutex保护
    TokenBucketMap() {
        this->input_token_bucket_map_mutex = PTHREAD_MUTEX_INITIALIZER;
    }
};

int exist(TokenBucketMap* t_map, uint32_t ip){
    pthread_mutex_lock(&t_map->input_token_bucket_map_mutex);
    int exist = t_map->ip_token_bucket.count(ip);
    pthread_mutex_unlock(&t_map->input_token_bucket_map_mutex);
    return exist;
}

Token_Bucket* getTokenBucket(TokenBucketMap* t_map, uint32_t ip) {
    pthread_mutex_lock(&t_map->input_token_bucket_map_mutex);
    Token_Bucket* bucket = t_map->ip_token_bucket[ip];
    pthread_mutex_unlock(&t_map->input_token_bucket_map_mutex);
    return bucket;
}

void addTokenBucket(TokenBucketMap* t_map, uint32_t ip) {
    pthread_mutex_lock(&t_map->input_token_bucket_map_mutex);
    Token_Bucket* bucket = new Token_Bucket();
    bucket->capacity = CLIENT_INPUT_CAPACITY;
    bucket->token_fill_rate = CLIENT_INPUT_FILL_RATE;
    bucket->tokens = 0;
    bucket->last_update_time = time(NULL);
    t_map->ip_token_bucket.insert(std::pair<uint32_t ,Token_Bucket*>(ip,bucket));
    pthread_mutex_unlock(&t_map->input_token_bucket_map_mutex);
}

void deleteTokenBucket(TokenBucketMap* t_map, uint32_t ip) {

    std::map<uint32_t, Token_Bucket*>::iterator it;
    it = t_map->ip_token_bucket.find(ip);
    if(it != t_map->ip_token_bucket.end()) {
        delete it->second;
        t_map->ip_token_bucket.erase(it);
    }

}

struct TokenBucketMap* initTokenBucket(struct TokenBucketMap* t_map) {
    t_map = new TokenBucketMap();
    return t_map;
}

void clearTimeOutTokenBucket(struct TokenBucketMap* t_map) {
    pthread_mutex_lock(&t_map->input_token_bucket_map_mutex);
    printf("check clear\n");
    sleep(2);
    std::map<uint32_t, Token_Bucket*>::iterator it;
    for(it = t_map->ip_token_bucket.begin(); it != t_map->ip_token_bucket.end(); ++it) {
        Token_Bucket* bucket = it->second;
        time_t now = time(NULL);
        if(now - bucket->last_update_time > CLIENT_TOKEN_BUCKET_TIMEOUT) {
                printf("ip: %u timeout delete\n",it->first);
                deleteTokenBucket(t_map,it->first);
        }
    }
    printf("check ok\n");
    pthread_mutex_unlock(&t_map->input_token_bucket_map_mutex);
}
