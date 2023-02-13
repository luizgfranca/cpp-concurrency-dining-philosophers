#include "philosopher.h"
#include <iostream>
#include <chrono>
#include <thread>


void Philosopher::eat() {
    
    while(
        !m_using_fork_counter->at(m_left_fork_index).try_lock() ||
        !m_using_fork_counter->at(m_right_fork_index).try_lock()
    ) {
        std::this_thread::sleep_for(std::chrono::milliseconds(2));
    }

    std::cout << (m_name + " started eating\n");    
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    
    m_using_fork_counter->at(m_left_fork_index).unlock();
    m_using_fork_counter->at(m_right_fork_index).unlock();
    
    std::cout << (m_name + " finished eating\n");
}

void Philosopher::think() {
    std::cout << (m_name + " started thinking\n");
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    std::cout << (m_name + " finished thinking\n");
}