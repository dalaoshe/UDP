cmake_minimum_required(VERSION 3.6)
project(UDP)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.c recvfrom_flags.c recvfrom_flags.h unp.h unprtt.h dg_send_recv.c rtt.c do_client.h do_client.c error_check.c do_server.c do_server.h token_bucket.h token_bucket.c token_bucket_map.cpp)
add_executable(UDP ${SOURCE_FILES})