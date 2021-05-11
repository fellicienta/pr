#include "lib.h"

int main()
{
    save_statistic("uniform.csv", uniform_distribution(1, 500, 10000));
    save_statistic("normal.csv", normal_distribution(50, 10, 10000));
    save_statistic("exponential.csv", exponential_distribution(1, 10000));

    return 0;
}