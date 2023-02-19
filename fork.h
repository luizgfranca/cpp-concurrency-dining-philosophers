#include <string>
#include "lock.h"

enum ForkResourceState {
    AVAILABLE,
    REQUESTED,
    AQUIRED
};

class ForkResourceManager {

    Lock m_manager_mutex;
    ForkResourceState m_state = ForkResourceState::AVAILABLE;

    void lock();
    void release();

public:
    ForkResourceState get_current_state();

    bool try_request();
    bool try_acquire();
    void free();

};