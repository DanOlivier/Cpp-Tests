#pragma once
#include "Queue.h"

class Producer{
public:
    Producer(Queue & q) : m_q(q), m_counter(1) { }

    void produce(){
        for (int i = 0; i < 5; i++){
            m_q.push(m_counter++);
            std::this_thread::sleep_for(std::chrono::milliseconds{ 500 });
        }
    }

    void execute(){
        m_t = std::thread(&Producer::produce, this);
    }

    void join(){
        m_t.join();
    }

private:
    Queue & m_q;
    std::thread m_t;

    unsigned int m_counter;
};