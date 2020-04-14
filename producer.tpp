/*Implementations of the producer class methods*/
template<typename T>
Producer<T>::Producer(unsigned int id, unsigned int items, ConcurrentQueue<T>& queue, std::vector<unsigned int>& totals)
    : m_id(id), m_total_items(items), m_queue(queue), m_items_produced(0), m_current_total(0), m_totals(totals)
{
}

template<typename T>
void Producer<T>::run()
{
    while(m_current_total < m_total_items){
        std::mt19937 rng(m_rd());
        std::uniform_int_distribution<int> uni(1,1000);
        T value = static_cast<T>(uni(rng));
        m_queue.insertBack(value);
        std::lock_guard<std::mutex> t_lock {p_mutex};
        m_items_produced++;
        m_totals[m_id] = m_items_produced;
        m_current_total = reduceCurrentTotal();
        std::cout << "Producer Thread with id: " << m_id << " produced item: " << value << "\n";
        std::cout << "\n";
    }
}

template<typename T>
unsigned int Producer<T>::reduceCurrentTotal()
{
    unsigned int count = 0;
    for (int i = 0; i < m_totals.size(); ++i) {
        count += m_totals[i];
    }
    return count;
}
