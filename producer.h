#pragma once
#include <iostream>
#include <vector>
#include <random>
#include "concurrentqueue.h"

template<typename T>
class Producer{
private:
    unsigned int m_id; //Thread ID
    unsigned int m_total_items; //How many items to produce in total
    ConcurrentQueue<T>& m_queue; //The concurrent queue
    unsigned int m_items_produced; //The 'local' total produced by ths thread
    unsigned int m_current_total; //The current total produced by all threads
    std::vector<unsigned int>& m_totals; //Reduction vector for terminating condition
    std::mutex p_mutex;
    std::random_device m_rd;


public:
    Producer() = delete;

    Producer(unsigned int id, unsigned int items, ConcurrentQueue<T>& queue, std::vector<unsigned int>& totals);

    void run();

    unsigned int reduceCurrentTotal();
};

#include "producer.tpp"
