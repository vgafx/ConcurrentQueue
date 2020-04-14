#include <iostream>
#include <thread>
#include <memory>

#include "concurrentqueue.h"
#include "consumer.h"
#include "producer.h"

int main()
{
    constexpr unsigned int Q_SIZE = 10;
    constexpr unsigned int NUM_THREADS = 6;
    constexpr unsigned int NUM_ITEMS = 100;

    /*Keep the running totals*/
    std::vector<unsigned int> p_items(NUM_THREADS);
    std::vector<unsigned int> c_items(NUM_THREADS);

    ConcurrentQueue<int> c_queue(Q_SIZE);
    std::cout << "Created Concurrent FIFO queue with capacity:" << c_queue.getCapacity() <<"\n";

    /*Store the threads*/
    std::vector<std::thread> p_threads;
    std::vector<std::thread> c_threads;

    p_threads.reserve(NUM_THREADS);
    c_threads.reserve(NUM_THREADS);

    /*Store the producer / consumer objects*/
    std::vector<std::unique_ptr<Producer<int>>> producers;
    std::vector<std::unique_ptr<Consumer<int>>> consumers;

    producers.reserve(NUM_THREADS);
    consumers.reserve(NUM_THREADS);

    /*Instanciate the objects*/
    for (unsigned int i = 0; i < NUM_THREADS; i++) {
        producers.emplace_back(std::make_unique<Producer<int>>(i, NUM_ITEMS, c_queue, p_items));

        consumers.emplace_back(std::make_unique<Consumer<int>>(i, NUM_ITEMS, c_queue, c_items));
    }

    std::cout << "Launching threads...\n";
    /*Start executing*/
    for (size_t i = 0; i < NUM_THREADS; i++) {
        p_threads.emplace_back(&Producer<int>::run, std::move(producers[i]));
        c_threads.emplace_back(&Consumer<int>::run, std::move(consumers[i]));
    }

    std::cout << "Waiting threads...\n";
    /*Join*/
    for (auto& thr : p_threads) {
        thr.join();
    }

    for (auto& thr : c_threads) {
        thr.join();
    }


    return 0;
}
