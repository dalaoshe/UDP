//
// Created by dalaoshe on 17-3-24.
//

#ifndef UDP_TOKEN_BUCKET_H
#define UDP_TOKEN_BUCKET_H

#include <time.h>
#include <stdint.h>

#define SERVER_OUTPUT_CAPACITY 1<<15
#define CLIENT_INPUT_CAPACITY (SERVER_OUTPUT_CAPACITY >> 10)
#define SERVER_OUTPUT_FILL_RATE 30
#define CLIENT_INPUT_FILL_RATE 1
#define CLIENT_TOKEN_BUCKET_TIMEOUT 60

struct Token_Bucket{
    time_t last_update_time;    //
    __uint16_t token_fill_rate; // n/secondes
    __uint16_t capacity;
    __uint16_t tokens;
};
struct TokenBucketMap;
int getToken(struct Token_Bucket*);
void updateToken(struct Token_Bucket*);
int exist(struct TokenBucketMap *t_map, uint32_t ip);

struct Token_Bucket* getTokenBucket(struct TokenBucketMap* t_map, uint32_t ip);

void addTokenBucket(struct TokenBucketMap* t_map, uint32_t ip) ;

void deleteTokenBucket(struct TokenBucketMap* t_map, uint32_t ip);
void clearTimeOutTokenBucket(struct TokenBucketMap* t_map);
struct TokenBucketMap* initTokenBucket(struct TokenBucketMap* t_map);
#endif //UDP_TOKEN_BUCKET_H
