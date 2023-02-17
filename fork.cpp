#include "fork.h"
#include <iostream>

void ForkResourceManager::lock() {
    m_manager_mutex.lock();
}

void ForkResourceManager::release() {
    m_manager_mutex.unlock();
}

bool ForkResourceManager::try_request() {
    lock();
    
    if(m_state != ForkResourceState::AVAILABLE) {
        release();
        return false;
    }

    m_state = ForkResourceState::REQUESTED;

    release();
    return true;
}

bool ForkResourceManager::try_acquire() {
    lock();

    if(m_state == ForkResourceState::AQUIRED) {
        release();
        return false;
    }

    m_state = ForkResourceState::AQUIRED;
    
    release();
    return true;
}

void ForkResourceManager::free() {
    lock();
    m_state = ForkResourceState::AVAILABLE;
    release();
}