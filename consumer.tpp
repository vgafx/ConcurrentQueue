/*Implementations of the consumer class methods*/
template<typename T>
Consumer<T>::Consumer(unsigned int id, unsigned int items, ConcurrentQueue<T>& queue, std::vector<unsigned int>& totals)
    : m_id(id), m_total_items(items), m_queue(queue), m_items_consumed(0), m_current_total(0), m_totals(totals)
{
}

template<typename T>
void Consumer<T>::run()
{
    while(m_current_total < m_total_items){
        T item = m_queue.getFront();
        std::lock_guard<std::mutex> t_lock {c_mutex};
        m_items_consumed++;
        m_totals[m_id] = m_items_consumed;
        m_current_total = reduceCurrentTotal();
        std::cout << "Consumer Thread with id: " << m_id << " consumed item: " << item << "\n";
        std::cout << "\n";
    }
}

template<typename T>
unsigned int Consumer<T>::reduceCurrentTotal()
{
    unsigned int count = 0;
    for (int i = 0; i < m_totals.size(); ++i) {
        count += m_totals[i];
    }
    return count;
}

