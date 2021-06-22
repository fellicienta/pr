#pragma once
#include <map>
#include <stdint.h>
#include <vector>

using Point = std::pair<int32_t, int32_t>;
using Set = std::vector<Point>;

double distance(Set G, Set B);
double calculate_distance(const Point p1, const Point p2);
