#include "fork.h"

#include <mutex>
#include <string>
#include <memory>
#include <vector>
#include <atomic>
#include <mutex>

class Philosopher {
    std::shared_ptr< std::vector<ForkResourceManager> > m_fork_resources;

    std::string m_name;
    int m_left_fork_index;
    int m_right_fork_index;

    void acquire_forks();
    void free_forks();

public:
    void eat();
    void think();
    void dine();

    std::string name() { return m_name; }
    void set_name(std::string name) { m_name = name; }
        
    void set_fork_resources(
        std::shared_ptr< std::vector<ForkResourceManager> > fork_resources,
        int left_fork_index,
        int right_fork_index    
    ) {
        m_fork_resources = fork_resources;
        m_left_fork_index = left_fork_index;
        m_right_fork_index = right_fork_index;
    }

};