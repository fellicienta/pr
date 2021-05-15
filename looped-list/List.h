#pragma once
#include <stddef.h>

struct List
{
    size_t element = 0;
    List *p_next = nullptr;
};

List *generate_list(const size_t n);
size_t get_survivor(List *&list, const size_t step);
size_t formula(const size_t n, const size_t k);