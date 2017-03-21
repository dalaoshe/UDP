cmake_minimum_required(VERSION 3.6)
project(UDP)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.c recvfrom_flags.c recvfrom_flags.h unp.h unprtt.h dg_send_recv.c rtt.c)
add_executable(UDP ${SOURCE_FILES})