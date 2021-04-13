#pragma once
#include <stddef.h>

struct List
{
    size_t element = 0;
    List *p_next = nullptr;
};

List *generate_list(size_t n);
size_t get_survivor(List *&list, size_t step);
size_t formula(size_t n, size_t k);