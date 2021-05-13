#include "distribution.h"

int main()
{
    std::map<std::string, std::shared_ptr<Distribution>> m;
    m.emplace("uniform.csv", std::make_shared<UniformIntDistribution>(1, 100));
    m.emplace("normal.csv", std::make_shared<NormalDistribution>(30, 10));
    m.emplace("exponential.csv", std::make_shared<ExponentialDistribution>(1));

    for (auto x : m)
        save_statistic(x.first, generate_statistic(x.second, 100000));

    return 0;
}