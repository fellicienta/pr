#pragma once
#include <vector>
#include <stdint.h>
#include <iterator>

template <typename T>
class Rolling_buffer 
{
public:
    Rolling_buffer(const uint32_t size = 10) {
        queue.resize(size);
        queue.clear();
    }
    uint32_t size() {
         return queue.size();
    }
    uint32_t capacity() {
        return queue.capacity();
    }
    void push(T item) {
        if (queue.size() < queue.capacity()) {
            queue.push_back(item);
        }
        else {
            queue.erase(queue.begin(), queue.begin() + queue.capacity() / 2);
            queue.push_back(item);
        }
    }
    typename std::vector<T>::iterator begin() {
        return queue.begin();
    }
    typename std::vector<T>::iterator end() {
        return queue.end();
    }

    T & operator[](uint32_t index) {
        return queue.at(index);
    }
    bool empty() {
        return queue.empty();
    } 
private:
    std::vector<T> queue;

    T pop() {
        if (queue.empty())
        return -1;

        T item = queue.front();
        queue.erase(queue.begin());

        return item;
    }
};