#include "distribution.h"

#include <memory>

int main()
{
    std::map<std::string, std::shared_ptr<Distribution>> m;
    m.emplace("uniform.csv", std::make_shared<Uniform_int_distrib>(1, 100));
    m.emplace("normal.csv", std::make_shared<Normal_distrib>(30, 10));
    m.emplace("exponential.csv", std::make_shared<Exponential_distrib>(1));

    for (auto x : m)
        save_statistic(x.first, x.second->generate(100000));

    return 0;
}