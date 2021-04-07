#pragma once
#include <vector>
#include <stdint.h>

template <typename T>
class DoubleStack
{
public:
    DoubleStack() {
        stack.resize(1000);
        head = 0;
        tail = stack.capacity();
    }
    void push(T item, char st) {
        if ('h' == st && head != tail) {
            stack.at(head++) = item;
        }
        else if ('t' == st && head != tail) {
            stack.at(--tail) = item;
        }
    }
    uint32_t hs_size() {
        return head;
    }
    uint32_t ts_size() {
        return stack.capacity() - tail;
    }
    bool hs_empty() {
        return 0 == hs_size() ?  true : false;
    }
    bool ts_empty() {
        return 0 == ts_size() ?  true :  false;
    }
    uint32_t capacity() {
        return stack.capacity();
    }
    typename std::vector<T>::iterator hbegin() {
        return stack.begin();
    }
    typename std::vector<T>::iterator hend() {
        return stack.begin() + head;
    }
    typename std::vector<T>::iterator tbegin() {
        return stack.begin() + tail;
    }
    typename std::vector<T>::iterator tend() {
        return stack.end();
    }
private:
    std::vector<T> stack;
    uint32_t head;
    uint32_t tail; 
};