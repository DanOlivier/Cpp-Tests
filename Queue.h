#pragma once
#include <queue>
#include <mutex>
#include <condition_variable>
#include <exception>
#include <iostream>
#include <thread>

class Queue{
public:
    Queue() : m_isProgramStopped(false) { }

    void push(int i){
        std::unique_lock<std::mutex> lock(m_mtx);
        m_q.push(i);
        m_cond.notify_one();
    }

    int pop(){
        std::unique_lock<std::mutex> lock(m_mtx);
        m_cond.wait(lock, [&](){ return !m_q.empty() || m_isProgramStopped; });

        if (m_isProgramStopped){
            throw std::runtime_error("Program stopped!");
        }

        int x = m_q.front();
        m_q.pop();

        std::cout << "Thread " << std::this_thread::get_id() << " popped " << x << "." << std::endl;
        return x;
    }

    void stop(){
        m_isProgramStopped = true;
        m_cond.notify_all();
    }

private:
    std::queue<int> m_q;
    std::mutex m_mtx;
    std::condition_variable m_cond;
    bool m_isProgramStopped;
};