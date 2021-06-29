#include "lib.h"

#include <math.h>

namespace
{
void move_disk(Tower (&t)[g_size], const uint32_t from, const uint32_t to)
{
    if (t[from].empty())
    {
        t[from].push(t[to].top());
        t[to].pop();
    }
    else if (t[to].empty())
    {
        t[to].push(t[from].top());
        t[from].pop();
    }
    else if (t[from].top() > t[to].top())
    {
        t[from].push(t[to].top());
        t[to].pop();
    }
    else
    {
        t[to].push(t[from].top());
        t[from].pop();
    }
}

uint32_t calculate_auxiliary_pole(const uint32_t from, const uint32_t to)
{
    uint32_t a = 0;
    for (uint32_t i = 0; i < g_size; ++i)
        a += i;
    return a - from - to;
}
} // namespace

void hanoi(Tower (&t)[g_size], const uint32_t from, uint32_t to)
{
    const uint32_t n = t[from].size();
    const uint32_t total_moves = pow(2, n) - 1;
    uint32_t tmp = calculate_auxiliary_pole(from, to);

    if (n % 2 == 1)
        std::swap(tmp, to);

    for (uint32_t j = 1; j <= total_moves; ++j)
    {
        if (j % 3 == 1)
            move_disk(t, from, tmp);
        else if (j % 3 == 2)
            move_disk(t, from, to);
        else if (j % 3 == 0)
            move_disk(t, tmp, to);
    }
}

void make_tower(Tower &t, const uint32_t n)
{
    for (uint32_t i = n; i >= 1; --i)
        t.push(i);
}