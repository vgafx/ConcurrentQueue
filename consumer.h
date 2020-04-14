#pragma once
#include <iostream>
#include <vector>
#include "concurrentqueue.h"

template<typename T>
class Consumer{
private:
    unsigned int m_id; //Thread ID
    unsigned int m_total_items; //How many items to consume in total
    ConcurrentQueue<T>& m_queue;
    unsigned int m_items_consumed; //The 'local' total consumed by ths thread
    unsigned int m_current_total; //The current total consumed by all threads
    std::vector<unsigned int>& m_totals; //Reduction vector for terminating condition
    std::mutex c_mutex;

public:
    Consumer() = delete;

    Consumer(unsigned int id, unsigned int items, ConcurrentQueue<T>& queue, std::vector<unsigned int>& totals);

    void run();

    unsigned int reduceCurrentTotal();

};

#include "consumer.tpp"
