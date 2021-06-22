#include "lib.h"

#include <math.h>

double g_max = std::numeric_limits<double>::max();

double find_distance(const Point &p1, const Point &p2)
{
    return sqrt(pow((p2.first - p1.first), 2) + pow((p2.second - p1.second), 2));
}

double distance(const Set &G, Set B)
{
    double total_sum = 0;
    uint32_t item_index = 0;

    for (auto g : G)
    {
        double min_distance = g_max;
        uint32_t current_index = 0;

        for (auto b : B)
        {
            double current_distance = find_distance(g, b);
            if (current_distance < min_distance)
            {
                min_distance = current_distance;
                item_index = current_index;
            }
            ++current_index;
        }
        total_sum += min_distance;
        B.erase(B.begin() + item_index);
    }
    return total_sum;
}