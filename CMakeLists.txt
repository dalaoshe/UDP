cmake_minimum_required(VERSION 3.6)
project(UDP)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp recvfrom_flags.cpp recvfrom_flags.h unp.h unprtt.h client_send_recv.cpp rtt.cpp do_client.h do_client.cpp error_check.cpp do_server.cpp do_server.h token_bucket.h token_bucket.cpp token_bucket_map.cpp UDPThread.cpp UDPThread.h)
add_executable(UDP ${SOURCE_FILES})