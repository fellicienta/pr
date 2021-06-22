#include "lib.h"

#include <math.h>

double g_max = std::numeric_limits<double>::max();

double calculate_distance(const Point p1, const Point p2)
{
    return sqrt(pow((p2.first - p1.first), 2) + pow((p2.second - p1.second), 2));
}

double distance(Set G, Set B)
{
    double total_sum = 0;

    while (!G.empty())
    {
        uint32_t item_index_g = 0;
        uint32_t item_index_b = 0;
        double min_distance = g_max;
        uint32_t current_index_g = 0;

        for (auto g : G)
        {
            uint32_t current_index_b = 0;

            for (auto b : B)
            {
                double current_distance = calculate_distance(g, b);
                if (current_distance < min_distance)
                {
                    min_distance = current_distance;
                    item_index_b = current_index_b;
                    item_index_g = current_index_g;
                }
                ++current_index_b;
            }
            ++current_index_g;
        }
        B.erase(B.begin() + item_index_b);
        G.erase(G.begin() + item_index_g);
        total_sum += min_distance;
    }
    return total_sum;
}