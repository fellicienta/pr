#pragma once
#include <vector>
#include <stdint.h>

enum STACK_ {
    HEAD,
    TAIL,
};

template <typename T>
class DoubleStack
{
public:
    DoubleStack() 
        : stack(1000), head(0), tail(stack.capacity()) 
        {}    
    bool push(T item, STACK_ st) {
        if (head == tail) 
            return false;

        switch (st) {
            case HEAD:
                stack.at(head++) = item;
                return true;   
            case TAIL: 
                stack.at(--tail) = item;
                return true;   
            default:
                return false;
        }
    }
    T pop(STACK_ st) {
        switch (st) {
            case HEAD: {
                T item = stack.at(--head);
                stack.at(head) = 0;
                return item;
            }
            case TAIL: {
                T item = stack.at(tail);
                stack.at(tail++) = 0;
                return item;
            }
            default:
                return -1;
        }
    }
    uint32_t size(STACK_ st) {
        switch (st) {
            case HEAD: 
                return head;
            case TAIL:
                return stack.capacity() - tail;
            default:
                return -1;
        }
    }
    bool empty(STACK_ st) {
        switch (st) {
            case HEAD: 
                return 0 == size(HEAD);
            case TAIL:
                return 0 == size(TAIL);
        }
    }
    uint32_t capacity() {
        return stack.capacity();
    }
private:
    std::vector<T> stack;
    uint32_t head;
    uint32_t tail; 
};