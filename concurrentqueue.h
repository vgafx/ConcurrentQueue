#pragma once

#include <mutex>
#include <condition_variable>
#include <deque>

template<typename T>
class ConcurrentQueue{
private:
    std::deque<T> m_concurrent_queue;
    unsigned int m_capacity;

    std::mutex m_mutex;
    std::condition_variable m_cond_var;

public:
    ConcurrentQueue();
    ConcurrentQueue(unsigned int in_capacity);

    ConcurrentQueue(const ConcurrentQueue&) = delete;
    ConcurrentQueue& operator=(const ConcurrentQueue&) = delete;

    void insertBack(T item);

    T getFront();

    unsigned int getCapacity();
};

#include "concurrentqueue.tpp"
