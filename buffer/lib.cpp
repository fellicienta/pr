#include "lib.h"
#include <vector>
#include <stdint.h>

Rolling_buffer::Rolling_buffer(const int size = 0) {
    this->size = size;
    this->queue.resize(size);
}

int Rolling_buffer::get_size() {
    return this->queue.size();
}