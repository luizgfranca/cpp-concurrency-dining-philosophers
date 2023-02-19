#include "lock.h"
#include <cstddef>
#include <functional>
#include <iostream>
#include <string>
#include <thread>

size_t Lock::get_thread_id() {
    return std::hash<std::thread::id>{}(std::this_thread::get_id());
}

void Lock::lock() {
    const auto this_thread_id = get_thread_id();

    m_generating[this_thread_id] = true;
    m_thread_ticket[this_thread_id] = ++m_next_ticket_number;
    m_generating[this_thread_id] = false;

    const auto this_thread_ticket = m_thread_ticket[this_thread_id];

    for (auto it = m_generating.begin(); it != m_generating.end(); it++) {
        auto iterator_thread_ticket = m_thread_ticket[it->first];
        auto iterator_thread_id = it->first;
        
        while (it->second)
            continue;

        while (
            (
                (iterator_thread_ticket < this_thread_ticket) ||
                (iterator_thread_ticket == this_thread_ticket && 
                    iterator_thread_id < this_thread_id)
            ) 
            && iterator_thread_ticket != 0
        )
            continue;
    }
}

void Lock::unlock() { m_thread_ticket[get_thread_id()] = 0; }