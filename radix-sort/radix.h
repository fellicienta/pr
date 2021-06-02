#pragma once
#include <stdint.h>
#include <vector>

using ItemType = uint32_t;

void generate_numbers(std::vector<ItemType> &v, const uint32_t amount, const uint32_t a,
                      const uint32_t b);
void radix_sort(std::vector<ItemType> &v);