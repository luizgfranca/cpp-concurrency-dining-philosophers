#include "philosopher.h"
#include <iostream>
#include <chrono>
#include <thread>

void Philosopher::acquire_forks() {
    bool is_left_fork_requested = false;
    bool is_right_fork_requested = false;

    bool is_left_fork_acquired = false;
    bool is_right_fork_acquired = false;

    while(!is_left_fork_acquired || !is_right_fork_acquired) {
        if (!is_left_fork_requested && !is_right_fork_requested) {
            is_left_fork_requested = m_fork_resources->at(m_left_fork_index).try_request();
            is_right_fork_requested = m_fork_resources->at(m_right_fork_index).try_request();
            continue;
        }

        if (is_left_fork_requested && !is_right_fork_acquired) {
            is_right_fork_acquired = m_fork_resources->at(m_right_fork_index).try_acquire();
            continue;
        }

        if (is_right_fork_requested && !is_left_fork_acquired) {
            is_left_fork_acquired = m_fork_resources->at(m_left_fork_index).try_acquire();
            continue;
        }

        if (is_left_fork_requested && is_right_fork_acquired) {
            is_left_fork_acquired = m_fork_resources->at(m_left_fork_index).try_acquire();
            continue;
        }

        if (is_right_fork_requested && is_left_fork_acquired) {
            is_right_fork_acquired = m_fork_resources->at(m_right_fork_index).try_acquire();
            continue;
        }

    }
}

void Philosopher::free_forks() {
    m_fork_resources->at(m_left_fork_index).free();
    m_fork_resources->at(m_right_fork_index).free();
}

void Philosopher::eat() {
    bool is_left_fork_requested = false;
    bool is_right_fork_requested = false;

    acquire_forks();

    std::cout << (m_name + " started eating\n");    
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
    std::cout << (m_name + " finished eating\n");

    free_forks();
}

void Philosopher::think() {
    std::cout << (m_name + " started thinking\n");
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
    std::cout << (m_name + " finished thinking\n");
}

void Philosopher::dine() {
    while (true) {
        eat();
        think();
    }
}