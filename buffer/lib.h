#pragma once
#include <vector>
#include <stdint.h>

template <typename T>
class Rolling_buffer 
{
public:
    Rolling_buffer();
    Rolling_buffer(const int size);
    int get_size();
private:
    std::vector<T> queue;
    int size;
};