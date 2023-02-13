#include <mutex>
#include <string>
#include <memory>
#include <vector>
#include <atomic>
#include <mutex>

class Philosopher {
    std::shared_ptr< std::vector<std::mutex> > m_using_fork_counter;

    std::string m_name;
    int m_left_fork_index;
    int m_right_fork_index;

public:
    void eat();
    void think();

    std::string name() { return m_name; }
    void set_name(std::string name) { m_name = name; }
        
    void set_fork_resources(
        std::shared_ptr< std::vector<std::mutex> > using_fork_counter,
        int left_fork_index,
        int right_fork_index    
    ) {
        m_using_fork_counter = using_fork_counter;
        m_left_fork_index = left_fork_index;
        m_right_fork_index = right_fork_index;
    }

};