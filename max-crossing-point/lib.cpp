#include "lib.h"

#include <algorithm>
#include <iostream>
#include <iterator>

using Frequencies = std::map<Point, uint32_t>;
using Frequency = Frequencies::const_iterator;

namespace
{
Frequencies get_overlap_frequency(const LineSegmentSet &set, const Point begin, const Point end)
{
    Frequencies f;

    for (Point i = begin; i <= end; ++i)
    {
        for (auto segment : set)
        {
            if (i >= segment.first && i <= segment.second)
                ++f[i];
        }
    }
    return f;
}
Frequency find_max_frequency(const Frequencies &f)
{
    return std::max_element(
        f.begin(), f.end(),
        [](const std::pair<uint32_t, uint32_t> &p1, const std::pair<uint32_t, uint32_t> &p2) {
            return p1.second < p2.second;
        });
}
std::pair<Point, Point> find_search_boundaries(const LineSegmentSet &set)
{
    Frequencies f_end;

    for (auto segment : set)
        ++f_end[segment.second];

    Frequency it_end = find_max_frequency(f_end);
    Point end = it_end->second == 1 ? f_end.rbegin()->first : it_end->first;

    Frequencies f_begin;

    for (auto segment : set)
    {
        if (segment.first > end)
            break;
        ++f_begin[segment.first];
    }

    Frequency it_begin = find_max_frequency(f_begin);
    Point begin;
    if (it_begin->second == 1 && it_end->second > 1)
        begin = f_begin.rbegin()->first;
    else
        begin = it_begin->first;

    return std::pair<Point, Point>(begin, end);
}
} // namespace

OverlapPointSet find_max_overlap_point(const LineSegmentSet &set)
{
    const std::pair<Point, Point> boundaries = find_search_boundaries(set);
    const Frequencies f = get_overlap_frequency(set, boundaries.first, boundaries.second);
    const uint32_t max_frequency = find_max_frequency(f)->second;

    OverlapPointSet result;
    if (max_frequency == 1) // if there is no overlap
        return result;      // return an empty set

    for (auto x : f)
    {
        if (x.second == max_frequency)
            result.insert(x.first);
    }

    return result;
}
