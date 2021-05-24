#pragma once
#include <map>
#include <set>
#include <stdint.h>

using Point = int32_t;
using OverlapPointSet = std::set<Point>;
using LineSegmentSet = std::map<Point, Point>;

OverlapPointSet find_max_overlap_point(LineSegmentSet set);
