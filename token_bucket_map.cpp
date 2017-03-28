//
// Created by dalaoshe on 17-3-26.
//
#include "token_bucket.h"
#include <map>
#include <cstdio>
struct TokenBucketMap {
    std::map<uint32_t, Token_Bucket*> ip_token_bucket;
};

int exist(TokenBucketMap* t_map, uint32_t ip){
    return t_map->ip_token_bucket.count(ip);
}

Token_Bucket* getTokenBucket(TokenBucketMap* t_map, uint32_t ip) {
    return t_map->ip_token_bucket[ip];
}

void addTokenBucket(TokenBucketMap* t_map, uint32_t ip) {
    Token_Bucket* bucket = new Token_Bucket();

    bucket->capacity = CLIENT_INPUT_CAPACITY;
    bucket->token_fill_rate = CLIENT_INPUT_FILL_RATE;
    bucket->tokens = 0;
    bucket->last_update_time = time(NULL);

    t_map->ip_token_bucket.insert(std::pair<uint32_t ,Token_Bucket*>(ip,bucket));
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
    std::map<uint32_t, Token_Bucket*>::iterator it;
    for(it = t_map->ip_token_bucket.begin(); it != t_map->ip_token_bucket.end(); ++it) {
        Token_Bucket* bucket = it->second;
        time_t now = time(NULL);
        if(now - bucket->last_update_time > CLIENT_TOKEN_BUCKET_TIMEOUT) {
                printf("ip: %u timeout delete\n",it->first);
                deleteTokenBucket(t_map,it->first);
        }
    }
}
