#include "philosopher.h"

#include <algorithm>
#include <chrono>
#include <iostream>
#include <string>
#include <utility>
#include <vector>
#include <memory>
#include <thread>

constexpr int NUMBER_OF_PHILOSOPHERS = 5;

void monitor_fork_usage(std::shared_ptr< std::vector<int> > using_fork_counter) {
    while(true) {
        std::this_thread::sleep_for(std::chrono::milliseconds(250));
        std::string monitor_message("");
        
        monitor_message.append("\nMONITOR\n-----------------------------------------------\n");    
        for(int i = 0; i < using_fork_counter->size(); i ++) {
            monitor_message.append("[" + std::to_string(i) + "] -> " + std::to_string(using_fork_counter->at(i)) + "\n" );
        }
        monitor_message.append("\n");

        std::cout << monitor_message;
    }
}

void dine(std::shared_ptr<Philosopher> philosopher) {
    while (true) {
        philosopher->eat();
        philosopher->think();
    }
}

int main() {
    auto using_fork_counter = std::make_shared< std::vector<int> >(NUMBER_OF_PHILOSOPHERS);
    auto philosophers = std::make_unique< std::vector<Philosopher> >(NUMBER_OF_PHILOSOPHERS);
    std::vector<std::thread> threads(NUMBER_OF_PHILOSOPHERS);


    for(int i = 0; i < philosophers->size(); i ++) {
        const int left_fork_pos = i == 0 ? NUMBER_OF_PHILOSOPHERS - 1 : i - 1;
        const int right_fork_pos = i == NUMBER_OF_PHILOSOPHERS ? 0 : i;

        philosophers->at(i).set_name(std::to_string(i));
        philosophers->at(i).set_fork_resources(using_fork_counter, left_fork_pos, right_fork_pos);
    }

    for(auto x : *using_fork_counter) { x = 0; }

    for(auto philosopher : *philosophers) {
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        std::cout << "creating thread for " + philosopher.name() << "\n";

        std::thread th(dine, std::make_shared<Philosopher>(philosopher));
        threads.push_back(std::move(th));
    }

    std::thread monitor_thread(monitor_fork_usage, using_fork_counter);

    for(std::thread& th : threads) {
        if(th.joinable()) {
            th.join();
        }
    }

    if(monitor_thread.joinable()) {
        monitor_thread.join();
    }
    
    return 0;
}