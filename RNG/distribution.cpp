#include "distribution.h"

#include <fstream>

int32_t NormalDistrib::generate()
{
    return std::round(d(gen));
}

int32_t UniformIntDistrib::generate()
{
    return d(gen);
}

int32_t ExponentialDistrib::generate()
{
    return d(gen);
}

Statistic generate_statistic(std::shared_ptr<Distribution> d, const uint32_t sample_size)
{
    Statistic st;

    for (uint32_t i = 0; i < sample_size; ++i)
        ++st[d->generate()];

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
