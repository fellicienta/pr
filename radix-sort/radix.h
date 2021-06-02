#pragma once
#include <stdint.h>
#include <vector>

using ItemType = int32_t;

void generate_numbers(std::vector<ItemType> &v, uint32_t n);
uint32_t find_digits_amount(ItemType x);
void radix_sort(std::vector<ItemType> &v);