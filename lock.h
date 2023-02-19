#include <cstddef>
#include <cstdint>
#include <map>
#include <thread>

class Lock {
    
    uint64_t m_next_ticket_number = 1;
    std::map<size_t, bool> m_generating;
    std::map<size_t, uint64_t> m_thread_ticket; 

    size_t get_thread_id();

public:
    void lock();
    void unlock();

};