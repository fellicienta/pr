#include "radix.h"

#include <algorithm>
#include <random>
#include <set>
#include <string>

void generate_numbers(std::vector<ItemType> &v, uint32_t n)
{
    static std::random_device rd;
    static std::mt19937 g(rd());

    for (uint16_t i = 0; i < n; ++i)
        v.push_back(rd() % std::numeric_limits<ItemType>::max());
}

void radix_sort(std::vector<ItemType> &v)
{
    uint32_t digits = find_digits_amount(*std::max_element(v.begin(), v.end()));
    std::vector<std::string> s;

    for (uint32_t i = 0; i < v.size(); ++i)
    {
        s.push_back(std::to_string(v[i]));
        s.at(i).assign("0", 0, digits - s[i].size());
    }

    for (int32_t j = digits - 1; j >= 0; --j)
    {
        for (uint32_t step = 0; step < s.size(); ++step)
        {
            for (uint32_t i = 1; i < s.size(); ++i)
                if (s[i - 1][j] > s[i][j])
                    std::swap(s[i - 1], s[i]);
        }
    }
    v.clear();
    for (uint32_t i = 0; i < s.size(); ++i)
    {
        v.push_back(std::stoi(s[i]));
    }
}

void counting_sort(std::vector<ItemType> &v)
{
}

uint32_t find_digits_amount(ItemType x)
{
    uint32_t d = 1000000000;
    for (uint32_t i = 10; i >= 1; --i)
    {
        if (x / d != 0)
            return i;
        d /= 10;
    }
    return 0;
}