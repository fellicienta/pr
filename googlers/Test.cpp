#include "lib.h"

#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <random>

void generate_set(Set &s, const uint32_t amount, const int32_t min_value, const int32_t max_value)
{
    std::random_device rd;
    std::mt19937 g(rd());
    s.resize(amount);

    for (uint16_t i = 0; i < amount; ++i)
    {
        s[i].first = min_value + rd() % max_value;
        s[i].second = min_value + rd() % max_value;
    }
}

double random_sampling(const Set &G, const Set &B)
{
    std::random_device rd;
    std::mt19937 g(rd());
    double min_sum = std::numeric_limits<double>::max();
    uint32_t n = G.size() * B.size();

    for (uint32_t i = 0; i < n; ++i)
    {
        Set googlers(G);
        Set bicycles(B);
        double current_sum = 0;

        while (googlers.size() != 0)
        {
            uint32_t index_g = rd() % googlers.size();
            uint32_t index_b = rd() % bicycles.size();
            current_sum += find_distance(googlers[index_g], bicycles[index_b]);
            googlers.erase(googlers.begin() + index_g);
            bicycles.erase(bicycles.begin() + index_b);
        }

        if (current_sum < min_sum)
            min_sum = current_sum;
    }
    return min_sum;
}

TEST(Googlers, distance_check)
{
    Point p1 = {1, 5};
    Point p2 = {1, 7};

    EXPECT_EQ(find_distance(p1, p2), 2);
}

TEST(Googlers, manual_input)
{
    Set G = {{1, 5}, {3, 4}, {5, 3}};
    Set B = {{1, 7}, {3, 6}, {5, 5}, {10, 2}};

    EXPECT_EQ(distance(G, B), 6);
}

TEST(Googlers, random_sampling)
{
    Set G = {{1, 5}, {3, 4}, {5, 3}};
    Set B = {{1, 7}, {3, 6}, {5, 5}, {10, 2}};

    EXPECT_LE(distance(G, B), random_sampling(G, B));
}

TEST(Googlers, random_input)
{
    Set G;
    Set B;
    generate_set(G, 10, 0, 20);
    generate_set(B, 15, 0, 20);

    EXPECT_LT(distance(G, B), random_sampling(G, B));
}
