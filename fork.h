#include <mutex>
#include <string>

enum ForkResourceState {
    AVAILABLE,
    REQUESTED,
    AQUIRED
};

class ForkResourceManager {

    std::mutex m_manager_mutex;
    ForkResourceState m_state = ForkResourceState::AVAILABLE;

    void lock();
    void release();

public:
    ForkResourceState get_current_state();

    bool try_request();
    bool try_acquire();
    void free();

};