#pragma once
#include <stack>
#include <stdint.h>

using Tower = std::stack<uint32_t>;
const uint32_t g_size = 3;

void hanoi(Tower (&t)[g_size], const uint32_t from, uint32_t to);
void make_tower(Tower &t, const uint32_t n);