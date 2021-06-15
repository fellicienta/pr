#pragma once
#include <stdint.h>
#include <vector>

using ItemType = uint32_t;
using Set = std::vector<ItemType>;

std::vector<Set> linear_partition(const Set &set, const uint32_t k);
