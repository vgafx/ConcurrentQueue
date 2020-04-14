/*** Concurrent Queue
 *  Implements the class functionality declared in the header file.
 *
 ***/
/*Default Ctor, only 1 item allowed in queue*/
template<typename T>
ConcurrentQueue<T>::ConcurrentQueue()
    :m_capacity(1)
{
}

template<typename T>
ConcurrentQueue<T>::ConcurrentQueue(unsigned int in_capacity)
    :m_capacity(in_capacity)
{
}

template<typename T>
void ConcurrentQueue<T>::insertBack(T item)
{
    std::unique_lock<std::mutex> ulock{m_mutex};
    auto f = [this](){return m_concurrent_queue.size() < m_capacity;};
    m_cond_var.wait(ulock,f);

    m_concurrent_queue.push_back(std::move(item));

    m_cond_var.notify_one();
    ulock.unlock();
}

template<typename T>
T ConcurrentQueue<T>::getFront()
{
    std::unique_lock<std::mutex> ulock{m_mutex};
    auto f = [this](){return m_concurrent_queue.size() > 0;};
    m_cond_var.wait(ulock,f);

    T item = m_concurrent_queue.front();
    m_concurrent_queue.pop_front();

    m_cond_var.notify_one();
    ulock.unlock();

    return item;
}

template<typename T>
unsigned int ConcurrentQueue<T>::getCapacity()
{
    return m_capacity;
}

