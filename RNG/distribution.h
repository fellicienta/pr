#pragma once

#include <map>
#include <memory>
#include <random>
#include <string>

using Statistic = std::map<int32_t, uint32_t>;

static std::random_device rd;
static std::mt19937 gen(rd());

class Distribution
{
public:
    virtual ~Distribution() = default;
    virtual int32_t generate() = 0;
};

class NormalDistrib : public Distribution
{
public:
    NormalDistrib(const int32_t mean, const uint32_t deviation)
        : d(mean, deviation)
    {
    }
    int32_t generate() override;

private:
    std::normal_distribution<> d;
};

class ExponentialDistrib : public Distribution
{
public:
    ExponentialDistrib(const uint32_t time_unit)
        : d(time_unit)
    {
    }
    int32_t generate() override;

private:
    std::exponential_distribution<> d;
};

class UniformIntDistrib : public Distribution
{
public:
    UniformIntDistrib(const int32_t a, const int32_t b)
        : d(a, b)
    {
    }
    int32_t generate() override;

private:
    std::uniform_int_distribution<> d;
};

Statistic generate_statistic(std::shared_ptr<Distribution> d, const uint32_t sample_size);
void save_statistic(const std::string &file_name, const Statistic &st);
