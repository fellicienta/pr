#pragma once

#include <stdint.h>

using Value = uint32_t;

Value get_most_frequent_dice_roll(const uint32_t dice_in_roll, const uint32_t die_faces,
                                  const uint32_t sample_size);
