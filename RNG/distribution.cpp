#include "distribution.h"

#include <fstream>

Statistic Normal_distrib::generate(const uint32_t sample_size)
{
    Statistic st;

    for (uint32_t i = 0; i < sample_size; ++i)
        ++st[std::round(d(gen))];

    return st;
}

Statistic Uniform_int_distrib::generate(const uint32_t sample_size)
{
    Statistic st;

    for (uint32_t i = 0; i < sample_size; ++i)
        ++st[d(gen)];

    return st;
}

Statistic Exponential_distrib::generate(const uint32_t sample_size)
{
    Statistic st;

    for (uint32_t i = 0; i < sample_size; ++i)
        ++st[d(gen)];

    return st;
}

void save_statistic(const std::string &file_name, const Statistic &st)
{
    std::ofstream file;
    file.open(file_name, std::ios::in | std::ios::out | std::ios::trunc);

    file << "VALUE"
         << ","
         << "FREQUENCY" << std::endl;

    for (auto i : st)
        file << i.first << ',' << i.second << std::endl;

    file.close();
}
