#include "distribution.h"

int main()
{
    std::map<std::string, std::shared_ptr<Distribution>> m;
    m.emplace("uniform.csv", std::make_shared<UniformIntDistrib>(1, 100));
    m.emplace("normal.csv", std::make_shared<NormalDistrib>(30, 10));
    m.emplace("exponential.csv", std::make_shared<ExponentialDistrib>(1));

    for (auto x : m)
        save_statistic(x.first, generate_statistic(x.second, 100000));

    return 0;
}