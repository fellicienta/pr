#pragma once

#include <map>
#include <random>
#include <string>

using Statistic = std::map<int32_t, uint32_t>;

static std::random_device rd;
static std::mt19937 gen(rd());

class Distribution
{
public:
    virtual ~Distribution() = default;
    virtual Statistic generate(const uint32_t sample_size) = 0;
};

class Normal_distrib : public Distribution
{
public:
    Normal_distrib(const int32_t mean, const uint32_t deviation)
        : d(mean, deviation)
    {
    }
    Statistic generate(const uint32_t sample_size) override;

private:
    std::normal_distribution<> d;
};

class Exponential_distrib : public Distribution
{
public:
    Exponential_distrib(const uint32_t time_unit)
        : d(time_unit)
    {
    }
    Statistic generate(const uint32_t sample_size) override;

private:
    std::exponential_distribution<> d;
};

class Uniform_int_distrib : public Distribution
{
public:
    Uniform_int_distrib(const int32_t a, const int32_t b)
        : d(a, b)
    {
    }
    Statistic generate(const uint32_t sample_size) override;

private:
    std::uniform_int_distribution<> d;
};

void save_statistic(const std::string &file_name, const Statistic &st);
