#pragma once
#include <map>
#include <set>
#include <stdint.h>

using Point = int32_t;
using OverlapPointSet = std::set<Point>;
using LineSegmentSet = std::multimap<Point, Point>;

OverlapPointSet find_max_overlap_point(const LineSegmentSet &set);
