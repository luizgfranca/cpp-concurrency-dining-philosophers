#include <string>
#include <memory>
#include <vector>

class Philosopher {
    std::shared_ptr< std::vector<int> > m_using_fork_counter;

    std::string m_name;
    int m_left_fork_index;
    int m_right_fork_index;

public:
    void eat();
    void think();

    std::string name() { return m_name; }
    void set_name(std::string name) { m_name = name; }
        
    void set_fork_resources(
        std::shared_ptr< std::vector<int> > using_fork_counter,
        int left_fork_index,
        int right_fork_index    
    ) {
        m_using_fork_counter = using_fork_counter;
        m_left_fork_index = left_fork_index;
        m_right_fork_index = right_fork_index;
    }

};