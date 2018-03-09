#pragma once
#include "Queue.h"

class Consumer{
public:
    Consumer(Queue & q) : m_q(q), m_takeCounter(0), m_isRunning(true)
    { }

    ~Consumer(){
        std::cout << "KILL CONSUMER! - TOOK: " << m_takeCounter << "." << std::endl;
    }

    void consume(){
        while (m_isRunning){
            try{
                m_q.pop();
                m_takeCounter++;
            }
            catch (std::exception e){
                std::cout << "Program was stopped while waiting." << std::endl;
            }
        }
    }

    void execute(){
        m_t = std::thread(&Consumer::consume, this);
    }

    void join(){
        m_t.join();
    }

    void stop(){
        m_isRunning = false;
    }

private:
    Queue& m_q;
    std::thread m_t;

    unsigned int m_takeCounter;
    bool m_isRunning;
};