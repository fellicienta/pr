#pragma once

#include <map>
#include <stdint.h>

using Frequencies = std::map<uint32_t, uint32_t>;
using Frequency = Frequencies::const_iterator;

uint32_t roll_sample(const uint32_t dice_in_roll, const uint32_t die_faces,
                     const uint32_t sample_size);
uint32_t computation(const uint32_t faces);
