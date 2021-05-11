#pragma once
#include <map>
#include <stdint.h>
#include <string>

using Statistic = std::map<int32_t, uint32_t>;

Statistic uniform_distribution(const int32_t a, const int32_t b, const uint32_t sample_size);
Statistic normal_distribution(const int32_t mean, const uint32_t deviation,
                              const uint32_t sample_size);
Statistic exponential_distribution(const uint32_t time_unit, const uint32_t sample_size);
void save_statistic(const std::string &file_name, const Statistic &st);
