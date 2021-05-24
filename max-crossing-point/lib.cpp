#include "lib.h"

#include <algorithm>

using Frequencies = std::map<Point, uint32_t>;
using Frequency = Frequencies::const_iterator;

namespace
{
Frequencies get_overlap_frequency(const LineSegmentSet &set)
{
    Frequencies f;
    for (auto segment : set)
    {
        for (int32_t i = segment.first; i <= segment.second; ++i)
            ++f[i];
    }

    return f;
}
uint32_t get_max_frequency(const Frequencies &f)
{
    Frequency it = std::max_element(
        f.begin(), f.end(),
        [](const std::pair<uint32_t, uint32_t> &p1, const std::pair<uint32_t, uint32_t> &p2) {
            return p1.second < p2.second;
        });

    return it != f.end() ? it->second : 0;
}
} // namespace

OverlapPointSet find_max_overlap_point(const LineSegmentSet &set)
{
    Frequencies f = get_overlap_frequency(set);
    uint32_t max_frequency = get_max_frequency(f);
    OverlapPointSet result;

    for (auto x : f)
    {
        if (x.second == max_frequency)
            result.insert(x.first);
    }

    return result;
}
