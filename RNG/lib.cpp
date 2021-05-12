#include "lib.h"

#include <fstream>
#include <random>

std::random_device rd;
std::mt19937 gen(rd());

Statistic uniform_distribution(const int32_t a, const int32_t b, const uint32_t sample_size)
{
    std::uniform_int_distribution<> distribution(a, b);
    Statistic st;

    for (uint32_t i = 0; i < sample_size; ++i)
        ++st[distribution(gen)];

    return st;
}

Statistic normal_distribution(const int32_t mean, const uint32_t deviation,
                              const uint32_t sample_size)
{
    std::normal_distribution<> distribution{mean, deviation};
    Statistic st;

    for (uint32_t n = 0; n < sample_size; ++n)
        ++st[std::round(distribution(gen))];

    return st;
}

Statistic exponential_distribution(const uint32_t time_unit, const uint32_t sample_size)
{
    std::exponential_distribution<> distribution(time_unit);
    Statistic st;

    for (uint32_t n = 0; n < sample_size; ++n)
        ++st[distribution(gen)];

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
