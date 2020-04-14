cmake_minimum_required(VERSION 2.8)

project(ConcurrentQueue)
set(CMAKE_CXX_FLAGS "-O3 -pthread")
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(SOURCES
    main.cpp
    concurrentqueue.tpp
    consumer.tpp
    producer.tpp)

set(HEADERS
    concurrentqueue.h
    consumer.h
    producer.h)



add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})
